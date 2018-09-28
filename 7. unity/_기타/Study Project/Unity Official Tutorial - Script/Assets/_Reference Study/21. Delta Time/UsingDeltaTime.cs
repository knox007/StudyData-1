//================================================
/*
	Time.deltaTime

	-	현재 프레임과 이전 프레임 사이의 경과 시간.

	-	Update함수안에서 

		transform.position -= new Vector3(speed * Time.deltaTime, 0.0f, 0.0f);
									vs
		transform.position -= new Vector3(speed, 0.0f, 0.0f);

		차이는?
*/
//================================================
using UnityEngine;
using System.Collections;
//================================================
public class UsingDeltaTime : MonoBehaviour
{
	//-------------------------
	public float speed = 8f; 
	public float countdown = 3.0f;
	public bool _useTimeDelta = true;
	//-------------------------
	Light _light;
	//-------------------------
	void Start()
	{
		_light = GetComponent<Light> ();
		_light.enabled = false;
	}
	//-------------------------
	void Update ()
	{
		countdown -= Time.deltaTime;
		if(countdown <= 0.0f)
			_light.enabled = true;

		if (_light.enabled == true)
		{
			if (_useTimeDelta) {
				if (Input.GetKey (KeyCode.RightArrow))
					transform.position += new Vector3 (speed * Time.deltaTime, 0.0f, 0.0f);
				if (Input.GetKey (KeyCode.LeftArrow))
					transform.position -= new Vector3 (speed * Time.deltaTime, 0.0f, 0.0f);	
			}
			else
			{
				if(Input.GetKey(KeyCode.RightArrow))
					transform.position += new Vector3(speed, 0.0f, 0.0f);
				if(Input.GetKey(KeyCode.LeftArrow))
					transform.position -= new Vector3(speed, 0.0f, 0.0f);	
			}
		}

	}//	void Update ()
	//-------------------------
}
//================================================