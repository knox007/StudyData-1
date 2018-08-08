//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class EnemyStateInit : FSMSingleton<EnemyStateInit>, IFSMState<EnemyStateManager>
{
    //---------------------------------
    readonly float autoDeadTime = 2f;    
    //---------------------------------
    public void Enter(EnemyStateManager e)
    {
        e._curTime = 0f;
    }
    //---------------------------------
    public void Execute(EnemyStateManager e)
    {
        e._curTime += Time.deltaTime;

        if(e._curTime > autoDeadTime )
        {
            e._curTime = 0f;
            e.ChangeState(EnemyStateDestroy.Instance);
        }
            
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