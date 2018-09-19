using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BarrelCtrl : MonoBehaviour {

    //  폭발 효과 프리팹
    public GameObject _expEffect;

    //  피격 횟수.
    int _hitCount = 0;

    //  리지드 바디 컴포넌트
    Rigidbody _rigidBody;

	// Use this for initialization
	void Start () {

        _rigidBody = GetComponent<Rigidbody>();
	}

	void ExpBarrel()
	{        
		Instantiate(_expEffect, transform.position, Quaternion.identity);   //  Quaternion.identity
		//  -   무회전.
		//      기본 회전값을 적용.(0, 0, 0)

		//  폭발시 무게를 가볍게 함.
		_rigidBody.mass = 1.0f;

		//  윗 방향으로 힘을 적용.
		_rigidBody.AddForce(Vector3.up * 500f);
	}

    private void OnCollisionEnter(Collision collision)
    {
        if(collision.collider.CompareTag("BULLET"))
        {
            if (++_hitCount == 3)
                ExpBarrel();
        }
    }


  
}
