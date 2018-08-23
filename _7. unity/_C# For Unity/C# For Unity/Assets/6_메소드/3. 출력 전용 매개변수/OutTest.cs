using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OutTest : MonoBehaviour {

	// Use this for initialization
	void Start () {

        int a = 10;
        int b = 3;
        int res = 0;
        //int res;

        int rest = 0;
        //int rest;

        DivideByRef(a, b, ref res, ref rest);
        //DivideByOut(a, b, out res, out rest);
        //  DivideByOut(a, b, out int res, out int rest);   c# 7.0 이상 지원

        print(a);
        print(b);
        print(res);
        print(rest);

    }
	
    void DivideByRef( int a, int b, ref int result, ref int rest )
    {
        result = a / b;
        rest = a % b;
    }

    void DivideByOut(int a, int b, out int result, out int rest)
    {
        result = a / b;
        rest = a % b;
    }
}

/*
    ref와 out의 차이

    1.  out 키워드를 이용해서 매개변수를 넘길 때
    
        메소드가 해당 매개변수에 결과를 저장하지 않으면

        컴파일 에러 발생.

    2.  out키워드는 메소드를 호출하는 쪽에서 초기화를 하지않은 지역변수를 

        out 매개변수로 넘기는것이 가능.

    3.  출력전용 매개변수는 함수호출시 매개변수 목록안에서 즉석으로 선언 가능. c# 7.0이상 지원.

        

 */
