//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class EnemyStatePatrol : FSMSingleton<EnemyStatePatrol>, IFSMState<EnemyStateManager>
{
	//---------------------------------
	public void Enter(EnemyStateManager e)
	{
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.MOVEFORWARD);
		
		float xPos = Random.Range (e._minOffset.x, e._maxOffset.x);
		float yPos = 0f;
		float zPos = Random.Range (e._minOffset.y, e._maxOffset.y);

		e._moveTargetOffset = new Vector3 (xPos, yPos, zPos);

		e._moveTargetPos = e._myTransf.position + e._moveTargetOffset;
	
	}//	public void Enter(EnemyStateManager e)
	//---------------------------------
	public void Execute(EnemyStateManager e)
	{
		//	이동 목표지점 체크.
		float distTarget = Vector3.Distance (e._myTransf.position, e._moveTargetPos);

		if (distTarget > e._property._validMoveOffset)
		{
			e._myTransf.rotation = Quaternion.Slerp (e._myTransf.rotation, Quaternion.LookRotation (e._moveTargetPos - e._myTransf.position), e._property._rotSpeed * Time.deltaTime);
			e._myTransf.position += e.transform.forward * e._property._moveSpeed * Time.deltaTime;

		}//	if (Vector3.Distance (e._myTransf.position, e._moveTargetPos) > e._property._validMoveOffset)
		else
		{
			e._myTransf.position = e._moveTargetPos;
			e.RepeatCurState ();

		}//	~if (Vector3.Distance (e._myTransf.position, e._moveTargetPos) > e._property._validMoveOffset)

		//	플레이어 추적 범위 체크.
		float distPlayer = Vector3.Distance (e._myTransf.position, e._gameStateManager._myPlayer.transform.position );
		if (distPlayer <= e._property._attackTargetDistOffset)
			e.ChangeState (EnemyStateTrace.Instance);

	}//	public void Execute(EnemyStateManager e)
	//---------------------------------
	public void Exit(EnemyStateManager e)
	{
	}
	//---------------------------------
	public void Skip(EnemyStateManager e) { }
    //---------------------------------

}// public class EnemyStatePatrol : FSMSingleton<EnemyStatePatrol>, IFSMState<EnemyStateManager>
//==========================================================