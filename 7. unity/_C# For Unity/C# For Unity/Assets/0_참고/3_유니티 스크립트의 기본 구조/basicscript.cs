//=========================================================
//  소스 훑어보기
//=========================================================
/*
    -   키워드 
        
        -   프로그래밍 언어의 규격에 미리 정의된 특별한 단어.
        -   변수 타입, 함수명등.
            예)  int, float, Start
 */
//=========================================================
using System.Collections;
using System.Collections.Generic;
/*  Ctrl + Alt + M / Ctrl + H
https://docs.unity3d.com/ScriptReference/MonoBehaviour.html

using UnityEngine;

    -   UnityEngine 이라는 네임스페이스를 사용하겠다는 선언.

    -   1)  using
            -   네임스페이스를 선언할때 사용하는 키워드.
        2)  UnityEngine
            -   네임 스페이스의 일종.
            
            -   네임 스페이스.
                -   성격이나 하는일이 비슷한 클래스, 구조체, 인터페이스, 대리자, 열거형식 등을
                    하나의 그룹으로 묶어 놓은 것.
        3)  ;
            -   컴파일러에게 문장의 끝을 알리는 기호.

            -   컴파일러
                -   소스 코드로부터 문법적 오류를 검사하여 오류가 없으면 어셈블리 코드로 번역.

			    * 어셈블리 코드
			    :	기계어와 1:1 대응되는 저급 언어

			    * 저급언어
			    :	기계어에 가까운 언어로 사람이 가독하기엔 힘들지만 속도는 빠르다.

*/
using UnityEngine;
/*
public class Basicscript : MonoBehaviour

    -   클래스
        -   C# 프로그래밍을 구성하는 기본 단위.
        -   데이터 + 데이터를 처리하는 기능.
            -   멤버변수와 멤버함수로 구성.

    public class basicscript : MonoBehaviour

        public
            -   접근 제한자의 일종
            -   접근 제한자(또는 접근 한정자)
                -   클래스의 기능중 외부에 공개할지를 정하거나
                    공개한다면 어느정도 공개할지 정하는 기능.
        class
            -   클래스 선언 키워드

        basicscript
            -   클래스 이름
            -   유니티의 경우 파일이름과 클래스의 이름이 다른 파일을
                게임 오브젝트에 부착하려고 하는 경우 에러가 발생.

        MonoBehaviour
            -   유니티의 기본 기능들을 구성한 클래스.
            -   상속
                -   기존의 만들어진 클래스(부모 클래스)의 기능을 물려받아 재사용할수 있도록 한다.(자식 클래스)                
                -   자식 클래스는 부모 클래스의 기능을 재정의 하거나 확장하여 사용한다.

*/
public class Basicscript : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        Debug.Log("Start Func called!!!");
    }

    // Update is called once per frame
    void Update()
    {
        Debug.Log("Update Func called!!!");
    }
}
