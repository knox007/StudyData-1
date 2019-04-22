//=================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=================================================================
public class Mole1 : MonoBehaviour
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

}// public class Mole1 : MonoBehaviour
 //=================================================================