using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//	delegate 선언.
delegate int TestDelegate(int a, int b);

class CCalculator
{
	//	인스턴스 메소드.
	public int Plus(int a, int b) {	return a + b; }

	//	정적 메소드.
	public static int Minus(int a, int b) { return a-b; }

}

public class DelegateTest : MonoBehaviour {
	
	void Start ()
	{
		CCalculator cal = new CCalculator ();

		TestDelegate callBack;

		callBack = new TestDelegate (cal.Plus);
		print (callBack (5, 3));

		callBack = new TestDelegate (CCalculator.Minus);
		print (callBack (5, 2));
	}

}
