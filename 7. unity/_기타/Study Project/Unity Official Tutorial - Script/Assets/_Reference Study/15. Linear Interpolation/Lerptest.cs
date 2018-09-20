using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lerptest : MonoBehaviour
{
	public Transform 	_target;    
	Transform 			_myTransf;

	// Use this for initialization
	void Start ()
    {
        _myTransf = GetComponent<Transform>();
    }
	
	// Update is called once per frame
	void Update ()
    {
        /*
			Mathf.Lerp
			
			-	public static float Lerp(float a, float b, float t);

			-	a : 초기 값.

                b : 목표 값.

                t : a와 b사이의 보간비율.

                리턴값 : t를 비율로 적용한 a와 b사이의 값.

		 */

        //  http://developug.blogspot.com/2014/09/unity-vector-lerp.html
        /*         
        Vector3 tmpPos = new Vector3(Mathf.Lerp(_myTransf.position.x, _target.position.x, Time.deltaTime * 0.5f), 0f,0f);
        _myTransf.position = tmpPos;
        //*/


        //_myTransf.position = Vector3.Lerp(transform.position, _target.position, Time.deltaTime);

    }
}
