using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GenericMethodTest : MonoBehaviour {

	void CopyArray<T>(T[] src, T[] target )
	{
		for (int i = 0; i < src.Length; ++i)
			target [i] = src [i];
	}


	void Start ()
	{
		int[] src = { 1, 2, 3, 4, 5 };
		int[] target = new int[src.Length];
		CopyArray<int> (src, target);
		foreach (int ele in target)
			print (ele);
		

		string[] src2 = { "one", "two", "three" };
		string[] target2 = new string[src2.Length];
		CopyArray<string> (src2, target2);
		foreach (string ele in target2)
			print (ele);
		
	}


}
