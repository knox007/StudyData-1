using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TransformFunctions : MonoBehaviour {

    public float moveSpeed = 10f;
    public float turnSpeed = 50f;

    //  transform 캐싱은 유효한가?
    //  https://blogs.unity3d.com/kr/2014/06/23/unity5-api-changes-automatic-script-updating/
    //  https://forum.unity.com/threads/cache-transform-really-needed.356875/
    Transform _myTransf;

    private void Start()
    {
        _myTransf = transform;
    }

    void Update()
    {
        /*
            Time.deltaTime
            
                -   마지막(바로 전) 프레임을 완료하는데 걸린 시간.

                    게임이 프레임 독립적으로 작동하도록 하는데 주로 사용.

                -   만약 유니티 게임이 초당 30프레임이라면 
                
                    Time.deltaTime은 대략  1/30(타입은 float) = 0.033f

                    -   최적화나 컴퓨터 사양 등의 이유로 항상 일정하지 않을수 있음.

                    -   http://bluemeta.tistory.com/1

                1초 = 6fps인 상태에서 현재 5프레임 일때,

                Time.deltaTime은 4프레임과 5프레임의 바로전 프레임을 완료하는데 걸린 시간.

                1      2                  3    4 ------------ 5                   6
                |------|------------------|----|--------------|-------------------|--------------|
                0초                                                                              1초

                -   용도

                    -   갱신될 정보의 변화를 매프레임이 아닌 매초당 일어나도록 만들어 줌.

                    -   예)

                            void Update()
                            {
                                float translation = Time.deltaTime * 10;

                                transform.Translate(0, 0, translation);

                             }

                            -   Time.deltaTime를 곱하지 않으면

                                매프레임당 10유닛 이동.

                                초당 30프레임의 프레임 레이트를 갖는 게임이라면 1초에 약 300 단위거리 이동(미터).

                            -   프레임단위보다는 초단위로 생각하는 것이 더 익숙하며,

                                프레임 레이트도 환경에 따라 다르다.

                            -   Time.deltaTime은 초당 30프레임의 프레임 레이트에서 대략 1/30.
                            
                                translate = 10 * 1/30 = 1/3f.
                                
                                Update() 메소드는 1초에 30번 반복
                                
                                -   1초후 이동거리 =  1/3f * 30 = 10만큼 이동.

                                -   Update() 안에서 Time.deltaTime을 곱함으로서 초당 10유닛만큼 이동하는 기능을 구현.


                -   정리.
                
                    -   Time.deltaTime 
                            
                        -   마지막(바로 전) 프레임을 완료하는데 걸린 시간.
                        
                    -   Time.deltaTime은 항상 일정하지 않지만 대략 1 / (프레임 레이트).
                    
                    -   Update() 내의 변수에 Time.deltaTime을 곱함으로써 해당 변수가 1초에 걸쳐 일어나는 변화임을 나타냄.


         */

        //  https://docs.unity3d.com/kr/current/ScriptReference/Transform.Translate.html
        if (Input.GetKey(KeyCode.UpArrow))
            _myTransf.Translate(Vector3.forward * moveSpeed * Time.deltaTime);

        if (Input.GetKey(KeyCode.DownArrow))
            _myTransf.Translate(-Vector3.forward * moveSpeed * Time.deltaTime);

        //  https://docs.unity3d.com/kr/current/ScriptReference/Transform.Rotate.html
        if (Input.GetKey(KeyCode.LeftArrow))
            _myTransf.Rotate(Vector3.up, -turnSpeed * Time.deltaTime);

        if (Input.GetKey(KeyCode.RightArrow))
            _myTransf.Rotate(Vector3.up, turnSpeed * Time.deltaTime);
    }
}
