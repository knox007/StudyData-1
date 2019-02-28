//===============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//===============================================================
/*
-------------------------
1.	do ~ while 문의 구성
-------------------------

	1.	필요성..

		-	반복 영역이 최소한 한번은 실행되어야 하는 구조.


	2.	형식

		do
		{
			반복 구간		
		}
		while( 반복 조건 );     <-  ';' 으로 마무리.



	3.	while문과의 차이

		-	반복 조건의 검사 위치가 다르다.
		
		-	반복영역이 최소 1회 이상 실행된다.

			->	사실 do ~ while <-> while문이 서로 대체 가능하다.

				보통 while문의 경우 코드 작성이나 이해하기에 더 용이하므로

				더 많이 사용한다. 
     
*/
//===============================================================
public class DoWhileTest : MonoBehaviour
{
    //-----------------
    int _index = 0;
    //-----------------
    void Start()
    {
        int[] numbers = new int[] { 6, 7, 8, 9 };
        int length = numbers.Length;
        int sum = 0;

        _index = 0;

        do
        {
            print(_index + " : " + numbers[_index]);

            ++_index;

        } while (_index < length);


        _index = 0;

        do
        {
            sum += numbers[_index];

            ++_index;

        } while (_index < length);

        print("sum = " + sum);

    }
    //-----------------
}
//===============================================================