/*
    스크립팅 규칙과 구문

    -   멤버 접근 연산자 "."

        -   클래스의 멤버(필드, 속성, 프로퍼티 등)에 접근할 때 사용.

    -   ;

        -   코드의 끝에 위치하며 문장의 종결을 의미.

        -   ;을 사용하지 않는 문법구조.
            
            -   클래스 선언의 시작과 끝.
            
            -   함수(메소드) 구현의 시작과 끝.

            -   if, for, while 문등 일부 키워드.

    -   들여쓰기

        -   소스 구문의 단락을 구분하기 위하여 탭이나 공백을 적용하는 것.

        -   소스코드 가독성에 필수.

            
    -   주석

       -    프로그램 내에 삽입된 메모.

			컴파일 대상에서 제외.

				-	프로그램의 실행결과에 영향을 미치지 않음.

	    -	필요성	

		    -	구현한 코드에 대한 부연 설명.

    		-	주의 사항.
	

	    -	종류

		    -	블록 단위 주석

            -	행 단위 주석

        -   유의 사항

		    -	주석 내용은 가급적 간결하고 명료하게 기입 할 것.

		    -	블록 단위 주석 사용시 닫기 주석 유의.


*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicSyntax : MonoBehaviour {

    void Start()
    {
        Debug.Log(transform.position.x);

        if (transform.position.y <= 5f)
        {
            Debug.Log("I'm about to hit the ground!");
        }
    }
}
