using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FloatingPoint : MonoBehaviour {

	// Use this for initialization
	void Start () {

        float a = 3.14259265358979323846f;  //  자신의 가수부가 담을 수 있는 부분까지만 저장하고 나머지는 버림.

        double b = 3.14259265358979323846;

        print(a);

        print(b);

        //  메모리를 두배로 사용하지만
        //  데이터의 손실이 적기때문에
        //  double형 사용을 권장.

    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
