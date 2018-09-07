/*
    1.  Nullable 형식

        -   아무런 의미없는 값으로 초기화 할 경우 사용.

        -   비어 있는 상태

        -   형식

            데이터타입?  변수이름;

            예)  
                int? a = null;
                float? b = null;


    2.  HasValue    -   해당 변수가 값을 갖고 있는지 확인.
        Value       -   변수에 담긴 값.


*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NullableTest : MonoBehaviour {

	// Use this for initialization
	void Start () {

        int? a = null;

        print(a.HasValue);
        print(a != null);

        a = 3;
        print(a.HasValue);
        print(a != null);
        print(a.Value);


    }
}
