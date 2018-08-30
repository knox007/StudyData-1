using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SwapTest : MonoBehaviour {

	// Use this for initialization
	void Start ()
    {
        int x = 1, y = 2;

        print(x);
        print(y);

        print("----- SwapByValue -----");
        SwapByValue(x, y);
        print(x);
        print(y);

        print("----- SwapByReference -----");
        SwapByReference(ref x, ref y);
        print(x);
        print(y);

    }











    void SwapByValue( int a, int b)
    {
        int temp = b;
        b = a;
        a = temp;
    }


















    void SwapByReference( ref int a, ref int b)
    {
        int temp = b;
        b = a;
        a = temp;
    }
}
