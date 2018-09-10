/*
    1.  Func & Action 대리자

        -   필요성

            -   한개의 익명 메소드를 사용하기 위해 이를 참조할 델리게이트 변수가 필요.

            -   델리게이트 변수를 생성하기 앞서 델리게이트 타입을 선언해야 함.

            -   각각 다른 타입의 무명 메소드를 만들때는 그 갯수만큼 따로따로 타입과 변수를 선언해야 함.


        -   Func와 Action
            
            -   미리 선언된 델리게이트 변수.

            -   별도의 선언없이 사용 가능.

            -   매개변수가 없는 매소드 ~ 매개변수 16개인 메소드까지 총 17개의 메소드 참조 가능.

                (익명 메소드, 일반 메소드 포함)

                -   특별한 경우를 제외하고 별도의 델리게이트를 만들 필요없음.

            -   Func

                -   반환값이 있는 메소드를 참조.

                -   형식 매개 변수중 가장 마지막에 있는 것이 반환 형식.

            -   Action

                -   반환값이 없는 메소드를 참조.
*/
//================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
//================================================================
//*  Func
public class FuncTest : MonoBehaviour
{
	// Use this for initialization
	void Start () {

        Func<int> func1 = () => 10;
        print(string.Format("func1 = {0}", func1()));

        Func<int, int> func2 = (x) => x * 2;
        print(string.Format("func2 = {0}", func2(4)));

        Func<double, double, double> func3 = (x, y) => x / y;
        print(string.Format("func3 = {0}", func3(22,7)));
    }
}
//*/
//================================================================