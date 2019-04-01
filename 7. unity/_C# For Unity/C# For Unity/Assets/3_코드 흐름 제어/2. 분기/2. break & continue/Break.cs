//=====================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=====================================================
public class Break : MonoBehaviour
{
    public int _limitSum = 11;

    void Start()
    {
        int sum = 0, num = 0;

        while(true)
        {
            sum += num;

            if (sum >= _limitSum)
                break;

            ++num;
        }

        print("sum : " + sum);
        print("num : " + num);

    }

}
//=====================================================
/*	quiz 1)	
	
	입력 : 2

	2 x 1 = 2
	2 x 2 = 4

	또는 

	입력 : 6

	6 x 1 = 6
	6 x 2 = 12
	6 x 3 = 18
	.....
	6 x 6 = 18

*/
