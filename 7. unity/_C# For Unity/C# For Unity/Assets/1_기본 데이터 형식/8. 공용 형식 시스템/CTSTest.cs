/*
    1.  공용 형식 시스템
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System;

public class CTSTest : MonoBehaviour {

	// Use this for initialization
	void Start () {

        //  using System 필요.
        System.Int32 a = 123;
        int b = 456;

        print(a + "   " + a.GetType().ToString());
        print(b + "   " + b.GetType().ToString());

        System.String c = "abc";
        string d = "def";

        print(c + "   " + c.GetType().ToString());
        print(d + "   " + d.GetType().ToString());


    }
	
}
