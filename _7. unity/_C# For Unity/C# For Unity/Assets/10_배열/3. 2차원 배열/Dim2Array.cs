using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
	1.	다차원 배열( 2차원 배열 )

		-	배열이 관리하는 인덱스가 2개 이상인 배열.

			-	각 차원별 요소 크기가 고정적인 배열

				-	Rectangular 배열.

			-	각 차원별 요소 크기가 서로 다른 배열

				-	가변 배열.

		-	주로 2차원 배열이 많이 사용됨.

            -   2차원 배열

                -   1차원 배열을 원소로 가지는 배열.

	2 - 1.	Rectangular 배열의 선언 및 초기화.

		-	선언

			데이터타입 [ , ] 배열이름 = new 데이터타입[ 2차원 길이, 1차원 길이 ];

			예)	int[ , ] array = new int [2, 3];

				array[0,0] = 1;
				array[0,1] = 2;
				array[0,2] = 3;
				array[1,0] = 4;
				array[1,1] = 5;
				array[1,2] = 6;

		-	초기화

			1)	new 연산자 사용, 배열 크기 명시.
				예)	int[ , ] arr = new int [2,3]{ {1,2,3}, {4,5,6} };

			2)	new 연산자 사용, 배열 크기 생략.
				예)	int[ , ] arr = new int [ , ]{ {1,2,3}, {4,5,6} };

			3)	new 연산자와 배열 크기 모두 생략.
				예)	int[ , ] arr = { {1,2,3}, {4,5,6} };

*/

/*
public class Dim2Array : MonoBehaviour
 {
	// Use this for initialization
	void Start () {

        print("---- new 연산자 사용, 배열 크기 명시. ----");
        int[,] arr1 = new int[2, 3] { {1,2,3}, {4,5,6} };
        for(int i = 0; i < arr1.GetLength(0); ++i)
        {
            for (int j = 0; j < arr1.GetLength(1); ++j)
            {
                string tmp = string.Format("arr1[{0}, {1}] = {2}", i, j, arr1[i, j]);
                print(tmp);
            }
        }

        print("---- new 연산자 사용, 배열 크기 생략. ----");
        int[,] arr2 = new int[,] { { 1, 2, 3 }, { 4, 5, 6 } };
        for (int i = 0; i < arr2.GetLength(0); ++i)
        {
            for (int j = 0; j < arr2.GetLength(1); ++j)
            {
                string tmp = string.Format("arr1[{0}, {1}] = {2}", i, j, arr2[i, j]);
                print(tmp);
            }
        }
                
        print("---- new 연산자와 배열 크기 모두 생략. ----");
        int[,] arr3 = new int[,] { { 1, 2, 3 }, { 4, 5, 6 } };
        for (int i = 0; i < arr3.GetLength(0); ++i)
        {
            for (int j = 0; j < arr3.GetLength(1); ++j)
            {
                string tmp = string.Format("arr1[{0}, {1}] = {2}", i, j, arr3[i, j]);
                print(tmp);
            }
        }

    }	
}
//*/

/*
	2 - 2.	가변 배열의 선언 및 초기화.

		-	선언

			데이터타입 [ ][ ]  배열이름 = new 데이터타입 [가변 배열 길이] [ ];

			-	가변 배열의 요소로 입력되는 배열은 그 길이가 모두 같을 필요 없음.

		-   초기화	

            1)
				int[ ][ ] jagged = new int[3][ ];

				jagged[0] = new int [5]{1,2,3,4,5};
				jagged[1] = new int []{1,2,3};

			2)	int[ ][ ] jagged2 = new int [2][ ] 
				{
					new int [] {100, 200},
					new int[3] { 1,2,3}
				};
				
*/

//*
public class Dim2Array : MonoBehaviour
 {
    // Use this for initialization
    void Start() {

        int[][] jagged1 = new int[3][];
        jagged1[0] = new int[5] { 1, 2, 3, 4, 5 };
        jagged1[1] = new int[] { 10,20,30 };
        jagged1[2] = new int[] { 100, 200, 300 };

        foreach(int[] arr in jagged1)
        {
            print(string.Format("arr\'s Length : {0}", arr.Length));
            foreach (int value in arr)
                print(value);
        }


        int[][] jagged2 = new int[2][]
        {
            new int[]{1000, 2000},
            new int[3]{5,6,7}
        };

        foreach (int[] arr in jagged2)
        {
            print(string.Format("arr\'s Length : {0}", arr.Length));
            foreach (int value in arr)
                print(value);
        }

    }	
}
//*/
