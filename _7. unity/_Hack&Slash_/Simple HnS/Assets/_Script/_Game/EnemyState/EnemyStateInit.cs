﻿//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class EnemyStateInit : FSMSingleton<EnemyStateInit>, IFSMState<EnemyStateManager>
{
    //---------------------------------
    public void Enter(EnemyStateManager e)
    {
		e._property = e._originProperty;
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.IDLE);
		e.ChangeState (EnemyStatePatrol.Instance);

        print("--- EnemyStateInit ---");
    }
    //---------------------------------
    public void Execute(EnemyStateManager e)
    {
		
    }
    //---------------------------------
    public void Exit(EnemyStateManager e)
    {
    }
    //---------------------------------
    public void Skip(EnemyStateManager e) { }
    //---------------------------------

}// public class EnemyStateInit : FSMSingleton<EnemyStateInit>, IFSMState<EnemyStateManager>
 //==========================================================