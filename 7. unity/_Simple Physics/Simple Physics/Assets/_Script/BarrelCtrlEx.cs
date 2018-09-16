using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BarrelCtrlEx : MonoBehaviour {

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

	public Texture[] _textures;

	MeshRenderer _meshRenderer;

	public float _expRadius = 10.0f;



	// Use this for initialization
	void Start () {

        _rigidBody = GetComponent<Rigidbody>();

        _meshFilter = GetComponent<MeshFilter>();

		_meshRenderer = GetComponent<MeshRenderer> ();

		_meshRenderer.material.mainTexture = _textures [Random.Range (0, _textures.Length)];

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

        /*//  폭발시 무게를 가볍게 함.
        _rigidBody.mass = 1.0f;

        //  윗 방향으로 힘을 적용.
        _rigidBody.AddForce(Vector3.up * 500f);
        */

		IndirectDamage (transform.position);


        /*
         * Random.Range 반환값 범위
         *  
         *  -   Range(float min, float max)
         *      -   min 이상 max 이하.
         *      
         *  -   Range(int min, int max)
         *      -   min 이상 max 미만.
         */
        int idx = Random.Range(0, _meshes.Length);

        //  메쉬 필터에 적용.
        _meshFilter.sharedMesh = _meshes[idx];

        //  변경된 메쉬에 따라 메쉬 컬라이더 수정.
        GetComponent<MeshCollider>().sharedMesh = _meshes[idx];
    
	
	}

	void IndirectDamage(Vector3 pos)
	{


		Collider[] colliders = Physics.OverlapSphere (pos, _expRadius, 1 << 8);

		foreach (var coll in colliders) {

			var rgdBody = coll.GetComponent<Rigidbody> ();

			rgdBody.mass = 5.0f;



			rgdBody.AddExplosionForce (600f, pos, _expRadius, 500f);





		}


	}
}
