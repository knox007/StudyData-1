/*
    1.  부동 소수점과 정수형식 사이의 변환
        
        -   부동 소수점  ->  정수형식

            -   소수점 아래는 버리고 소수점 위의 값만 남김.

        -   정수형식    ->  부동 소수점

            -   문제 없음.
 
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FloatToInt : MonoBehaviour {

	// Use this for initialization
	void Start () {

        float a = 0.9f;
        int b = (int)a;
        print(b);

        float c = 1.1f;
        int d = (int)c;
        print(d);

        int e = 10;
        float f = (float)e;
        print(f);

	}
	
}
