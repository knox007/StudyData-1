/*
    GetComponent

    -   게임오브젝트에 등록된 컴포넌트에 접근하기 위한 함수.

    -   원형
    
        -   public Component GetComponent (Type type)

    -   해당 스크립트가 적용된 게임오브젝트내의 컴포넌트 접근

        -   GetComponent<Type>()

        다른 게임오브젝트의 컴포넌트에 접근

        -   해당 게임 오브젝트 객체.GetComponent<Type>()
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExampleBehaviourScript : MonoBehaviour {

	Renderer _renderer;
	Material _material;
	void Start()
	{
		_renderer = GetComponent<Renderer> ();
		_material = _renderer.material;

	}

	void Update()
	{
		if (Input.GetKeyDown(KeyCode.R))
			_material.color = Color.red;
		
		if (Input.GetKeyDown(KeyCode.G))
			_material.color = Color.green;
		
		if (Input.GetKeyDown(KeyCode.B))
			_material.color = Color.blue;
	}
}
