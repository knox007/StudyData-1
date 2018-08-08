//====================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//====================================================================
public class EnemyStateManager : FSM<EnemyStateManager>
{
    //---------------------------------
    public CharProper _property;
    [HideInInspector]
    public float _curTime;
    //---------------------------------
    void OnEnable ()
    {
        Initialize(this, EnemyStateInit.Instance);
	}
    //---------------------------------
    void Update ()
    {
        FSMUpdate();
	}
    //---------------------------------

}// public class EnemyStateManager : MonoBehaviour
//====================================================================