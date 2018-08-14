﻿//====================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//====================================================
public class EnemyStateTrace : FSMSingleton<EnemyStateTrace>, IFSMState<EnemyStateManager>
{
	//---------------------------------
	public void Enter(EnemyStateManager e)
	{
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.MOVEFORWARD);
	}
	//---------------------------------
	public void Execute(EnemyStateManager e)
	{
		float distPlayer = Vector3.Distance (e._myTransf.position, e._gameStateManager._myPlayer.transform.position );

		if (distPlayer >= e._property._attackTargetDistOffset)
			e.ChangeState (EnemyStatePatrol.Instance);
		else
		{
			//	이동 목표지점 체크.
			float distTarget = Vector3.Distance (e._myTransf.position, e._gameStateManager._myPlayer.transform.position);
			if (distTarget > e._property._stopToAttackDist)
			{
				e._myTransf.rotation = Quaternion.Slerp (e._myTransf.rotation, Quaternion.LookRotation (e._gameStateManager._myPlayer.transform.position - e._myTransf.position), e._property._rotSpeed * Time.deltaTime);
				e._myTransf.position += e.transform.forward * e._property._moveSpeed * Time.deltaTime;

			}//	if (Vector3.Distance (e._myTransf.position, e._moveTargetPos) > e._property._validMoveOffset)
			else
				e.ChangeState (EnemyStateAttack.Instance);
		
		}//	if (distPlayer >= e._property._attackTargetDistOffset)
	
	}//	public void Execute(EnemyStateManager e)
	//---------------------------------
	public void Exit(EnemyStateManager e)
	{
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.IDLE);
	}
	//---------------------------------
	public void Skip(EnemyStateManager e) { }
	//---------------------------------

}//	public class EnemyStateTrace : FSMSingleton<EnemyStatePatrol>, IFSMState<EnemyStateManager>
//====================================================