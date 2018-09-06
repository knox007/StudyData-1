/*
	1.	일반화 대리자.

		-	선언

			delegate	반환형식	대리자이름<T>	( 매개변수 목록 );

*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

delegate int Compare<T>(T a, T b);

public class GenericDelegateTest : MonoBehaviour {

	int AscendCompare<T>(T a, T b) where T : IComparable<T>
	{
		return a.CompareTo(b);
	}

	int DescendCompare<T>(T a, T b) where T : IComparable<T>
	{
		return a.CompareTo(b) * -1;
	}

	void BubbleSort<T>(T[] array, Compare<T> cmp )
	{
		int i = 0;
		int j = 0;
		T tmp;

		for (i = 0; i < array.Length - 1; ++i)
		{
			for (j = 0; j < array.Length - (i + 1); ++j)
			{
				if (cmp (array [j], array [j + 1]) > 0)
				{
					tmp = array [j + 1];
					array [j + 1] = array [j];
					array [j] = tmp;	
				}

			}//	for (j = 0; array.Length - (i + 1); ++j)

		}//	for (i = 0; array.Length - 1; ++i)
	}


	// Use this for initialization
	void Start () {
	
		int[] array1 = {3,7,4,2,10};

		print ("----- Origin array1 -----");
		foreach (int a in array1)
			print (a);

		print ("----- Sorting array1 by AscendCompare -----");
		BubbleSort (array1, new Compare<int> (AscendCompare));
		foreach (int a in array1)
			print (a);


		string[] array2 = { "abc", "def", "ghi", "jkl"};
		print ("----- Origin array2 -----");
		foreach (string a in array2)
			print (a);

		print ("----- Sorting array2 by DescendCompare -----");
		BubbleSort (array2, new Compare<string> (DescendCompare));
		foreach (string a in array2)
			print (a);

	}

}
