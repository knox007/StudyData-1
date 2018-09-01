/*
    1.  문자열 분할.

        메소드      |       설명
        ------------------------------------------------------------
        Split()     |   지정된 문자를 기준으로 분리한 문자열을 반환.
        SubString() |   지정된 위치로부터 지정된 수만큼의 문자로 이루어진 문자열 반환.
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class StringSlice : MonoBehaviour {

	// Use this for initialization
	void Start () {

        string test = "Good morning";

        print(test.Substring(0, 5));
        print(test.Substring(5));

        string[] array = test.Split(new string[] { " " }, StringSplitOptions.None);
        print("Word Count : " + array.Length);

        foreach (string ele in array)
            print(ele);

    }
}
