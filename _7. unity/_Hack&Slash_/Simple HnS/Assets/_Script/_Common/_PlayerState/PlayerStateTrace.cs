//====================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//====================================================================
public class PlayerStateTrace : FSMSingleton<PlayerStateTrace>, IFSMState<PlayerStateManager>
{
	//---------------------------------
	public void Enter(PlayerStateManager e)
	{
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.MOVEFORWARD);
	}
	//---------------------------------
	public void Execute(PlayerStateManager e)
	{
		float distToEnemy = Vector3.Distance (e._myTransf.position, e._gameStateManager._selectedEnemy.transform.position);

		if (distToEnemy >= e._property._attackTargetDistOffset)
			e.ChangeState (PlayerStateIdle.Instance);
		else
		{
			if (distToEnemy > e._property._stopToAttackDist) {
				e._myTransf.rotation = Quaternion.Slerp (
					e._myTransf.rotation, 
					Quaternion.LookRotation (e._gameStateManager._selectedEnemy.transform.position - e._myTransf.position),
					e._property._rotSpeed * Time.deltaTime
				);

				e._myTransf.position += e.transform.forward * e._property._moveSpeed * Time.deltaTime;
			
			}//	if (distToEnemy > e._property._stopToAttackDist)
			else
				e.ChangeState (PlayerStateAttack.Instance);
			
		}//	if (distToEnemy >= e._property._attackTargetDistOffset)

	}// public void Execute(PlayerStateManager e)
	//---------------------------------
	public void Exit(PlayerStateManager e)
	{
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.IDLE);
	}
	//---------------------------------
	public void Skip(PlayerStateManager e) { }
	//---------------------------------

}//	public class PlayerStateTrace : FSMSingleton<PlayerStateTrace>, IFSMState<PlayerStateManager>
//====================================================================