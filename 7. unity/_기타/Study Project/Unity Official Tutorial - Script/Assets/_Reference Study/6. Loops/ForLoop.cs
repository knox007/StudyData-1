using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
	for( 초기식; 조건식; 증감식 )
	{
		반복 대상
    }
*/
public class ForLoop : MonoBehaviour
{
    int numEnemies = 3;

    void Start()
    {
        for (int i = 0; i < numEnemies; i++)
        {
            Debug.Log("Creating enemy number: " + i);
        }
    }
}
