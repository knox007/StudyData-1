using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
    Awake & Start 특성.

    -   공통점

        -   게임 실행시 단 1회 호출됨.
    
    -   차이점

        -   Awake
            
            -   게임 오브젝트가 활성화 되어있어야 호출됨.
            
                -   스크립트가 비활성화 되어있어도 
                
                    게임 오브젝트가 활성화 되어있다면 Awake는 호출됨.

        -   Start
        
            -   스크립트가 활성화 되어있어야 호출됨.

                -   게임 오브젝트가 활성화 되어있어도 

                    스크립트가 비활성화 되어있다면 Start는 호출 안됨.

        -   대개의 경우 Awake에서 초기화 작업 하도록 권장.        

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
