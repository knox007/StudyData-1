/*
 char

    -   정수를 다루는 데이터 형식을 기반으로 함.
    
    -   c#은 c/c++ 보다 형식검사가 강하다

        -   c의 경우 서식 문자로 정수나 문자로 표현이 가능 하지만

            문자만 가능함.

string

    -   여러개의 문자를 연속으로 처리하는 타입.

    -   정해진 크기나 담을 수 있는 데이터의 범위가 따로 정해져있지 않다.

        -   텍스트 양에 따라 유동적임.

 */
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Char : MonoBehaviour {

	// Use this for initialization
	void Start () {

        char a = '안';
        //char a = (char)65;
        //int a = '안';
        char b = '녕';
        char c = '하';
        char d = '세';
        char e = '요';

        print(a);
        print(b);
        print(c);
        print(d);
        print(e);

        string aa = "안녕하세요";
        print(aa);



    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
