using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class IntegerType : MonoBehaviour {

	// Use this for initialization
	void Start () {
        sbyte a = -10;
        //sbyte a = -500000000000;
        byte b = 40;

        print(a);
        print(b);

        short c = -30000;
        ushort d = 60000;

        print(c);
        print(d);

        //int e = -1000_0000;   //  자릿수 구분자 c# 7.0에서 지원 
        int e = -10000000;
        //int f = 3_0000_0000;
        int f = 300000000;

        print(e);
        print(f);

    }

    // Update is called once per frame
    void Update () {
		
	}
}
