/*
	1.	배열
		
		-	동일한 데이타 타입으로 구성된 데이터 집합.

		-	인덱스를 통하여 각각의 요소에 접근.

			-	첫번째 요소의 인덱스는 0이며 []연산자로 접근.

		-	선언 및 사용.

			데이터타입 [ ] 	배열이름	=  new 데이터타입[ 크기 ];

			예)
				int [] array = new int[5];

				a[0] = 10;
				a[1] = 20;
				a[2] = 30;
				a[3] = 40;
				a[4] = 50;



	2.	배열의 초기화.

		1)	new 연산자 사용, 배열 크기 명시.

			예)	string [] array = new string[3]{"Hello","World","!!!"};

		2)	new 연산자 사용, 배열 크기 생략.
		
			예)	string [] array = new string[ ]{"Hello","World","!!!"};

		3)	new 연산자와 배열 크기 모두 생략.

			예)	string [] array = {"Hello","World","!!!"};
*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ArrayTest : MonoBehaviour {

	// Use this for initialization
	void Start () {

		string[] array1 = new string[3]{ "Hello", "World", "!!!" };
		print ("---------- array1 -----------");
		foreach (string tmp in array1)
			print (tmp);


		string[] array2 = new string[]{ "Hello", "World", "!!!" };
		print ("---------- array2 -----------");
		foreach (string tmp in array2)
			print (tmp);


		string[] array3 = { "Hello", "World", "!!!" };
		print ("---------- array3 -----------");
		foreach (string tmp in array3)
			print (tmp);

	}

}
