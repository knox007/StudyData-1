using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Inventory : MonoBehaviour {
	
	public class Stuff
	{
		public int bullets;
		public int grenades;
		public int rockets;
		public float fuel;

		// 기본 생성자.
		public Stuff ()
		{
			bullets = 1;
			grenades = 1;
			rockets = 1;
		}

		public Stuff(int bul, int gre, int roc)
		{
			bullets = bul;
			grenades = gre;
			rockets = roc;
		}

		public Stuff(int bul, float fu)
		{
			bullets = bul;
			fuel = fu;
		}

	}

	public int bulletCount = 10;

	// Creating an Instance (an Object) of the Stuff class
	public Stuff myStuff;

	void Start()
	{
		myStuff = new Stuff(bulletCount, 5, 5);
		Debug.Log ("--- Inventory ---");
		Debug.Log(myStuff.bullets); 
	}
}
