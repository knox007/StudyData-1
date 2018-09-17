using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*

    foreach
       
        -   배열(또는 컬렉션)을 순회하며 각 데이터 요소에 차례대로 접근 하도록 함.

        -   배열(또는 컬렉션) 끝에 도달하면 자동으로 반복이 종료.

        -   사용 방법

            foreach( 데이터_타입  변수명  in  배열_또는_컬렉션 )
                코드_또는_코드블록

        -   in 키워드와 함께 사용.

            요소를 차례대로 순회하면서 in 키워드 앞의 변수에 담는다.

        -   최적화 및 속도 관련 이슈

            http://geekcoders.tistory.com/entry/Unity-%EC%9C%A0%EB%8B%88%ED%8B%B0-%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%A8%B8%EA%B0%80-%EC%95%8C%EC%95%84%EC%95%BC-%ED%95%A0-%EC%BD%94%EB%93%9C%EC%9E%91%EC%84%B1%EB%B2%95

            http://blog.ejonghyuck.net/221015850179



 */
public class ForeachLoop : MonoBehaviour
{
    void Start()
    {
        string[] strings = new string[3];

        strings[0] = "First string";
        strings[1] = "Second string";
        strings[2] = "Third string";

        foreach (string item in strings)
        {
            print(item);
        }
    }
}