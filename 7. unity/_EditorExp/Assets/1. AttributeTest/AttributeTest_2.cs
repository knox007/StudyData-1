//=========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Serialization;
//=========================================================
//-------------------------
//  AddComponentMenu
//  -   Component 메뉴에 메뉴 항목 추가.
//  -   스크립트는 모두 Component/Scripts 메뉴의 안에 정리
//  -   카테고리별로 정리할때 유용.
//      -   기존 Component/Scripts 메뉴 안의 메뉴는 제거됨.
[AddComponentMenu("jackie/jackietest")]
//-------------------------
//  ExecuteInEditMode
//  -   에디터에서도 게임모드처럼 실행.
//  -   호출되는 타이밍은 게임 오브젝트가 갱신되는 때.
//      씬 Asset을 더블클릭해서,
//      씬을 로드할 때에는 Awake와 Start 함수가,
//      인스펙터 등에서 컴포넌트의 변수 등을 변경하면 Update가 호출됨. 
//      또한, OnGUI 에서 설치된 GUI가 에디터의 GUI 렌더링 사이클을 돌면서 표시되는식.
[ExecuteInEditMode]
//-------------------------
public class AttributeTest_2 : MonoBehaviour
{
    //-------------------------
    //  SerializeField
    //  -   비공개 멤버변수를 에디터에만 공개.
    [SerializeField]
    //  FormerlySerializedAs
    //  -   변수명 변경시 새로운 변수명에 데이터를 유지.
    //      Seiralized된 데이터는 변수명을 경로로써 보존.
    //  -   using UnityEngine.Serialization; 추가.
    [FormerlySerializedAs("test")]
    string rrr;
    //-------------------------
    [Range(0, 10)]
    public int number;
    //-------------------------
    [ContextMenu("RandomNumber")]
    void RandomNumber()
    {
        number = Random.Range(0, 100);
    }
    [ContextMenu("ResetNumber")]
    void ResetNumber()
    {
        number = 0;
    }
    void Start () {
        print("-- Start --");
	}
	
	// Update is called once per frame
	void Update () {
        print("-- Update --");
    }
}
//=========================================================