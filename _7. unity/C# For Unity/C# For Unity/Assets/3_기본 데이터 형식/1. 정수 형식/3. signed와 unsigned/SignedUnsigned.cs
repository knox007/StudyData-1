using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SignedUnsigned : MonoBehaviour {

	// Use this for initialization
	void Start () {

        byte a = 255;

        sbyte b = (sbyte)a;

        print(a);
        print(b);

    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
