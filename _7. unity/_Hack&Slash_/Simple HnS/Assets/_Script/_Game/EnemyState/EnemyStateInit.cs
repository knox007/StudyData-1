//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class EnemyStateInit : FSMSingleton<EnemyStateInit>, IFSMState<EnemyStateManager>
{
    //---------------------------------
    public void Enter(EnemyStateManager e)
    {
		e._myAnimator.SetInteger("act", 0);
		e.ChangeState (EnemyStatePatrol.Instance);
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