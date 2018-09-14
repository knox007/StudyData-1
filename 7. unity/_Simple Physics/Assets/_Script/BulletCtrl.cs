//===========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//===========================================================
public class BulletCtrl : MonoBehaviour {
    //------------------
    public float _speed = 1000f;
    //------------------
    Rigidbody _rigidBody;
    //------------------
    // Use this for initialization
    void Start ()
    {
        _rigidBody = GetComponent<Rigidbody>();

        _rigidBody.AddForce(transform.forward * _speed);
        //_rigidBody.AddForce(Vector3.forward * _speed);
        //_rigidBody.AddRelativeForce(Vector3.forward * _speed);
        //_rigidBody.AddRelativeForce(transform.forward * _speed);

    }
    //------------------
}
//===========================================================
/*
 * Rigidbody에 힘(Force)을 가하는 함수.
    
    void AddForce( Vector3 force )

    -   월드 좌표 기준.
    
    -   force를 현재 transform의 절대값으로 적용한다.
    
    void AddRelativeForce( Vector3 force )

    -   로컬 좌표 기준.

    -   force를 현재 transform의 상대값으로 적용한다.
 */
