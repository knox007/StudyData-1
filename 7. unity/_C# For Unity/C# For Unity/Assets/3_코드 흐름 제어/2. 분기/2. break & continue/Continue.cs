//=====================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=====================================================
public class Continue : MonoBehaviour
{
    public int _range = 10;
    
    void Start()
    {
        for (int cur = 0; cur <= _range; ++cur)
        {
            if (cur % 2 == 0)
                continue;

            print(cur);
        }
    }

}
//=====================================================
/*	quiz )	
	
	n이라는 정수를 입력 받아서
	1~100 중 n의 배수를 합한 값을 출력.

*/
