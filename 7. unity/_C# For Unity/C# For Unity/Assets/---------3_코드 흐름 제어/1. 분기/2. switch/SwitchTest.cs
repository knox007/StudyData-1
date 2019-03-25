//=========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=========================================================
/*

    1.	if ~ else 문과 유사.

        -   차이점

            if ~ else 는 모든 참인 조건을 만날때까지 모든 조건을 체크.
            switch 는 해당 조건만 체크.


	2.	형식

		switch( 정수형 변수 )	//	char, enum 도 가능.
		{
			case 정수:
				break;

			case 정수:
				break;

			default :
				break;
		
		}


		-	case 정수 :

			-	정수형 변수에 해당하는 값을 실행.

			-	case문의 끝에 : 사용하는 것 유의.
		


		-	break

			-	반복문 뿐만 아니라 switch문을 탈출하는 용도로도 쓰인다.

			-	break문이 없다면 해당 case문 이하 case문을 모두 실행하되 다음 break문을 만나는 시점에서 
	
				switch를 탈출한다.


		-	default

			-	case 문에 정의 된 조건에 해당하는 값이 아닌 모든 경우에 실행.
			
			-	if ~ else의 else와 유사하며 불필요한 경우 생략 가능.

*/
//=========================================================
public class SwitchTest : MonoBehaviour
{
    //----------------------
    public enum eSTATE { Idle, Walk, Chase, Attack, Dead };
    public eSTATE _eState = eSTATE.Idle;
    //----------------------
    void OnMouseDown()
    {
        switch (_eState)
        {
            case eSTATE.Dead:
                print("state is Dead.");
                break;

            case eSTATE.Chase:
                print("state is Chase.");
                break;

            case eSTATE.Attack:
                print("state is Attack.");
                break;

            case eSTATE.Idle:
                print("state is Idle.");
                break;

            default:
                print("and so on.");
                break;
        }
    }
}
//=========================================================