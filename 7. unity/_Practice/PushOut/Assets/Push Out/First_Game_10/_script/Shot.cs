//=====================================================
/*
 1. Debug.DrawRay
*/
//=====================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=====================================================
public class Shot : MonoBehaviour
{
    //----------------------
    //  사정거리
    public float _range = 10f;
    //  파워.
    public float _pow = 200f;
    //  트랜스폼 정보.
    Transform _myTrsf;
    //  addforce 모드 비교를 위한 토글.
    public bool _isDefaultAddForce = true;
    //----------------------
    private void Start()
    {
        _myTrsf = transform;
    }
    //----------------------
    private void Update()
    {
        Debug.DrawRay(_myTrsf.position, _myTrsf.forward * _range, Color.red);

        //  Space 버튼을 눌렀는지 확인.
        if(Input.GetKeyUp(KeyCode.Space))
        {
            //  가상의 선에 충돌한 오브젝트의 정보를 받아올 변수.
            RaycastHit hitInfo;
            //  _myTrsf 트랜스폼의 위치와 방향, 범위를 참고하여 가상의 선을 쏜뒤 
            //  충돌한 오브젝트가 있다면 해당 정보를 hitInfo에 반환한다.
            if ( Physics.Raycast(_myTrsf.position, _myTrsf.forward, out hitInfo, _range ))
            {
                //  충돌한 오브젝트의 태그를 비교한다.
                if(hitInfo.collider.gameObject.CompareTag("FBC"))
                {
                    //  이름을 출력한다.
                    Debug.Log(hitInfo.collider.name);
                    //  충돌한 지점에 물리력을 적용한다.
                    if(_isDefaultAddForce)
                        hitInfo.rigidbody.AddForce(_myTrsf.forward * _pow);
                    else
                        hitInfo.rigidbody.AddForceAtPosition(_myTrsf.forward * _pow, hitInfo.point);
                    
                }
            }
        }

    }
    //----------------------
}
//=====================================================