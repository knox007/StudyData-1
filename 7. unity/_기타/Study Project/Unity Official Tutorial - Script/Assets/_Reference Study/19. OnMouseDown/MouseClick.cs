//======================================================
using UnityEngine;
using System.Collections;
//======================================================
public class MouseClick : MonoBehaviour
{
	//--------------------
	public Rigidbody _rigidBody;
	public Renderer _renderer;
	//--------------------
	//	Left 마우스버튼이 충돌체에 클릭될때마다 호출.
	void OnMouseDown ()
	{
		/*
		print ("-- OnMouseDown Call !! --");
		_rigidBody.AddForce(transform.forward * 500f);
		_rigidBody.useGravity = true;
		//*/
	
	}//	void OnMouseDown ()
	//--------------------
	//	Left 마우스버튼이 충돌체에 눌려지는 동안 호출.
	void OnMouseDrag()
	{
		/*
		print ("-- OnMouseDrag Call !! --");
		_renderer.material.color -= Color.white * Time.deltaTime;
		//*/
	}
	//--------------------
	//	마우스커서가 충돌체에 최초 충돌했을때 1회 호출.
	void OnMouseEnter()
	{
		/*
		print ("-- OnMouseEnter Call !! --");
		_renderer.material.color = Color.red;
		//*/
	}
	//--------------------
	//	마우스커서가 충돌체에 충돌해있는 동안 호출.
	void OnMouseOver()
	{
		/*
		print ("-- OnMouseOver Call !! --");
		_renderer.material.color -= new Color(0.1f, 0, 0) * Time.deltaTime;
		//*/
	}
	//--------------------
	//	마우스커서가 충돌체에서 벗어나는 순간 1회 호출.
	void OnMouseExit()
	{
		/*
		print ("-- OnMouseExit Call !! --");
		_renderer.material.color = Color.white;
		//*/
	}
	//--------------------
	//	Left 마우스버튼이 릴리즈되었을때 호출.
	//	충돌체 - IsTrigger,
	//	Physics.queriesHitTriggers - true인 경우 호출.
	//	Ignore Raycast layer에 속해있는 레이어인 경우 호출 되지 않음.
	//	코루틴이 될수 있음.
	//	OnMouseUpAsButton와 유사.
	void OnMouseUp()
	{
		/*
		print ("-- OnMouseUp Call !! --");
		//*/
	}
	//--------------------
	void OnMouseUpAsButton()
	{
		/*
		print ("-- OnMouseUpAsButton Call !! --");
		//*/
	}
	//--------------------


}//	public class MouseClick : MonoBehaviour
//======================================================