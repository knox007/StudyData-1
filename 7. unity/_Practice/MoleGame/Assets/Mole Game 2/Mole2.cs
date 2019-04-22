//=================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=================================================================
public class Mole2 : MonoBehaviour
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
    public eMOLESTATE _eMoleState;
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


}// public class Mole1 : MonoBehaviour
 //=================================================================