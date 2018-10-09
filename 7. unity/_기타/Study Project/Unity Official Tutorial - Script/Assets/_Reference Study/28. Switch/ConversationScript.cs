/*
	switch

	-	형식

		switch( 조건값 )
		{
			case 데이터 1:
				......
				break;


			case 데이터 2:			
				......
				break;


			case 데이터 3:
				......
				break;

			default:
				......
				break;
		}
	-	조건값은 int/enum/string 가능.

		(c/c++은 정수만(char 포함.) 가능.)

	-	break문이 없으면 다음 break를 만날때까지 모두 처리.

	-	if ~ else문과 유사.

		차이점

		-	if ~ else는 조건의 범위가 넓은 경우 유용.

		-	switch는 조건의 범위가 한가지 이거나 

			중복처리해도 무관한 경우.
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ConversationScript : MonoBehaviour {

	public enum eFOOD
	{
		APPLE,
		BANANA,
		CHOCOLATE,
		DONUT,
		GRAPE
	};

	public eFOOD _curFood;
	eFOOD _preFood;

	void Start()
	{
		_curFood = eFOOD.APPLE;
		//_curFood = (eFOOD)100;
		ShowFood (_curFood);
		_preFood = _curFood;


		//	ShowFood ("사과");
	}

	void Update()
	{
		if (_curFood != _preFood)
		{
			ShowFood (_curFood);
			_preFood = _curFood;
		}
	}

	void ShowFood( string foodName )
	{
		switch( foodName )
		{
		case "사과":
			print ("사과");
			break;

		case "딸기":
			print ("딸기");
			break;

		case "포도":
			print ("포도");
			break;

		case "복숭아":
			print ("복숭아");
			break;

		default:
			print ("과일이 아닙니다.");
			break;
		}

	}
	void ShowFood( eFOOD eFood )
	{
		switch (eFood)
		{
		case eFOOD.APPLE:
			print ("APPLE");
			break;

		case eFOOD.BANANA:
			print ("BANANA");
			break;

		case eFOOD.CHOCOLATE:
			print ("CHOCOLATE");
			break;

		case eFOOD.DONUT:
			print ("DONUT");
			break;

		case eFOOD.GRAPE:
			print ("GRAPE");
			break;

		default:
			print ("this is not food!!!!");
			break;

		}
	}
}
