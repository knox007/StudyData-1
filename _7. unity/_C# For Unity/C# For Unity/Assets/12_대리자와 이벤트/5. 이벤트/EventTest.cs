/*
	1.	이벤트

		-	사용 목적

            -   어떤 일이 생겼을때 이를 알려주는 객체가 필요한 경우.

                예) 특정시간이 되었을 때 이를 알려주는 알람시계

                    버튼을 클릭했을 때 이를 알려주는 객체.

        -   동작 원리는 대리자와 유사

            -   이벤트는 대리자를 event 키워드로 수식해서 만듬.

            -   대리자의 단점
                
                -   할당 연산은 기존에 등록된 모든 메서드 리스트를 초기화 시킨다.

                -   해당 클래스 뿐 아니라 외부에서도 메서드 호출하듯이 대리자를 호출할 수 있다.

                    -   객체의 상태를 나타내는 메소드를 관리하는 대리자라면 허위 상태를 적용할 수도 있다.
            
                -   이러한 단점들을 보완한게 이벤트 이다.
                
                    -   이벤트는 할당연산자(=)를 사용할 수 없으며 오직 추가(+=) 연산자나 삭제 (-=)만 가능하다.
                    
                    -   해당 클래스 외부에서는 직접 호출할 수 없다.

        
        -   선언 및 사용 절차.

            1)  대리자 선언.
                
                -   클래스 내부나 외부나 상관없음.

            2)  대리자의 인스턴스를 event 키워드로 수식해서 선언.

            3)  이벤트 핸들러 작성.

                -   대리자와 일치하는 메소드.

            4)  클래스의 인스턴스 생성 후 객체의 이벤트에 이벤트 핸들러 등록.

            5)  이벤트 발생시 이벤트 핸들러 호출.

    
            
    2.  대리자 vs 이벤트

        -   차이점.

            -   이벤트는 외부에서 직접 사용할 수 없음.

        -   용도.

            -   대리자

                -   콜백.

            -   이벤트

                -   객체의 상태 변화나 사건의 발생 알림.

*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System;

public class EventTest : MonoBehaviour
{
    //------------------------------------------
    delegate void EventHandler(string msg);
    //------------------------------------------
    class CNotifier
    {
        public event EventHandler _eventHandler;

        public void DoAction( int number )
        {
            int tmp = number % 10;

            if (tmp != 0 && tmp % 3 == 0)
                _eventHandler(String.Format("{0} : 짝!!!", number));
        }

    }// class CNotifier
    //------------------------------------------
    public void DoSomething(string msg) { print(msg); }
    //------------------------------------------
    // Use this for initialization
    void Start ()
    {
        CNotifier notifier = new CNotifier();
        notifier._eventHandler += new EventHandler(DoSomething);

        for (int i = 1; i < 30; ++i)
            notifier.DoAction(i);

    }
    //------------------------------------------    

}