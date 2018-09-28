//=====================================================
/*
    Edit - ProjectSetting - Input
*/
//=====================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
//=====================================================
public class ButtonInput : MonoBehaviour
{
    public Text _buttonState;

    void Update()
    {
        //  public static bool GetButtonDown(string buttonName);
        bool down = Input.GetButtonDown("Jump");
        bool held = Input.GetButton("Jump");
        bool up = Input.GetButtonUp("Jump");

        if (down)
        {
            _buttonState.text = "Jump Down";
            _buttonState.color = Color.blue;
            _buttonState.rectTransform.localPosition = Vector3.up * 50;
        }
        else if (held)
        {
            _buttonState.text = "Jump Held";
            _buttonState.color = Color.yellow;
            _buttonState.rectTransform.localPosition = Vector3.right * 50;

        }
        else if (up)
        {
            _buttonState.text = "Jump Up";
            _buttonState.color = Color.red;
            _buttonState.rectTransform.localPosition = Vector3.down * 50;
        }
        else
        {
            _buttonState.text = "No Event";
            _buttonState.color = Color.white;
            _buttonState.rectTransform.localPosition = Vector3.zero;
        }

    }// void Update()

}// public class ButtonInput : MonoBehaviour
//=====================================================