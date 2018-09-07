using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
public class GenericClassTest : MonoBehaviour {

	class CGenericClass<T>
	{
		T[] _array;

		public CGenericClass() { _array = new T[3]; }

		public T this[int idx]
		{
			get { return _array [idx];}

			set
			{
				if (idx >= _array.Length)
				{
					Array.Resize (ref _array, idx + 1);					
					print (string.Format ("Array Resized : {0}", _array.Length));
				}

				_array [idx] = value;
			}
		}

		public int Length { get { return _array.Length; } }
	}

	// Use this for initialization
	void Start ()
	{
		CGenericClass<string> strList = new CGenericClass<string>();
		strList [0] = "abc";
		strList [1] = "def";
		strList [2] = "ghi";
		strList [3] = "jkl";

		for(int i = 0; i < strList.Length; ++i)
			print (strList [i]);

		CGenericClass<int> intList = new CGenericClass<int>();
		intList[0] = 0;
		intList[1] = 1;
		intList[2] = 2;
		intList[3] = 3;
		intList[4] = 4;

		for(int i = 0; i < intList.Length; ++i)
			print (intList [i]);

	}
}
