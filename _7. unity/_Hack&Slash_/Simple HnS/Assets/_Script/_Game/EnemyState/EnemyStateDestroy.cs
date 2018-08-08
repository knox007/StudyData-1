//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class EnemyStateDestroy : FSMSingleton<EnemyStateDestroy>, IFSMState<EnemyStateManager>
{
    public void Enter(EnemyStateManager e)
    {
        e.gameObject.DestroyAPS();
    }
    //---------------------------------
    public void Execute(EnemyStateManager e) { }
    //---------------------------------
    public void Exit(EnemyStateManager e) { }
    //---------------------------------
    public void Skip(EnemyStateManager e) { }
    //---------------------------------

}// public class EnemyStateDestroy : FSMSingleton<EnemyStateDestroy>, IFSMState<EnemyStateManager>
 //==========================================================