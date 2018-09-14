//============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//============================================================
public class FloatTest : MonoBehaviour
{
    //----------------------------
	void Start ()
    {
        print("----- 부동 소수점 오차 테스트 1------");
        float f = 0f;
        for (int cur = 0; cur < 1000; ++cur)
            f += 0.01f;
        print(f);


        print("----- 부동 소수점 오차 테스트 2------");
        float a = 10f;
        float b = 1.3f;
        
        float c = a*b;
        int d = (int)(a * b);

        print(c);
        print(d);       


        print("----- float 정밀도 테스트 ------");
        float ff1 = 1.123456f;
        float ff2 = 1.1234567f;
        print(ff1);
        print(ff2);

    }// void Start ()
    //----------------------------

}// public class FloatTest : MonoBehaviour
 //============================================================