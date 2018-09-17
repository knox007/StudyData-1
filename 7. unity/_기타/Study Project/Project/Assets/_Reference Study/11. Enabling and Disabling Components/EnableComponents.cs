using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
    enabled

        -   컴포넌트 비활성화

        -   고찰

            -   컴포넌트 비활성화 시 전체 함수가 정지되는 건 아님.
                
                -   스크립트 비활성화 시 MonoBehaviour이 정지 되는데 전체가 아닌 아래 함수들이 정지된다고 함.
                    
                    -   Awake(), Start(), Update(), FixedUpdate(), LateUpdate(), OnGUI(), OnDisable(), OnEnable()

                        -   위 함수들을 하나라도 포함하지 않는 스크립트는 인스펙터 창에서 비활성화 불가능.

                            -   인스펙터 창에 체크박스 표시 안됨.
                        
                        -   https://docs.unity3d.com/kr/current/ScriptReference/MonoBehaviour.html 참고.

                    -   오작동 방지를 위해 다음과 같이 예외처리 할 것.
                            
                        -   void OnTriggerEnter( Collider other )
                            {
                                if( enabled == false )
                                    return;

                                ..............
                                    
                            }

        
    SetActive()
    
        - 오브젝트 비활성화

*/
public class EnableComponents : MonoBehaviour
{
    private Light myLight;


    void Start()
    {
        myLight = GetComponent<Light>();
    }


    void Update()
    {
        if (Input.GetKeyUp(KeyCode.Space))
        {
            myLight.enabled = !myLight.enabled;
        }
    }
}
