//==============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==============================================================
public class FBCManager5 : MonoBehaviour
{
    //----------------------------
    public UIManager4 _uiManager;
    //----------------------------
    public int _count;      //  낙하하는 박스 갯수 파악.
    public float _time;     //  박스가 떨어지기까지 걸리는 시간 파악.
    bool _isEnd;            //  박스가 다 떨어졌는지 확인.
    //----------------------------
    private void Start()
    {
        //  초기화.
        _count = 0;
        _isEnd = false;
        _time = 0f;
    }
    //----------------------------
    private void OnTriggerEnter(Collider other)
    {
        //  충돌한 오브젝트의 태그를 확인한다.
        if( other.gameObject.CompareTag("FBC"))
            ++_count;

        //  플레이어가 떨어지면 실패로 처리한다.
        if (other.gameObject.CompareTag("Player") && _isEnd == false)
        {
            _isEnd = true;
            _uiManager._textFailed.gameObject.SetActive(true);
            _uiManager._imageBG.gameObject.SetActive(true);
            _uiManager._buttonReplay.gameObject.SetActive(true);
        }


        //  16개 이상 떨어지면 박스가 다 떨어진것으로 한다.
        //  이 경우, 게임 성공으로 처리한다.
        if (_count >= 16)
        {
            _isEnd = true;
            _uiManager._textClear.gameObject.SetActive(true);
            _uiManager._imageBG.gameObject.SetActive(true);
            _uiManager._buttonReplay.gameObject.SetActive(true);
        }
    }
    //----------------------------
    private void Update()
    {
        //  박스가 다 떨어지지 않은 상태라면 경과시간을 누적한다.
        if (_isEnd==false)
            _time += Time.deltaTime;

        _uiManager._textTime.text = _time.ToString();
    }
    //----------------------------


}// public class FBCManager : MonoBehaviour
 //==============================================================