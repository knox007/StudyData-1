/*
    https://docs.unity3d.com/ScriptReference/Object.Destroy.html?_ga=2.132594958.1216030260.1538038852-1209687789.1538038852

    Destroy 
    
    -    원형
    
        -   public static void Destroy(Object obj, float t = 0.0F);

            obj :   메모리에서 제거하고자 하는 게임 오브젝트, 또는 컴포넌트

            t   :   딜레이 타임.

*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyBasic : MonoBehaviour {

	void Update ()
	{
		if(Input.GetKey(KeyCode.Space))
			Destroy(gameObject);
	}
}
