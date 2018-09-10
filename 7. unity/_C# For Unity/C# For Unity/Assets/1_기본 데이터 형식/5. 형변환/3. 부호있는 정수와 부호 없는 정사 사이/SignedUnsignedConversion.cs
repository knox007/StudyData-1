using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SignedUnsignedConversion : MonoBehaviour {

	// Use this for initialization
	void Start () {

        int a = 500;
        print(a);

        uint b = (uint)a;
        print(b);

        int c = -30;
        print(c);

        uint d = (uint)c;
        print(d);
        
	}
	
}
