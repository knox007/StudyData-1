using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LocalFuncTest : MonoBehaviour {

	// Use this for initialization
	void Start () {
        print(ToLowerString("Hello"));
	}

    string ToLowerString( string input )
    {
        char[] arr = input.ToCharArray();

        /*
        for (int cur = 0; cur < arr.Length; ++cur)
            arr[cur] = ToLowerChar(cur);
        
        char ToLowerChar(int idx )  //  c# 7.0 이상 지원
        {
            if (arr[idx] < 65 || arr[idx] > 90) //  A~Z의 아스키 값. 65~90
                return arr[idx];
            else
                return (char)(arr[idx] + 32);   //  a~z의 아스키 값. 97~122
        }
        */

        return new string(arr);
    }
	
}
