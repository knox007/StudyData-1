using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChangableParams : MonoBehaviour {

	int Sum( params int[] args )
	{
		print ("Summing.....");

		int sum = 0;

		for (int i = 0; i < args.Length; ++i)
		{
			print (args [i]);

			sum += args [i];
		}

		return sum;			
	}

	// Use this for initialization
	void Start () {

		int sum = Sum (1, 2);
		//int sum = Sum (1, 2, 3, 4, 5);
		print ("Sum = " + sum);
		
	}
}
