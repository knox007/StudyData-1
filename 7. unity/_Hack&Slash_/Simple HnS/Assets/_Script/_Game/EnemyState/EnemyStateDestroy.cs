//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class EnemyStateDestroy : FSMSingleton<EnemyStateDestroy>, IFSMState<EnemyStateManager>
{
	EnemyStateManager _e;
    public void Enter(EnemyStateManager e)
    {
		_e = e;
		
        e.gameObject.DestroyAPS();

		++e._gameStateManager._myPlayer._enemyDownCount;

		if(e._gameStateManager._myPlayer._enemyDownCount >= 3)
			Invoke ("GoResultScene", 2f);

    }
    //---------------------------------
    public void Execute(EnemyStateManager e) { }
    //---------------------------------
    public void Exit(EnemyStateManager e) { }
    //---------------------------------
    public void Skip(EnemyStateManager e) { }
    //---------------------------------
	public void GoResultScene()
	{
		_e._gameStateManager._sceneLoader.OnLoad ();
	}
	//---------------------------------

}// public class EnemyStateDestroy : FSMSingleton<EnemyStateDestroy>, IFSMState<EnemyStateManager>
 //==========================================================