using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
	while( 반복 조건 )
	{
		반복 구간
	} 

        -	반복 조건
    	-	반복 구간
    	-	반복조건을 무너뜨리는 연산.
*/
public class WhileLoop : MonoBehaviour
{
    int cupsInTheSink = 4;

    void Start()
    {
        while (cupsInTheSink > 0)
        {
            Debug.Log("I've washed a cup!");
            cupsInTheSink--;
        }
    }
}
