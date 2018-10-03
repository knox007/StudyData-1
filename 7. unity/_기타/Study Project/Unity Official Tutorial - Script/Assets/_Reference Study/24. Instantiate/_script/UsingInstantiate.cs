/*
 	Instantiate

	-	게임오브젝트의 복제본을 생성.
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UsingInstantiate : MonoBehaviour {
	
	public Rigidbody rocketPrefab;
	public Transform barrelEnd;
	public int _bulletSpeed = 100;

	void Update ()
	{
		if(Input.GetButtonDown("Fire1"))
		{
			Rigidbody rocketInstance;
			/*
				rocketPrefab		:	복사본.
				barrelEnd.position	:	생성시 적용할 위치.
				barrelEnd.rotation	:	생성시 적용할 회전값.
			*/
			rocketInstance = Instantiate(rocketPrefab, barrelEnd.position, barrelEnd.rotation) as Rigidbody;
			rocketInstance.AddForce(barrelEnd.forward * _bulletSpeed);
		}
	}
}
