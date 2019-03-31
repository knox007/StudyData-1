//=======================================================
/*
    상수

        -   변수와 반대되는 개념. 
            
            데이터 그 자체.

            데이터에 특정한 의미를 부여하고자 할때 사용.

            한번 담긴 데이터는 변경할 수 없다.


    -   const

        -   형식)
        
            const 자료형 상수명 = 값;

    
        
    -   열거형

        -   종류는 같지만 다른 값을 갖는 상수를 선언할 때 사용.

        -   형식)
            
            enum 열거형식명 { 상수1, 상수2, 상수3, ... }

        -   상수1, 상수2.. 는 int 형으로 인식.

        -   첫번째 요소에 특별한 값을 할당해주지 않으면 0으로 자동 할당.

            나머지 값은 1씩 증가한 값을 자동으로 할당.

            특정 요소에 값을 할당하면 그 이후 값들은 자동으로 1씩 증가되어 할당됨.


 */
//=======================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=======================================================
public class ConstEnum : MonoBehaviour
{
    const float PHI = 3.141592f;

    public enum eDIRECTION
    {   
        EAST,
        WEST,
        SOUTH,
        NORTH
    }
    public eDIRECTION _eDirection;

    void Start()
    {
        print("-- 원의 면적 --");
        float rad = 2.0f;
        float circleArea = PHI * rad * rad;
        print(circleArea);

        print("-- 열거형 예시 --");
        _eDirection = eDIRECTION.EAST;
        print(_eDirection);        
    }

}
//=======================================================