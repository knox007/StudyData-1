/*
--------------------------
1.	오버 플로우
--------------------------

	1.	변수는 자료형에 따라 관리할 수 있는 데이터의 범위가 정해진다.

	2.	오버 플로우

		-	변수가 관리할 수 있는 범위를 넘어서는 크기의 값을 저장하게 되면 발생하는 현상.

*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OverFlow : MonoBehaviour {

	// Use this for initialization
	void Start () {
        
        byte a = byte.MaxValue; //  255 -> 1111 1111

        print(a);

        ++a;    //  1111 1111 + 0000 0001 = 0001 0000 0000

                //  1바이트는 8개의 비트만 관리할수 있으므로

                //  자릿수가 올라간 왼쪽 비트는 버려지고 오른쪽 8개의 비트만 관리함.
        
        print(a);
        

        sbyte b = sbyte.MinValue;   //  -128    ->  1000 0000

        print(b);

        --b;    //  1000 0000 - 0000 0001 = 0111 1111 = 127

        print(b);
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
