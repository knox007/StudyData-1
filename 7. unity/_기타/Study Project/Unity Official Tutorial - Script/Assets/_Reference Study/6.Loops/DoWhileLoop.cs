﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
		do
		{
			반복 구간		
		}
		while( 반복 조건 );


        -   필요성..
        
            -	반복 영역이 최소한 한번은 실행되어야 하는 구조.


        -    while문과의 차이

    		-	반복 조건의 검사 위치가 다르다.
		
	    	-	반복영역이 최소 1회 이상 실행된다.

		    	->	사실 do ~ while <-> while문이 서로 대체 가능하다.

    				보통 while문의 경우 코드 작성이나 이해하기에 더 용이하므로

	    			더 많이 사용한다.

 */
public class DoWhileLoop : MonoBehaviour
{
    void Start()
    {
        bool shouldContinue = false;

        do
        {
            print("Hello World");

        } while (shouldContinue == true);
    }
}