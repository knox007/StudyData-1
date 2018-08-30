/*
    인터페이스

        -   목적

            -   일종의 규격, 약속등을 미리 규정.
            
            -   


        -   선언

            interface   인터페이스_이름
            {
                반환형 메소드_이름(매개변수 목록);
                반환형 메소드_이름(매개변수 목록);
                ......
            }

            예)
                interface ILog
                {
                    void WriteLog( string log );
                    .....
                }

            -   클래스 선언과 유사.

            -   메소드, 이벤트, 인덱서, 프로퍼티만 가질수 있음.

            -   구현부가 없음.

            -   접근제한자를 사용할 수 없고 전부 public.

            -   인터페이스로는 인스턴스(객체, 변수)를 만들수 없음.

                -   인터페이스를 상속받는 클래스의 인스턴스를 만드는 것은 가능.

                    -   자식 클래스는 인터페이스에 선언되어있는 모든 메소드를 
                    
                        구현해줘야 함.

                        -   public 한정자로 수식해야함.

            -   인터페이스는 인스턴스는 만들지 못하지만 참조는 가능.

                -   자식 클래스가 부모클래스로 인식.

                
*/

//  Simple Hack & Slash - FSM 참고

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InterfaceTest : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
