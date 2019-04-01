//===============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//===============================================================
/*
 -------------------------
1.	반복문이란?
-------------------------

	1.	필요성..

		-	동일한 작업을 일정 횟수( 또는 일정 조건 )동안 반복하고 싶을때 필요.

	2.	종류

		-	while

		-	do ~ while

		-	for

        -   foreach
     

-------------------------
2.	while
-------------------------

	1.	형식

		while( 반복 조건 )
		{
			반복 구간

            반복조건을 무너뜨리기 위한 연산
		}

	
		예)	
			int num = 0;
	
			while( num < 3 )
			{	
				printf("Hello !!\n");

				++num;
			}


 */
//===============================================================
//*
public class WhileTest : MonoBehaviour
{
    public GameObject[] _objects;

    private void Start()
    {
        int count = 0;

        while( count < _objects.Length )
        {
            _objects[count].GetComponent<Renderer>().material.color = Color.yellow;

            ++count;
        }
    }

}
//*/
//===============================================================
/* 두개의 값을 입력 받아 연산하기.

public class WhileTest : MonoBehaviour
{
    public int _valueA;
    public int _valueB;

    private void Start()
    {
        Debug.Log(_valueA + " * " + _valueB + " = " + (_valueA * _valueB));
    }
}
//*/
//===============================================================
/*	quiz)
    숫자를 하나 입력 받으면 그 숫자에 대한 구구단을 출력한다.*/
