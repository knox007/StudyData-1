//========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;   //  UI관련 기능을 사용하기 위한 네임스페이스.
//========================================================
public class UIManager3 : MonoBehaviour
{
    //---------------------
    public Text _textTime;      //  경과시간을 연출하는 텍스트UI.
    public Text _textClear;     //  성공 텍스트.
    public Text _textFailed;    //  실패 텍스트.
    public Image _imageBG;      //  결과 텍스트의 배경으로 사용될 이미지.
    //---------------------
    private void Start()
    {
        //  처음 시작할때는 메시지를 보여줄 필요가 없다.
        _textClear.gameObject.SetActive(false);
        _textFailed.gameObject.SetActive(false);
        _imageBG.gameObject.SetActive(false);
    }
    //---------------------

}// public class UIManager2 : MonoBehaviour
 //========================================================