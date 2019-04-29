//======================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//======================================================
public class GameManager2 : MonoBehaviour
{
    //--------------------------
    //  게임 상태.
    public enum eGAMESTATE
    {
        READY,
        PLAY,
        END
    }
    public eGAMESTATE _eGameState = eGAMESTATE.READY;
    //--------------------------
    //  두더지 배열.
    public Mole7[] _moles;

    //  게임 제한시간.
    public float _limitTime = 5f;

    //  착한/나쁜 두더지를 잡은 횟수.
    public int _hitCount_Good;
    public int _hitCount_Bad;

    //  사운드.
    public AudioClip _aclipReady;   //  준비.
    public AudioClip _aclipGo;      //  시작.
    public AudioClip _aclipFinish;  //  결과.

    public AudioSource _audioSrc;
    //--------------------------
    public UIManager1 _uiManager;
    //--------------------------
    private void Start()
    {
        _audioSrc.clip = _aclipReady;
        _audioSrc.Play();
    }
    //--------------------------
    public void Go()
    {
        _eGameState = eGAMESTATE.PLAY;
        _audioSrc.clip = _aclipGo;
        _audioSrc.Play();
    }
    //--------------------------
    private void Update()
    {
        if (_eGameState == eGAMESTATE.PLAY)
        {
            _limitTime -= Time.deltaTime;

            if (_limitTime <= 0f)
            {
                _limitTime = 0f;

                End();

                //  게임 종료 처리.
            }
        }
        string tmp = string.Format("{0:N2}", _limitTime);
        Debug.Log(" time : " + tmp);
        _uiManager.SetLimitTime(tmp);
    }
    //--------------------------
    void End()
    {
        _eGameState = eGAMESTATE.END;

        int finalScore = _hitCount_Bad * 100 - _hitCount_Good * 1000;
        _uiManager.ShotResult(_hitCount_Good, _hitCount_Bad, finalScore);
        _audioSrc.clip = _aclipFinish;
        _audioSrc.Play();
    }
    //--------------------------

}// public class GameManager2 : MonoBehaviour
 //======================================================