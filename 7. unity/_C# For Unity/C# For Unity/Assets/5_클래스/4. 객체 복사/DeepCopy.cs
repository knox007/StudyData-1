using System.Collections;
using System.Collections.Generic;
using UnityEngine;

class CTest
{
    public int _a;
    public int _b;

    public CTest DeepCopy()
    {
        CTest tmpTest = new CTest();

        tmpTest._a = _a;
        tmpTest._b = _b;

        return tmpTest;
    }
}

public class DeepCopy : MonoBehaviour {

	// Use this for initialization
	void Start () {

        print("--- 얕은 복사 ---");
        {
            CTest test1 = new CTest();
            test1._a = 10;
            test1._b = 20;

            CTest test2 = test1;
            test2._b = 30;

            print(test1._a);
            print(test1._b);

            print(test2._a);
            print(test2._b);
        }
        

        print("--- 깊은 복사 ---");
        {
            CTest test1 = new CTest();
            test1._a = 10;
            test1._b = 20;

            CTest test2 = test1.DeepCopy();
            test2._b = 30;

            print(test1._a);
            print(test1._b);

            print(test2._a);
            print(test2._b);
        }

    }
	
}
