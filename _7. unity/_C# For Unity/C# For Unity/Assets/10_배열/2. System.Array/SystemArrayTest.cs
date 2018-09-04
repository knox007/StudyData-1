/*
	1.	System.Array

		-	모든 C# 배열은 내부적으로 .NET Framework의 System.Array에서 파생

		-	상속에 의해 System.Array의 메소드, 프로퍼티 사용 가능.

	2.	주요 메소드 및 프로퍼티

		분류		|	이름			|	설명
	-----------------------------------------------------------------------------------------------------------------
	정적 메소드		|	Sort()			|	정렬
					|	IndexOf()		|	찾고자 하는 특정 데이터의 인덱스 반환.
					|	TrueForAll()	|	배열의 모든 요소가 지정한 조건에 부합하는지의 여부 반환.
					|	BinarySearch()	|	이진 탐색.
					|	FindIndex()		|	지정한 조건에 부합하는 첫번째 요소 반환.
					|	Resize()		|	배열 크기 수정.
					|	Clear()			|	배열 요소 초기화
					|					|	숫자 형식 : 0
					|					|	논리 형식 : false
					|					|	참조 형식 : null
					|	ForEach()		|	모든 요소에 대해 동일한 작업 수행.
	-----------------------------------------------------------------------------------------------------------------
	인스턴스 메소드	|	GetLength()		|	지정한 차원의 길이 반환.
	-----------------------------------------------------------------------------------------------------------------
	프로퍼티		|	Length			|	배열의 길이 반환
					|	Rank			|	배열의 차원 반환


*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using System;

public class SystemArrayTest : MonoBehaviour {

	//--------------------------------
	bool Check( int score )
	{
		if (score >= 40)
			return true;
		else
			return false;
	}
	//--------------------------------
	void Print(int value )
	{
		print (value);
	}
	//--------------------------------
	void Start ()
	{
		int[] scores = { 60, 80, 20, 100, 40 };

		print ("----------- 조회 -------------");
		foreach (int score in scores)
			print (score);

		print ("----------- 정렬 -------------");
		Array.Sort(scores);
		Array.ForEach<int> (scores, new Action<int> (Print));	//	Action 대리자는 추후 설명.

		print ("----------- 검색 -------------");
		print ("80 is at " + Array.BinarySearch<int> (scores, 80));

		print ("----------- 인덱싱 -------------");
		print ("80 is at " + Array.IndexOf(scores, 80));

		print ("----------- 조건 검사 -------------");
		print ("전부 합격 ? : " + Array.TrueForAll<int> (scores, Check));

		print ("----------- 인덱스 찾기 -------------");
		int index = Array.FindIndex<int>
			( scores, delegate (int score) 		//	익명 메소드는 추후 설명.
			{
					if (score < 40)
						return true;
					else
						return false;				
			});
		scores [index] = 45;

		print ("----------- 조건 검사 -------------");
		print ("전부 합격 ? : " + Array.TrueForAll<int> (scores, Check));


		print ("----------- 배열 길이 -------------");
		print ("배열 길이 : " + scores.Length);


		print ("----------- 배열 길이 수정. -------------");
		Array.Resize (ref scores, 10);
		print ("배열 길이 : " + scores.Length);

		print ("----------- 조회 2 -------------");
		Array.ForEach<int> (scores, new Action<int> (Print));		//	Action 대리자는 추후 설명.

		print ("----------- 초기화 -------------");
		Array.Clear (scores, 3, 7);

		print ("----------- 조회 2 -------------");
		Array.ForEach<int> (scores, new Action<int> (Print));		//	Action 대리자는 추후 설명.
		
		
	}
	//--------------------------------
}
