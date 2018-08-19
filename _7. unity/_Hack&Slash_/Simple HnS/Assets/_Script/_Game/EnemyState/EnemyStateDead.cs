//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class EnemyStateDead : FSMSingleton<EnemyStateDead>, IFSMState<EnemyStateManager>
{
	//---------------------------------
	EnemyStateManager _e;
	//---------------------------------
	public void Enter(EnemyStateManager e)
	{
		_e = e;
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.KNOCKDOWN);

        print("--- EnemyStateDead ---");
        //Invoke ("Clear", 2f);
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

}
//==========================================================