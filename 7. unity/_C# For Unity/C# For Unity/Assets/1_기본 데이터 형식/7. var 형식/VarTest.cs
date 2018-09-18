/*
    1.  S.T.L

        -   C#은 변수나 상수에 대해 형식 검사가 깐깐하다.
            
            -   Strong Typed Language
            
            -   프로그래머의 실수를 줄여줌.
                
                -   컴파일 단계에서 오류를 발생시킴.

     

    2.   var을 통해서 약한 형식 검사를 하는 언어 기능 지원.

            -   var을 사용해서 변수를 선언하면 컴파일러가 자동으로 해당 변수의 

                형식 지정.

            -   반드시 초기화를 해줘야 함.

            예)
                var a = 3;          //  a는 int

                var b = "Hello";    //  b는 string

            -   지역변수로만 사용.
            
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//using System;

public class VarTest : MonoBehaviour {
        
	// Use this for initialization
	void Start () {

        var a = 20;     //  using System;
        print(a.GetType().ToString() + "  :  " + a);

        var b = 3.141213;
        print(b.GetType().ToString() + "  :  " + b);

        var c = "Hello";
        print(c.GetType().ToString() + "  :  " + c);

        var d = new int[] { 1, 2, 3 };
        print(d.GetType().ToString());

        foreach (var e in d)
            print(e);

    }
}
