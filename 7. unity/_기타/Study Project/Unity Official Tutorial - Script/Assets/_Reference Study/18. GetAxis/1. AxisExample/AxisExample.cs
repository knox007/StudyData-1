//=====================================================
/*
    Edit - ProjectSetting - Input
*/
//=====================================================
using UnityEngine;
using System.Collections;
using UnityEngine.UI;
//=====================================================
public class AxisExample : MonoBehaviour
{
    public float range;
    public Text textOutput;


    void Update()
    {
        /*  public static float GetAxis (string axisName); 
        
            -   키 입력에 따라 -1.0 ~ 1.0 의 값을 반환.

            -   입력 없으면 0.

        */
        float h = Input.GetAxis("Horizontal");
        float xPos = h * range;

        transform.position = new Vector3(xPos, 2f, 0);
        textOutput.text = "Value Returned: " + h.ToString("F2");
    }
}
//=====================================================