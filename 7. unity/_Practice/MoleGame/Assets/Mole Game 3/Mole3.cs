//=================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=================================================================
public class Mole3 : MonoBehaviour
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
    //  해당 게임오브젝트의 렌더러.
    Renderer _myRenderer;
    Material _myMaterial;
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
    }
    //-----------------------
    public void Open_Ing()
    {
        _myMaterial.mainTexture = _imageOpen[_animationIndex];
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
        _myMaterial.mainTexture = _imageIdle[_animationIndex];
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
        _myMaterial.mainTexture = _imageClose[_animationIndex];
        ++_animationIndex;

        if (_animationIndex >= _imageClose.Length)
        {
            _eMoleState = eMOLESTATE.NONE;
            _animationIndex = 0;
        }
    }
    //-----------------------
    public void Catch_On()
    {
        _eMoleState = eMOLESTATE.CATCH;
        _animationIndex = 0;
    }
    //-----------------------
    public void Catch_Ing()
    {
        _myMaterial.mainTexture = _imageCatch[_animationIndex];
        ++_animationIndex;

        if (_animationIndex >= _imageCatch.Length)
        {
            _eMoleState = eMOLESTATE.NONE;
            _animationIndex = 0;
        }
    }
    //-----------------------

}// public class Mole1 : MonoBehaviour
 //=================================================================