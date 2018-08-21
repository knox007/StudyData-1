/*
    박싱

        -   object 형식은 참조 형식이므로 힙에 데이터를 할당.

        -   object 형식은 값형식의 데이터를 힙에 할당하기위해
        
            박싱 기능을 이용하여 해당 데이터를 힙에 할당.

            박싱 - 박스에 넣는다.

            예)  
                object a = 20;

                1)  20을 박싱한다.
                2)  박싱한 20을 힙에 할당한다.
                3)  a는 그 주소를 참조한다.
               


    언박싱
        
        -   힙에 있던 값 형식 데이터를 값 형식 객체에 다시 할당 해야하는 경우 발생.

            예)  
                object a = 20;

                int b = (int)a;

                1)  a는 20이 박싱되어 저장되어있는 힙을 참조 중.
                2)  b는 a가 참조하고 있는 메모리로부터 값을 복사하려고 시도.
                3)  20이 박싱된 값인지 확인.
                4)  박싱되어있는 20이라는 값을 꺼내어 b에 복사.
                    ->  박싱한 메모리와 언박싱한 메모리 2개 존재.(가비지 발생)
                
        -   주의사항
        
            -   모든 객체가 값형식으로 언박싱 될수 없음.

            -   이전에 박싱이 된 데이터에 한하여 언박싱이 가능.

            -   박싱하기 전 타입을 따라야 함.


    정리

        -   박싱      :   값형식 ->  참조형식으로 변환.
            언박싱    :   참조형식 -> 값형식으로 변환.

        -   값형식을 박싱할때 완전히 새로운 개체가 만들어져야 하며,
            
            이 작업에는 할당 작업보다 최대 20배의 시간이 걸린다고 한다.

            언박싱또한 캐스팅 과정이 할당 작업보다 4배의 시간이 걸릴수 있다고 한다.

            https://docs.microsoft.com/ko-kr/previous-versions/visualstudio/visual-studio-2012/ms173196(v=vs.110) (MSDN 발췌)

        -   엄청난 성능상의 단점과 가비지 발생확률도 높으므로 쓰지 않도록 한다.
    
        
 */
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoxingUnBoxing : MonoBehaviour {

	// Use this for initialization
	void Start () {

        int a = 123;
        object b = (object)a;
        int c = (int)b;         //  언박싱할때, 형변환 연산자를 명시적으로 사용해야 함.

        print(a);
        print(b);
        print(c);

        double x = 3.141592;
        object y = x;           //  박싱할때, 형변환 연산자를 사용하지 않으면 암시적으로 object 타입으로 변환.
        double z = (double)y;

        print(x);
        print(y);
        print(z);


    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
