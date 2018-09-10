//====================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//====================================================================
public class PlayerStateAttack : FSMSingleton<PlayerStateAttack>, IFSMState<PlayerStateManager>
{
	//---------------------------------
	public void Enter(PlayerStateManager e)
	{
		//	1.	Set Attack Random Idx
		int attackIdxMin = (int)CharProper.eANIMSTATE.STRAIGHTPUNCH;
		int attackIdxMax = (int)CharProper.eANIMSTATE.UPPERRIGHT + 1;
		e._curAttackIdx = Random.Range(attackIdxMin, attackIdxMax);
	
		//	2.	Apply Idx
		e._myAnimator.SetInteger("act", e._curAttackIdx);
		print ("--- PlayerStateAttack ---");
	}
	//---------------------------------
	public void Execute(PlayerStateManager e)
	{
        //	4.	Repeat Current State
        if (e._gameStateManager._selectedEnemy.CurrentState == EnemyStateDead.Instance)
            e.ChangeState(PlayerStateIdle.Instance);
        else
        {
            //	3. 	Check if Animation is over
            if (e._myAnimator.GetCurrentAnimatorStateInfo(0).IsName(GlobalPlayerInfo.Instance._aniNameList[(int)e._curAttackIdx]) &&
                (e._myAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime % 1f) > 0.9f)
            {
                if (e._gameStateManager._selectedEnemy != null && e._gameStateManager._selectedEnemy.CurrentState != EnemyStateDead.Instance)
                    e._gameStateManager._selectedEnemy.ChangeState(EnemyStateGotDamage.Instance);

                e.RepeatCurState();
            }

        }// ~if (e._gameStateManager._selectedEnemy.CurrentState == EnemyStateDead.Instance)

    }// public void Execute(PlayerStateManager e)
	//---------------------------------
	public void Exit(PlayerStateManager e)
	{ 
	}
	//---------------------------------
	public void Skip(PlayerStateManager e) { }
	//---------------------------------

}//	public class PlayerStateAttack : FSMSingleton<PlayerStateAttack>, IFSMState<PlayerStateManager>
//====================================================================