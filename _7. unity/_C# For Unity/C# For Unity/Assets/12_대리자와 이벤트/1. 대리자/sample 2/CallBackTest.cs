using System.Collections;
using System.Collections.Generic;
using UnityEngine;

delegate int Compare(int a, int b);

public class CallBackTest : MonoBehaviour {

	int AscendCompare(int a, int b)
	{
		if (a > b)
			return 1;
		else if (a == b)
			return 0;
		else
			return -1;
	}

	int DescendCompare(int a, int b)
	{
		if (a < b)
			return 1;
		else if (a == b)
			return 0;
		else
			return -1;
	}

	void BubbleSort(int[] array, Compare cmp )
	{
		int i = 0;
		int j = 0;
		int tmp = 0;

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
	void Start ()
	{
		int[] array = { 3, 7, 4, 2, 10 };
		print ("----- Origin -----");
		foreach (int a in array)
			print (a);

		print ("----- Sorting by AscendCompare -----");
		BubbleSort (array, new Compare (AscendCompare));
		foreach (int a in array)
			print (a);


		print ("----- Sorting by DescendCompare -----");
		BubbleSort (array, new Compare (DescendCompare));
		foreach (int a in array)
			print (a);
		
	}

}
