//=====================================================
/*
	public static float GetAxisRaw (string axisName); 
        
    	-   버튼 입력에 따라 -1.0 ~ 1.0 의 값을 반환.

			-	0.05씩 증감.

			-	버튼 업시 0으로 복귀.

		-   입력 없으면 0.
*/
//=====================================================
using UnityEngine;
using System.Collections;
using UnityEngine.UI;
//=====================================================
public class AxisExample : MonoBehaviour
{
    public float range;
    public Text _axisState;


    void Update()
    {
        float h = Input.GetAxis("Horizontal");
        float xPos = h * range;

        transform.position = new Vector3(xPos, 2f, 0);
		_axisState.text = "Value Returned: " + h.ToString("F2");
    }
}
//=====================================================