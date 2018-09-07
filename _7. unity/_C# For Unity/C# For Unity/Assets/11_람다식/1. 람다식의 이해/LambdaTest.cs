/*
    1.  람다식

        -   목적
                
            -   익명 메소드 만드는 방식( 참고 : 대리자 )

        -   선언

            -   ( 매개변수_목록 ) => 식.

            -   =>  

                -   입력 연산자.

                -   매개변수 전달.
                            
            
            예)
                delegate int Calculate( int a, int b );

                ........    

                Calculate cla = (int a, int b) => a + b;

                또는

                Calculate cla = (a, b) => a + b;

                -   형식 유추기능 제공.

                    -   컴파일러가 대리자의 선언 코드로 부터

                        익명 메소드의 매개 변수 형식을 유추.

        
        -   대리자를 이용하는 방법과 비교.

            대리자 버전)

                delegate int Calculate( int a, int b );
                
                ....
                
                Calculate calc = delegate( int a, int b ) { return a + b; };

            람다식 버전)
                
                delegate int Calculate( int a, int b );
                
                ....
                
                Calculate calc = (a, b) => a + b;

        -   람다식이 있음에도 대리자 버전의 익명메소드를 구현하는 이유?

            -   대리자 버전( C# 2.0 ), 람다식 버전( C# 3.0 )

                -   C# 2.0 버전의 프로젝트와의 호환성 유지.

*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LambdaTest : MonoBehaviour {

    delegate int Calculate(int a, int b);

	void Start ()
    {
        Calculate calc = (a, b) => a + b;

        print(string.Format("{0} + {1} = {2}",3, 4, calc(3,4)));
	}
}
