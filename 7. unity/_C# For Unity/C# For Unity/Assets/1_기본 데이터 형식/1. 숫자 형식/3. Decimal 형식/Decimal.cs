/*
    decimal
        
        -   유효범위 29자리
        
        -   16 바이트
        
        -   -7.9e28 ~ 7.9 e28

 */
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Decimal : MonoBehaviour {

	// Use this for initialization
	void Start () {

        float a = 3.142592653589793238462643383279f;    //  f       : float형 literal
        double b = 3.142592653589793238462643383279;    //  nothing : double형 literal
        decimal c = 3.142592653589793238462643383279m;  //  m       : decimal형 literal

        print(a);
        print(b);
        print(c);


    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
