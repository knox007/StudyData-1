/*
	CancelInvoke

	-	pubic void CancelInvoke();

		-	현재 MonoBehaviour 상의 실행중인 모든 Invoke호출 취소.

	-	pubic void CancelInvoke( string methodName );

		-	현재 MonoBehaviour 상의 실행중인 methodName에 대한

			모든 Invoke호출 취소.
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CancelInvoke : MonoBehaviour {

	public GameObject target;

	void Start()
	{
		InvokeRepeating("SpawnObject", 1, 1);
	}

	void SpawnObject()
	{
		float x = Random.Range(-2.0f, 2.0f);
		float z = Random.Range(-2.0f, 2.0f);
		Instantiate(target, new Vector3(x, 2, z), Quaternion.identity);
	}

	void Update()
	{
		if (Input.GetButton ("Jump"))
		{
			CancelInvoke ();
			//CancelInvoke ("SpawnObject");
		}
	}
}
