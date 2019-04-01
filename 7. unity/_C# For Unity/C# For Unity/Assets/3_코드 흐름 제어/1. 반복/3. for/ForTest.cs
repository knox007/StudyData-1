﻿//============================================================
/*
-------------------------
1.	for
-------------------------

	1.	형식.

		for( 초기식; 조건식; 증감식 )
		{

			반복 대상

		}

    
    2.	while vs for (1)

    	-	for문의 경우 반복을 구성하기 위해 필요한 모든 요소를 한군데 묶어서 관리.
	
	    -	초기식	:	반복을 시작하기 앞서 딱 한번 실행됨. 

                        초기식은 for문 내부나 외부에서도 선언 및 초기화가 가능하다.	

		
    		조건식	:	매번 반복을 시작하기 앞서 실행되며, 

	    				조건식의 결과에 따라 반복 유무가 결정됨.

    		증감식	:	반복 영역 실행 후 진행.


        while vs for (2)
	
    	-	반복의 횟수가 명시적으로 정해진 경우 for문 권장.

	    -	그외의 경우, 특히 사용자의 입력값에 따라 반복 유무가 정해지는 경우 while 권장.



*/
//============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//============================================================
public class ForTest : MonoBehaviour
{
    public int _count = 5;

    private void Start()
    {
        //*
         
        //int num = 0;
        //for (int num = 0; num < _count; ++num)
        for (int num = 0; num < _count; ++num)
            print("Hello!! " + num + "회 출력");
        //*/

        /*
        int num = 0;
        while( num < _count )
        {
            print("Hello!! " + num + "회 출력");
            ++num;
        }
        //*/

    }
}
//============================================================
/*	quiz)
	두 수를 입력하여 작은수와 큰수 사이의 합을 구한다.
*/
