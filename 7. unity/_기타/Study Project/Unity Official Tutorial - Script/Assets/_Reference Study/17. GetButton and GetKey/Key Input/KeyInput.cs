//=====================================================
/*
    KeyCode

    -   https://docs.unity3d.com/kr/current/ScriptReference/KeyCode.html

 */
//=====================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
//=====================================================
public class KeyInput : MonoBehaviour
{
    public Text _keyState;

	void Update ()
    {
        //  public static bool GetKeyDown (KeyCode key); 
        bool down = Input.GetKeyDown(KeyCode.Space);
        bool held = Input.GetKey(KeyCode.Space);
        bool up = Input.GetKeyUp(KeyCode.Space);

        if (down)
        {
            _keyState.text = "Key Down";
            _keyState.color = Color.blue;
            _keyState.rectTransform.localPosition = Vector3.up * 50;
        }
        else if (held)
        {
            _keyState.text = "Key Held";
            _keyState.color = Color.yellow;
            _keyState.rectTransform.localPosition = Vector3.right * 50;

        }
        else if (up)
        {
            _keyState.text = "Key Up";
            _keyState.color = Color.red;
            _keyState.rectTransform.localPosition = Vector3.down * 50;
        }
        else
        {
            _keyState.text = "No Event";
            _keyState.color = Color.white;
            _keyState.rectTransform.localPosition = Vector3.zero;
        }

    }// void Update ()

}// public class KeyInput : MonoBehaviour
//=====================================================