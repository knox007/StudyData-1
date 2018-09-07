/*
1.  문자열 찾기

    메소드          |          설명
    -----------------------------------------------------------------------
    IndexOf()       |   찾고자 하는 지정된 문자 또는 문자열의 위치 검색.
    LastIndesOf()   |   찾고자 하는 지정된 문자 또는 문자열의 위치를 뒤에서부터 검색.
    StartsWith()    |   매개변수로 설정된 문자열로 시작하는지 확인.
    EndsWith()      |   매개변수로 설정된 문자열로 끝나는지 확인.
    Contains()      |   매개변수로 설정된 문자열을 포함하는지 확인.
    Replace()       |   매개변수 A를 매개변수 B로 변환한 문자열을 반환.
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StringSearch : MonoBehaviour {

	// Use this for initialization
	void Start () {

        string test = "Good Morning";

        print(test);

        //  IndexOf
        print("IndexOf Good : " + test.IndexOf("Good"));
        print("IndexOf d : " + test.IndexOf("d"));

        //  LastIndexOf
        print("LastIndexOf Good : " + test.LastIndexOf("Good"));
        print("LastIndexOf d : " + test.LastIndexOf("d"));

        //  StartsWith
        print("StartsWith Good : " + test.StartsWith("Good"));
        print("StartsWith Morning : " + test.StartsWith("Morning"));

        //  EndsWith
        print("EndsWith Good : " + test.EndsWith("Good"));
        print("EndsWith Morning : " + test.EndsWith("Morning"));

        //  Contains
        print("Contains Bad : " + test.Contains("Bad"));
        print("Contains Morning : " + test.Contains("Morning"));

        //  Replace
        print("Replace Morning with Night : " + test.Replace("Morning", "Night"));

    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
