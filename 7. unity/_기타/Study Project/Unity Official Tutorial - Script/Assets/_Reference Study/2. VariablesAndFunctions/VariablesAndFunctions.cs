/*
    필드

    -   접근지정자  변수타입  변수이름 = 초기값;    ( 초기화 )
        접근지정자  변수타입  변수이름;             ( 선언 )

    -   예)  
    
            (private)       int          myInt   =      5;

            접근지정자       변수타입    변수명         초기값.


    메소드( 멤버 함수 )
    
    -   접근지정자       반환타입    메소드이름   ( 매개변수 목록 ) { 메소드 구현 }

    -   예)  
            (private)       int         MultiplyByTwo     (int number)
            접근지정자       반환타입    메소드이름       ( 매개변수 목록 ) 
            {
                //  메소드 구현부....
                int ret;
                ret = number * 2;
                return ret;
            }
            
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VariablesAndFunctions : MonoBehaviour
{
    //  필드( 멤버 변수 )
    int myInt = 5;

    void Start()
    {
        myInt = MultiplyByTwo(myInt);
        Debug.Log(myInt);
    }

    //  메소드( 멤버 함수 )
    //  -   접근지정자       반환타입    메소드이름   ( 매개변수 목록 ) { 메소드 구현 }
    int MultiplyByTwo(int number)
    {
        int ret;
        ret = number * 2;
        return ret;
    }
}