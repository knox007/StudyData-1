//=================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=================================================================
public class Mole8 : MonoBehaviour
{
    //-----------------------
    //  두더지 상태 선언.
    public enum eMOLESTATE
    {
        NONE,
        OPEN,
        IDLE,
        CLOSE,
        CATCH
    }
    public eMOLESTATE _eMoleState = eMOLESTATE.NONE;
    //-----------------------
    //  애니메이션 이지미들 묶음.
    public Texture[] _imageOpen;
    public Texture[] _imageIdle;
    public Texture[] _imageClose;
    public Texture[] _imageCatch;
    //-----------------------
    //  애니메이션을 교체할 시간.
    public float _animationTime;
    //  애니메이션 시간을 측정하기 위한 변수.
    public float _currentAniTime;
    //-----------------------
    //  현재 애니메이션이 몇번째인지 관리하기 위한 변수.
    int _animationIndex;
    //-----------------------
    //  해당 게임오브젝트의 렌더러와 메터리얼.
    Renderer _myRenderer;
    Material _myMaterial;
    //-----------------------
    //  오디오 소스.
    public AudioSource _audioSrc;
    //  오디오 클립.
    public AudioClip _aclipOpen;    //  등장 효과음.
    public AudioClip _aclipCatch;   //  두더지 피격 효과음.
    //-----------------------
    //  착한 두더지인지 체크.
    public bool _isGoodMole;
    //  착한 두더지 등장 확률.
    public int _goodMoleRate = 15;

    //  착한 두더지 애니메이션 이지미들 묶음.
    public Texture[] _imageOpen2;
    public Texture[] _imageIdle2;
    public Texture[] _imageClose2;
    public Texture[] _imageCatch2;
    //-----------------------
    //  게임 매니져에 접근하기 위한 변수.
    public GameManager2 _gameManager;
    //-----------------------
    private void Awake()
    {
        _myRenderer = GetComponent<Renderer>();
        _myMaterial = _myRenderer.material;
    }
    //-----------------------
    //  
    public void Open_On()
    {
        _eMoleState = eMOLESTATE.OPEN;
        _animationIndex = 0;
        _audioSrc.clip = _aclipOpen;
        _audioSrc.Play();

        int value = Random.Range(0, 100);

        if (value <= _goodMoleRate)
            _isGoodMole = true;
        else
            _isGoodMole = false;

        if (_gameManager._eGameState == GameManager2.eGAMESTATE.READY)
            _gameManager.Go();
    }
    //-----------------------
    public void Open_Ing()
    {
        if(_isGoodMole == false)
            _myMaterial.mainTexture = _imageOpen[_animationIndex];
        else
            _myMaterial.mainTexture = _imageOpen2[_animationIndex];
        ++_animationIndex;

        if (_animationIndex >= _imageOpen.Length)
            Idle_On();
    }
    //-----------------------
    public void Idle_On()
    {
        _eMoleState = eMOLESTATE.IDLE;
        _animationIndex = 0;
    }
    //-----------------------
    public void Idle_Ing()
    {        
        if (_isGoodMole == false)
            _myMaterial.mainTexture = _imageIdle[_animationIndex];
        else
            _myMaterial.mainTexture = _imageIdle2[_animationIndex];
        ++_animationIndex;

        if (_animationIndex >= _imageIdle.Length)
            Close_On();
    }
    //-----------------------
    public void Close_On()
    {
        _eMoleState = eMOLESTATE.CLOSE;
        _animationIndex = 0;
    }
    //-----------------------
    public void Close_Ing()
    {
        if (_isGoodMole == false)
            _myMaterial.mainTexture = _imageClose[_animationIndex];
        else
            _myMaterial.mainTexture = _imageClose2[_animationIndex];
        ++_animationIndex;

        if (_animationIndex >= _imageClose.Length)
        {
            _eMoleState = eMOLESTATE.NONE;
            _animationIndex = 0;

            StartCoroutine(Wait());
        }
    }
    //-----------------------
    public void Catch_On()
    {
        _eMoleState = eMOLESTATE.CATCH;
        _animationIndex = 0;
        _audioSrc.clip = _aclipCatch;
        _audioSrc.Play();

        if (_isGoodMole)
            ++_gameManager._hitCount_Good;
        else
            ++_gameManager._hitCount_Bad;
    }
    //-----------------------
    public void Catch_Ing()
    {
        if (_isGoodMole == false)
            _myMaterial.mainTexture = _imageCatch[_animationIndex];
        else
            _myMaterial.mainTexture = _imageCatch2[_animationIndex];
        ++_animationIndex;

        if (_animationIndex >= _imageCatch.Length)
        {
            _eMoleState = eMOLESTATE.NONE;
            _animationIndex = 0;

            StartCoroutine(Wait());
        }
    }
    //-----------------------
    public IEnumerator Wait()
    {
        //  0.5~4.5사이 랜덤값 반환.
        float waitTime = Random.Range(0.5f, 4.5f);

        //  waitTime 시간(초)만큼 대기.
        yield return new WaitForSeconds(waitTime);

        //  Open 시작.
        Open_On();
        
        //* 1)  게임 상태 갱신 - 시작.
        if (_gameManager._eGameState == GameManager2.eGAMESTATE.READY)
            _gameManager.Go();
        //*/
    }
    //-----------------------
    private void Update()
    {
        if (_currentAniTime >= _animationTime)
        {
            switch (_eMoleState)
            {
                case eMOLESTATE.OPEN:
                    Open_Ing();
                    break;

                case eMOLESTATE.IDLE:
                    Idle_Ing();
                    break;

                case eMOLESTATE.CLOSE:
                    Close_Ing();
                    break;

                case eMOLESTATE.CATCH:
                    Catch_Ing();
                    break;

            }// switch(_eMoleState)

            _currentAniTime = 0f;

        }// if( _currentAniTime >= _animationTime )
        else
            _currentAniTime += Time.deltaTime;

    }// private void Update()
    //-----------------------
    private void OnMouseDown()
    {
        //  마우스 터치 이벤트 발동.
        switch (_eMoleState)
        {
            //  등장 또는 대기중인 상태.
            case eMOLESTATE.IDLE:
            case eMOLESTATE.OPEN:
                Catch_On();
                break;
        }
    }
    //-----------------------

}// public class Mole8 : MonoBehaviour
 //=================================================================