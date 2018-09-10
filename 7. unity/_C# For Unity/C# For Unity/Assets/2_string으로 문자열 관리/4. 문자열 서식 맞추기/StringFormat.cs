/*
    1.  문자열 서식 맞추기

        -   형식

            string.Format(문자열 틀, 가변길이 매개변수);
        
            문자열 틀
            
            -   { 매개변수_인덱스,  정렬방식  : 서식_지정자 }

                -   매개변수 인덱스

                    -   입력된 매개변수의 순서대로 0, 1, 2,....로 정의.

                -   정렬방식

                    -   문자가 출력될 위치와 공간 설정

                -   서식 지정자

                    -   매개변수로 입력된 데이터의 표현 방식.

                    -   주요 서식 지정자.

                        D   :   십진수

                        X   :   16진수

                        N   :   컴마로 구분하여 숫자 표현.

                        F   :   고정소수점.

                        E   :   지수.
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StringFormat : MonoBehaviour {

    // Use this for initialization
    void Start() {

        string szFormat = "{0,-20}{1,-15}{2,-30}";

        string szResult = string.Format(szFormat, "Publisher", "Author", "Title");
        print(szResult);
        szResult = string.Format(szFormat, "Marvel", "Stan Lee", "Iron Man");
        print(szResult);

        //  D   :   10 진수
        szResult = string.Format("{0:D}", 123);
        print(szResult);
        szResult = string.Format("{0:D5}", 123);
        print(szResult);
        
        //  X   :   16 진수
        szResult = string.Format("{0:X}", 123);
        print(szResult);
        szResult = string.Format("{0:X8}", 123);
        print(szResult);

        //  N   :   숫자.
        szResult = string.Format("{0:N}", 123456789);
        print(szResult);
        szResult = string.Format("{0:N0}", 123456789);
        print(szResult);

        //  F   :   고정 소수점.
        szResult = string.Format("{0:F}", 123.45);
        print(szResult);
        szResult = string.Format("{0:F5}", 123.45);
        print(szResult);
        
        //  E   :   공학용.
        szResult = string.Format("{0:E}", 123.456789);
        print(szResult);


    }

    // Update is called once per frame
    void Update () {
		
	}
}
