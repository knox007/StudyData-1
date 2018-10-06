/*
	InvokeRepeating

	-	pubic void InvokeRepeating( string methodName, float time, float repeatRate );

		-	methodName	:	실행할 메소드.

		-	time		:	호출 지연시간.

		-	repeatRate	:	호출 반복시간.

		-	time 후에 methodName 를 호출한 후 repeatRate 마다

			반복적으로 호출.
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InvokeRepeating : MonoBehaviour {

	public GameObject target;

	void Start()
	{
		InvokeRepeating("SpawnObject", 2, 1);
	}

	void SpawnObject()
	{
		float x = Random.Range(-2.0f, 2.0f);
		float z = Random.Range(-2.0f, 2.0f);
		Instantiate(target, new Vector3(x, 2, z), Quaternion.identity);
	}
}
