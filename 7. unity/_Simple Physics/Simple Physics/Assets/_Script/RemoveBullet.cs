using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RemoveBullet : MonoBehaviour {

    public GameObject _bulletEffectMetal;

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.collider.tag == "BULLET")
        {
            if(_bulletEffectMetal!=null)
                ShowEffect(collision);

            Destroy(collision.gameObject);
        }

        /*
            Collision   속성

        -   collider    :   충돌한 게임 오브젝트의 collider 컴포넌트

        -   contacts    :   물체 간의 충돌지점.

                            물리엔진에 의해 생성.

                            충돌시 접점은 여러개가 될수 있다.
                        
                            예)  바운싱, 코너 부분 충돌.
                    

        -   gameObject  :   충돌한 게임 오브젝트.

        -   impulse     :   충돌시 발생한 충격량.

        -   relativeVelocity    :   충돌한 두 객체의 상대적인 선 속도.

        -   rigidbody   :   충돌한 게임 오브젝트의 Rigidbody 컴포넌트.

        -   transform   :   충돌한 게임오브젝트의 Transform 컴포넌트.
        */

    }

    void ShowEffect(Collision coll)
    {
        ContactPoint contactPt = coll.contacts[0];

        /*
         
        ContactPoint    속성

        -   normal  :   충돌지점의 법선.

        -   otherCollider   :   충돌지점의 또다른 컬라이더.

        -   point   :   충돌지점 위치.

        -   separation  :   충돌한 두 컬라이더간의 거리.

        -   thisCollider    :   충돌지점의 첫번째 컬라이더
        
         */

        Quaternion rot = Quaternion.FromToRotation(-coll.gameObject.transform.forward, contactPt.normal);

        //  스파크 생성.
        GameObject spark = Instantiate(_bulletEffectMetal, contactPt.point, rot);

        //  스파크를 피충돌체에 자식으로 설정.
        //  -   부모의 트랜스폼 영향을 받음.
        spark.transform.parent = this.transform;
    }

}

/*
 * 회전과 쿼터니언
 * 
 * 쿼터니언( Quaternion )
 *  
 *  -   유니티에서 사용하는 각도 단위.(수학적 용어로 복소수 4차원 벡터.)
 *  
 *  -   각도를 4개의 원소로 표현.( 인스펙터 뷰에서 Debug모드로 확인 가능.)
 *  
 *  
 *  이전 회전 방식
 *  
 *  -   오일러 각도를 이용한 회전.
 *  
 *  -   통상 수학적으로 표현하는 각도는 오일러 각도.
 *  
 *  -   오일러각도
 *  
 *      -   오일러가 고안.
 *      
 *      -   3차원 공간의 절대좌표를 기준으로 물체가 얼마나 회전했는지 측정하는 방법.
 *      
 *      -   프로그래밍(DX등)에서 x,y,z축을 차례대로 회전시켜 적용하는 방식으로 회전한다.
 *      
 *          -   회전하는 동안 두축이 겹치는 경우, 어느 축으로도 회전하지 않고 잠기는 현상 발생. *          
 *              
 *              -   짐벌락(Gimbal Lock)현상.
 *              
 *                  http://hoodymong.tistory.com/?page=6
 *                  
 *                  https://www.youtube.com/watch?v=zc8b2Jo7mno
 *                  
 *              -   원인은 각 축을 차례대로 회전시킨 것.    
 *              
 *              -   차선책으로 x, y, z를 각각 89도로 제한하는 방식 적용.
 *              
 *                  -   쿼터니언 등장.
 *                  
 *                  
 *  -   쿼터니언
 *  
 *      -   세 개의 축을 동시에 회전
 *          
 *          -   유니티는 내부적으로 쿼터니언 타입으로 변환해 사용한다.
 *          
 *          -   오일러 <-> 쿼터니언 인터페이스도 제공한다.
 *           
 */
