/*
	IsInvoking

	-	public bool IsInvoking( string methodName );

		-	methodName에대한 Invoke 호출이 있는지 확인.

	-	public bool IsInvoking();

		-	Invoke 호출이 있는지 확인.
		

*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IsInvoking : MonoBehaviour {

	public GameObject target;

	void Start()
	{
		
	}

	void SpawnObject()
	{
		float x = Random.Range(-2.0f, 2.0f);
		float z = Random.Range(-2.0f, 2.0f);
		Instantiate(target, new Vector3(x, 2, z), Quaternion.identity);
	}

	void Update()
	{
		//if (Input.GetButton ("Jump") && !IsInvoking("SpawnObject"))
		if (Input.GetButton ("Jump") && !IsInvoking ())
			InvokeRepeating ("SpawnObject", 1, 1);

		//if (IsInvoking ("SpawnObject"))
		if (IsInvoking ())
			print ("SpawnObject Invoking!!!!");
			
	}
}
