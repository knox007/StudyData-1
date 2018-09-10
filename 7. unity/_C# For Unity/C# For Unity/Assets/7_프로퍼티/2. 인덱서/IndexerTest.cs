/*
    1.  인덱서

        -   배열의 인덱스를 이용해 객체내의 데이터에 접근하게 하는 프로퍼티

            -   객체를 배열처럼 사용.
        
        -   선언

            class 클래스이름
            {
                접근지정자 인덱서타입 this[ 인덱스타입 index ]
                {
                    get { ......... }

                    set { ......... }
                }
                
            }
        
        -   프로퍼티는 프로퍼티 이름으로 객체내의 데이터 접근.
            
            인덱서는 인덱스를 통해 접근.
        
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;


public class IndexerTest : MonoBehaviour {


	class CIndexTest
	{
		int[] _array;

		public CIndexTest()	{ _array = new int[3]; }

		public int this[int idx]
		{
			get { return _array [idx];}

			set
			{
				if (idx >= _array.Length)
				{
					Array.Resize<int> (ref _array, idx + 1);

					print( string.Format("Array resized : {0}", _array.Length));
				}

				_array [idx] = value;
			}
		}

		public int Length { get { return _array.Length; } }
	}

    void Start ()
    {

		CIndexTest _test = new CIndexTest ();

		for (int i = 0; i < 5; ++i)
			_test [i] = i;

		for (int i = 0; i < _test.Length; ++i)
			print (_test[i]);		
		
	}
}
