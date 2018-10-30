//===================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
//===================================================
//----------------------------------
//  RequireComponent
//  -   특정 컴포넌트가 최소 1개는 Attach되어 있어야 한다고 선언.
//  -   이미 붙어 있으면 아무 일도 안함.
//  -   지정된 컴포넌트를 지우려고 하면 에러 메시지 연출.
[RequireComponent(typeof(Animator))]
//----------------------------------
//  DisallowMultipleComponent
//  -   하나의 게임오브젝트에 중복된 컴포넌트를 attach 하는것을 금지.
//  -   상속 받은 자식 클래스에도 적용됨.
[DisallowMultipleComponent]
//----------------------------------
public class AttributeTest_1 : MonoBehaviour {

    //------------------
    //  Range
    [Header("----- Range -----")]
    [Tooltip("num1")]
    [Range(1, 10)]
    public int num1;
    [Range(1, 10)]
    public float num2;
    [Range(1, 10)]
    public long num3;
    [Range(1, 10)]
    public double num4;
    //------------------
    /*
        Multiline 
        
        TextArea
        -   Multiline과 큰 차이 없음.
        -   폭에 맞춰 자동적으로 줄바꿈 표시.
            스크롤 바 표시.
        -   추천.
    */
    [Space(20)]
    [Header("----- Multiline / TextArea -----")]
    [Multiline(5)]
    public string multiline;
    [TextArea(3, 5)]
    public string textArea;
    //------------------
    //  ContextMenuItem
    //  -   인스펙터에 노출된 변수에 컨텍스트 메뉴 추가.
    //  -   스크립트의 멤버변수에 리셋 기능 적용에 좋을 듯.
    [Space(20)]
    [Header("----- ContextMenuItem -----")]
    [ContextMenuItem("Random", "RandomNumber")]
    [ContextMenuItem("Reset", "ResetNumber")]
    public int number;
    void RandomNumber() { number = Random.Range(0, 100); }
    void ResetNumber() { number = 0; }
    //------------------
    //  ColorUsage
    //  -   색의 변경을 위한 컬러 픽커를 사용함.
    //      알파값 사용/미사용, HDR 용 등으로 설정.
    [Space(20)]
    [Header("----- ColorUsage -----")]
    public Color color1;
    [ColorUsage(false)]
    public Color color2;
    [ColorUsage(true, true, 0, 8, 0.125f, 3)]
    public Color color3;
    //------------------
    

    // Use this for initialization
    void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
//===================================================