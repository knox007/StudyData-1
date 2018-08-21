/*
 bool
 
    -   논리 형식
    
    -   1바이트

        -   true나 false를 사용하는데도 1바이트를 사용하는 이유?

            -   컴퓨터가 기본적으로 다루는 데이터의 크기가 바이트 단위.
    
    -   true, false
    
    -   컴퓨터는 어차피 0이 아닌 값들은 true로 인식하므로 

        일반적으로 0이나 1로 참,거짓을 판별하는데 사용.

        예)  if( result == 0 )
                
                do something
            
             else

                do else.

                -   하지만 여기서 사용된 0이 거짓을 의미하는 0인지

                    순수하게 숫자로서 0을 의미하는지는 3자 입장에서는 

                    헷갈리기 쉽다.
   
 */
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bool : MonoBehaviour {

	// Use this for initialization
	void Start () {

        bool a = true;
        bool b = false;

        print(a);
        print(b);


    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
