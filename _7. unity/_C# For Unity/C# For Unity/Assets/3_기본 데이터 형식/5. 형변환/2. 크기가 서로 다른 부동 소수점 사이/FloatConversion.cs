/*
    1.  크기가 서로 다른 부동 소수점 형식사이의 변환

        -   float과 double 사이의 형변환.

            -   부동 소수점 형식의 특성상 오버플로우는 존재하지 않음.

                -   정밀도 손상.


        -   float나 double는 소수를 이진수로 메모리에 보관하며

            형변환(float <-> double)시, 10진수로 복원한 후,

            다시 이진수로 변환하여 기록.

            -   문제는 이진수로 표현하는 소수가 완전하지 않음.

                예)  1/3 같은 수는 0.333333.... 이 되버림.

                
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FloatConversion : MonoBehaviour {

	// Use this for initialization
	void Start () {

        float a = 69.6875f;
        print(a);

        double b = (double)a;
        print(b);

        float c = 0.1f;
        print(c);

        double d = (double)c;
        print(d);
        
    }

}
