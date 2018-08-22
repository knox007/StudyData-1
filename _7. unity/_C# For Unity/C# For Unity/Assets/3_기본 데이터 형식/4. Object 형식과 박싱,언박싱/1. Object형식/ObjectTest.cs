/* 
    object

    -   c#이 모든 데이터 형식의 부모.

        -   기본 데이터 형부터 클래스등의 커스텀 데이터 형등이

            자동으로 object 타입을 상속받게 함.

    -   object  <-  int

                <-  long

                <-  char

                <-  bool

                <-  string

                .......


 */
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectTest : MonoBehaviour {

	// Use this for initialization
	void Start () {

        object a = 123;
        object b = 3.14259f;
        object c = 3.142592653589793238462643383279m;
        object d = true;
        object e = "안녕하세요";

        print(a);
        print(b);
        print(c);
        print(d);
        print(e);
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
