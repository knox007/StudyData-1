﻿//===========================================================
/*

--------------------------
1.	숫자 데이터 형식
--------------------------

	1.	문자 데이터도 숫자(아스키 코드 값 )으로 되어 있다.

       예) 'a' = 61, b = '64'

	2.	15가지 기본 자료형중 12가지가 숫자 데이터 형식.

		-	12가지도 정수, 부동소수, 소수 계열등 3가지로 나뉨.


--------------------------
1 - 1.	정수 계열 형식
--------------------------

	1.	12가지 숫자 형식 중 9가지가 정수 계열 형식.

		-	프로그래머로 하여금 적절한 데이터 형식을 사용함으로써


            메모리를 효율적으로 사용하도록 하기 위함.



        데이터 형식	|	설명                          |크기(바이트)         |	값의 범위											|
		-------------------------------------------------------------------------------------------------------------------------------
        byte        |	부호없는 정수				  |			1		    |	0 ~ 255												|
        sbyte       |	정수                          |			1		    |	-128 ~ 127											|
        char        |	유니코드 문자                 |			2		    |														|

        이하 C/C++과 동일.

        short       |	정수                          |			2		    |	-32,768 ~ 32767                                     |
        ushort      |	부호없는 정수                 |			2		    |	0 ~ 65,535											|
        int         |	정수                          |			4           |	-2,147,483,648 ~ 2,147,483,647						|
        uint        |	부호없는 정수                 |			4		    |	0 ~ 4,294,967,295									|
        long        |	정수                          |			8		    |	-922,337,203,685,477,508 ~ 922,337,203,685,477,507	|

*/
//===========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IntegerType : MonoBehaviour {

	// Use this for initialization
	void Start () {
        sbyte a = -10;
        //sbyte a = -500000000000;
        byte b = 40;
        //byte b = 300;

        print(a);
        print(b);

        print("byte.min = " + byte.MinValue);
        print("byte.max = " + byte.MaxValue);

        short c = -30000;
        ushort d = 60000;

        print(c);
        print(d);

        //int e = -1000_0000;   //  자릿수 구분자 c# 7.0에서 지원 
        int e = -10000000;
        //int f = 3_0000_0000;
        int f = 300000000;

        print(e);
        print(f);

        int max = int.MaxValue;
        int min = int.MinValue;

        print(min);
        print(max);

    }

    // Update is called once per frame
    void Update () {
		
	}
}
