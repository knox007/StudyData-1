using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PartialManager : MonoBehaviour {

	// Use this for initialization
	void Start () {

        PartialTest partialTest = new PartialTest();

        print(partialTest.Method1());
        print(partialTest.Method2());
        print(partialTest.Method3());
        print(partialTest.Method4());

    }
}
