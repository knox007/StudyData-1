/*
    1.  문자열 편집

        메소드      |       설명
        --------------------------------------------------------
        ToLower()   |   대문자 -> 소문자 변환후 반환
        ToUpper()   |   소문자 -> 대문자 변환후 반환
        Insert()    |   지정된 위치에 지정된 문자열 삽입후 반환
        Remove()    |   지정된 위치로부터 지정된 수만큼 문자 삭제후 반환.
        Trim()      |   문자열 앞/뒤 공백 제거후 반환.
        TrimStart() |   문자열 앞 공백 제거후 반환.
        TrimEnd()   |   문자열 뒤 공백 제거후 반환.
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StringEdit : MonoBehaviour {

	// Use this for initialization
	void Start () {

        print("abc".ToUpper());
        print("ABC".ToLower());

        print("Happy Day!!!".Insert(5, " Birth"));
        print("I don't love you".Remove(2, 5));

        string tmp = " I Have No Spaces ";
        print(tmp + "!!!");
        print(tmp.Trim() + "!!!");
        print(tmp.TrimStart() + "!!!");
        print(tmp.TrimEnd() + "!!!");

    }
}
