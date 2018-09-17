using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
    Awake & Start 특성.

    -   공통점

        -   스크립트가 활성화될때 단 1회 호출됨.
    
    -   차이점

        -   해당 스크립트가 비활성화 되어있어도 Awake는 호출됨.

            다시 스크립트를 활성화 시킬때 Start는 호출됨.
            

 */
public class AwakeAndStart : MonoBehaviour
{
    void Awake()
    {
        Debug.Log("Awake called.");
    }


    void Start()
    {
        Debug.Log("Start called.");
    }
}
