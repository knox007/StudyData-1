using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
    Update()
    
        -   매 프레임마다 호출.
            
        -   일반적으로 가장 빈번하게 사용
                
        -   물리 효과가 적용되지 않은 오브젝트의 움직임,
        
            단순한 타이머, 키 입력을 받을 때 사용.

    FixedUpdate()
    
        -   프레임을 기반으로 호출되는 Update 와 달리
        
           	Fixed Timestep에 설정된 값에 따라 일정한 간격으로 호출.
            
        -   물리 효과가 적용된(Rigidbody) 오브젝트를 조정할 때 사용
            
            -   Update는 불규칙한 호출임으로 물리엔진 충돌검사 등이 제대로 안될 수 있음.


    LateUpdate()

        -   모든 Update 함수가 호출된 후, 마지막으로 호출.
        
        -   주로 오브젝트를 따라가게 설정한 카메라에 LateUpdate로 위치 갱신.
        
            -   카메라가 따라다니는 오브젝트가 Update함수 안에서 움직일 경우가 있기 때문.

            -   스크립트의 실행 순서를 장담할 수 없음.

*/
public class UpdateAndFixedUpdate : MonoBehaviour
{
    void FixedUpdate()
    {
        Debug.Log("FixedUpdate time :" + Time.deltaTime);
    }


    void Update()
    {
        Debug.Log("Update time :" + Time.deltaTime);
    }
}
