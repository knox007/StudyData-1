/*
	배열.
        
    -   같은 타입의 메모리를 연속적으로 할당한 것.

    -   데이터타입  []  배열이름 = new 데이터타입 [배열갯수];

    -   배열의 접근

        -   인덱스를 통하여 접근하며 
        
            배열의 첫 요소의 인덱스는 0,

            마지막 요소는 전체갯수 - 1.            

            예)     int [] num = new int[5];

                    num[0] = 1;
                    num[1] = 2;
                    num[2] = 3;
                    num[3] = 4;
                    num[4] = 5;

    -   인스펙터에서의 배열 사용.

        -   접근 지정자를 public으로 선언하면 인스펙터에 노출시킴.

        -   size를 지정해주면 하단에 size갯수만큼 Element들이 노출됨.

        -   배열의 타입에 맞게 게임오브젝트, 컴포넌트, 값등을 채움.

*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Arrays : MonoBehaviour {

	public GameObject[] players;

	void Start ()
	{
		players = GameObject.FindGameObjectsWithTag("Player");

		for(int i = 0; i < players.Length; i++)
		{
			Debug.Log("Player Number "+i+" is named "+players[i].name);
		}
	}
}
