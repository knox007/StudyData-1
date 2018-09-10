using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BarrelCtrl4 : MonoBehaviour {

    //  폭발 효과 프리팹
    public GameObject _expEffect;

    //  파손된 드럼통 메쉬를 저장할 배열.
    public Mesh[] _meshes;

    //  피격 횟수.
    int _hitCount = 0;

    //  리지드 바디 컴포넌트
    Rigidbody _rigidBody;

    //  메쉬 필터 컴포넌트.
    //  -   3D 모델의 3차원 형상정보(메쉬)를 관리.
    MeshFilter _meshFilter;

    //  드럼통에 적용할 텍스쳐 배열
    public Texture[] _textures;

    //  메쉬 렌더러 컴포넌트
    MeshRenderer _meshRenderer;

    //  폭발 반경
    public float _expRadius = 10.0f;

	// Use this for initialization
	void Start () {

        _rigidBody = GetComponent<Rigidbody>();

        _meshFilter = GetComponent<MeshFilter>();

        _meshRenderer = GetComponent<MeshRenderer>();

        //  매터리얼에 할당된 첫번째 메터리얼 설정.
        _meshRenderer.material.mainTexture = _textures[Random.Range(0, _textures.Length)];

    }

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.collider.CompareTag("BULLET"))
        {
            if (++_hitCount == 3)
                ExpBarrel();

        }
    }


    void ExpBarrel()
    {        
        Instantiate(_expEffect, transform.position, Quaternion.identity);   //  Quaternion.identity
                                                                            //  -   무회전.
                                                                            //      기본 회전값을 적용.(0, 0, 0)

        /*        
        //  폭발시 무게를 가볍게 함.
        _rigidBody.mass = 1.0f;
        
        //  윗 방향으로 힘을 적용.
        _rigidBody.AddForce(Vector3.up * 500f);
        */

        IndirectDamage(transform.position);

        int idx = Random.Range(0, _meshes.Length);

        //  메쉬 필터에 적용.
        _meshFilter.sharedMesh = _meshes[idx];

        //  변경된 메쉬에 따라 메쉬 컬라이더 수정.
        GetComponent<MeshCollider>().sharedMesh = _meshes[idx];
    }

    void IndirectDamage(Vector3 pos)
    {
        /*  드럼통 반경에 있는 충돌체들 검출        
         *  반환값     :   충돌체
         *  매개변수   :   원점, 반지름, 레이어
         *  
         *  -   폭발점을 기준으로 반경내에 있는 지정된 레이어를 지닌 충돌체 검출.
         *  
         *  -   레이어
         *  
         *      -   비트연산으로 표기.
         *      
         *      -   1<<8
         *      
         *          -   2^8 = 256
         *          
         *      -   비트연산으로 표기하는 이유?
         *      
         *          -   2개 이상의 레이어 선택 가능.
         *          
         *              -   OR 연산
         *                  
         *                     예)   1<<8 | 1<<7 ->  8 또는 7번 레이어.
         *                     
         *           -  특정 레이어 제외.
         *              
         *              -   NOT 연산
         *              
         *                      예)  ~(1<<8)     ->  8번을 제외한 모든 레이어.
         */
        Collider[] colliders = Physics.OverlapSphere(pos, _expRadius, 1 << 8);

        foreach( var coll in colliders )
        {
            var rgdBody = coll.GetComponent<Rigidbody>();

            rgdBody.mass = 5.0f;

            
            /*
             * 매개변수
             * 
             *  -   횡폭발력, 폭발원점, 폭발반경, 종폭발력
             */
            rgdBody.AddExplosionForce(600f, pos, _expRadius, 500f);
        }

    }
}
