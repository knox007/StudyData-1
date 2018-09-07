/*
    1.  익명 메소드

        -   이름이 없는 메소드

        -   대리자가 참조할 메소드를 넘겨야 할 일이 생겼는데
        
            일회용으로 사용하거나 임시로 사용할 메소드가 필요할때 적용.

        -   선언

            대리자 인스턴스 = delegate( 매개변수 목록 )
                            {
                                ........
                            }
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AnonymousMethodTest : MonoBehaviour
{
    //--------------------------------------
    delegate int Compare(int a, int b);
    //--------------------------------------
    void BubbleSort(int [] lists, Compare cmp )
    {
        int i = 0;
        int j = 0;
        int tmp = 0;

        for( i = 0; i < lists.Length - 1; ++i)
        {
            for (j = 0; j < lists.Length - (i + 1); ++j)
            {
                if( cmp(lists[j], lists[j+1]) > 0 )
                {
                    tmp = lists[j + 1];
                    lists[j + 1] = lists[j];
                    lists[j] = tmp;

                }// if( cmp(lists[j], lists[j+1]) > 0 )

            }// for( j = 0; j < lists.Length - (i + 1); ++j )

        }// for( i = 0; i < lists.Length - 1; ++i)

    }// void BubbleSort(int [] lists, Compare cmp )  
    //--------------------------------------
    void Start ()
    {
        int[] array1 = { 3, 7, 4, 2, 10 };

        print("----- Origin ------");
        foreach (int a in array1)
            print(a);

        print("----- Sort Ascending ------");
        BubbleSort(array1, delegate (int a, int b)
        {
           if (a > b)
               return 1;
           else if (a == b)
               return 0;
           else
               return -1;
       }
        );
        foreach (int a in array1)
            print(a);


        print("----- Sort Descending ------");
        BubbleSort(array1, delegate (int a, int b)
        {
            if (a < b)
                return 1;
            else if (a == b)
                return 0;
            else
                return -1;
        }
        );
        foreach (int a in array1)
            print(a);



    }// void Start ()
    //--------------------------------------
}