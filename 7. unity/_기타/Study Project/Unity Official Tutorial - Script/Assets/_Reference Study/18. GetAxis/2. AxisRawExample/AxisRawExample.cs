//=================================================
/*
	public static float GetAxis (string axisName); 

		-   버튼 입력에 따라 -1.0 ~ 1.0 의 값을 반환.

			-	입력 즉시 변환. 증감단계값 없음.

			-	버튼 업시 0으로 복귀.

		-   입력 없으면 0.
*/
//=================================================
using UnityEngine;
using UnityEngine.UI;
using System.Collections;
//=================================================
public class AxisRawExample : MonoBehaviour
{
	public float range;
	public Text _axisRawState;


	void Update () 
	{
		float h = Input.GetAxisRaw("Horizontal");
		float xPos = h * range;

		transform.localPosition = new Vector3(xPos, 2f, 0);
		_axisRawState.text = "Value Returned: "+h.ToString("F2");
	}
}
//=================================================