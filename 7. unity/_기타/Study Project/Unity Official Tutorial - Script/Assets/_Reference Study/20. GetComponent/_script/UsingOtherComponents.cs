//=================================================
/*
	GetComponent

		-	게임 오브젝트에 연결된 컴포넌트를 리턴.

		-	스크립트를 클래스 레벨로 접근하도록 하게함.

	컴포넌트

		-	게임오브젝트에 링크되어 해당 게임 오브젝트의 

			기능이나 속성등을 정의.

		-	보통 스크립트작업(클래스 구현)을 통해 생성.

		-	모든 게임 오브젝트는 기본적으로 Transform 컴포넌트를 지님.

			-	Transform 컴포넌트는 제거 불가.
*/
//=================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=================================================
public class UsingOtherComponents : MonoBehaviour
{
	//---------------------------
	public GameObject otherGameObject;
	//---------------------------
	AnotherScript anotherScript;
	YetAnotherScript yetAnotherScript;
	BoxCollider boxCol;
	//---------------------------
	void Awake ()
	{
		anotherScript = GetComponent<AnotherScript>();
		yetAnotherScript = otherGameObject.GetComponent<YetAnotherScript>();
		boxCol = otherGameObject.GetComponent<BoxCollider>();
	}
	//---------------------------
	void Start ()
	{
		boxCol.size = new Vector3(3,3,3);
		Debug.Log("The player's score is " + anotherScript.playerScore);
		Debug.Log("The player has died " + yetAnotherScript.numberOfPlayerDeaths + " times");
	}
	//---------------------------

}//	public class UsingOtherComponents : MonoBehaviour
//=================================================