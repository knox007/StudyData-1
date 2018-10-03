using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SingleCharacterScript : MonoBehaviour {

	public class Stuff
	{
		public int bullets;
		public int grenades;
		public int rockets;

		public Stuff(int bul, int gre, int roc)
		{
			bullets = bul;
			grenades = gre;
			rockets = roc;
		}
	}

	public int bulletCount = 10;
	public Stuff myStuff;
	public float speed;
	public float turnSpeed;
	public Rigidbody bulletPrefab;
	public Transform firePosition;
	public float bulletSpeed;

	void Start()
	{
		Debug.Log ("--- SingleCharacterScript ---");
		myStuff = new Stuff(bulletCount, 7, 25);
		Debug.Log(myStuff.bullets); 
	}

	void Update ()
	{
		Movement();
		Shoot();
	}


	void Movement ()
	{
		float forwardMovement = Input.GetAxis("Vertical") * speed * Time.deltaTime;
		float turnMovement = Input.GetAxis("Horizontal") * turnSpeed * Time.deltaTime;

		transform.Translate(Vector3.forward * forwardMovement);
		transform.Rotate(Vector3.up * turnMovement);
	}


	void Shoot ()
	{
		if(Input.GetButtonDown("Fire1") && myStuff.bullets > 0)
		{
			Rigidbody bulletInstance = Instantiate(bulletPrefab, firePosition.position, firePosition.rotation) as Rigidbody;
			bulletInstance.AddForce(firePosition.forward * bulletSpeed);
			myStuff.bullets--;
		}
	}
}
