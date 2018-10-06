/*
	Invoke

	-	public void Invoke(string methodName, float time);

		-	methodName	:	실행할 메소드.

			time		:	지연시간.

		-	일정시간 후 지정 메소드 실행.
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InvokeScript : MonoBehaviour {

	public GameObject target;

	void Start()
	{
		Invoke ("SpawnObject", 2);
	}

	void SpawnObject()
	{
		Instantiate(target, new Vector3(0, 2, 0), Quaternion.identity);
	}
}
