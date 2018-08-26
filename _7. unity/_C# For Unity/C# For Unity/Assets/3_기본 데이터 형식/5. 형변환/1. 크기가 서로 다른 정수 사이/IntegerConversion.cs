/*
    1.  크기가 서로 다른 정수 형식 사이의 변환

        1)  작은 형식   ->  큰 형식

            -   문제 없음.

        2)  큰 형식    ->  작은 형식
        
            -   오버 플로우 발생.

*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IntegerConversion : MonoBehaviour {

	// Use this for initialization
	void Start () {

        sbyte a = 127;
        print(a);

        int b = (int)a;
        print(b);

        int c = 128;
        print(c);

        sbyte d = (sbyte)c;
        print(d);

    }
	
}
