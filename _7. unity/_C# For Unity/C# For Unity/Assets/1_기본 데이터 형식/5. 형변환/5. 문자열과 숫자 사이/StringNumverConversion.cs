/*
    1.  문자열과 숫자 간의 형변환
    
        -   기존의 형변환 방법으로는 컴파일 조차 되지 않음.

            예)  string a = "12345";
                int b = (int)a;

                int c = 12345;
                string d = (string)c;

            -   (int)형변환 연산자는 다른 숫자 형식 데이터를 int형식으로

                변환하는 방법( 그리고 object형식을 언박싱 하는 방법 )을 갖고 있지만

                string을 비롯한 다른 형식으로의 변환 방법은 갖고 있지 않음.

                string형도 마찬가지.

            -   c#은 정수계열, 부동소수점 계열 모두 Parse()라는 메소드를 지원.

                매개변수로 숫자로 변환할 문자열을 넘기면 숫자로 반환.

                예)      int a = int.Parse("123");

                         float b = float.Parse("123.45");


            -   숫자 데이터를 문자열로 바꾸는 방법도 지원.

                object로 부터 물려받은 ToString()메소드를 각각 데이터 형에 적당하게
                
                오버라이드(재정의) 함.

                예)     int a = 12345;

                        string b = a.ToString();

                        float c = 123.45f;

                        string d = c.ToString();

*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System;

public class StringNumverConversion : MonoBehaviour {

	// Use this for initialization
	void Start () {

        int a = 123;
        string b = a.ToString();
        print(b);

        float c = 123.4f;
        string d = c.ToString();
        print(d);

        string e = "12345";
        int f = int.Parse(e);
        //int f = Convert.ToInt32(e);   //  using System;
        print(f);

        string g = "1.2345";
        float h = float.Parse(g);
        //float h = Convert.ToSingle(g);   //  using System;
        print(h);
        
	}
	
}
