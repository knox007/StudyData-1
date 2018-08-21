using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IntegerLiteral : MonoBehaviour {

	// Use this for initialization
	void Start () {
        byte a = 240;
        print(a);

        //byte b = 0b11110000;    //  c# 7.0 에서 지원
        //print(b);

        byte c = 0xf0;
        print(c);

        //uint d = 0x1234_abcd;   //  c# 7.0 에서 지원
        uint d = 0x1234abcd;
        print(d);


    }

    // Update is called once per frame
    void Update () {
		
	}
}
