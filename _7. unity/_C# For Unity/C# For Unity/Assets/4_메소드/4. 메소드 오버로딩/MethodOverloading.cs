
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MethodOverloading : MonoBehaviour {

	//------------------------------
	int Plus( int a, int b )
	{
		print ("---- int Plus( int a, int b ) ----");
		return a + b;
	}
	//------------------------------
	int Plus( int a, int b, int c )
	{
		print ("---- int Plus( int a, int b, int c ) ----");
		return a + b + c;
	}
	//------------------------------
	double Plus(double a, double b)
	{
		print ("---- double Plus(double a, double b) ----");
		return a + b;
	}
	//------------------------------
	double Plus( int a, double b )
	{
		print ("---- double Plus( int a, double b ) ----");
		return a + b;
	}
	//------------------------------
	// Use this for initialization
	void Start () {
		print (Plus (1, 2));
		print (Plus (1, 2,3));
		print (Plus (1.0, 2.4));
		print (Plus (1, 2.4));
		
	}

}
