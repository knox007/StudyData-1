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
		e._myAnimator.SetInteger("act", 2);
		
		float xPos = Random.Range (e._minOffset.x, e._maxOffset.x);
		float yPos = 0f;
		float zPos = Random.Range (e._minOffset.y, e._maxOffset.y);

		e._moveTargetPos = new Vector3 (xPos, yPos, zPos);
	
	}//	public void Enter(EnemyStateManager e)
	//---------------------------------
	public void Execute(EnemyStateManager e)
	{
		e._myTransf.rotation = Quaternion.Slerp(e._myTransf.rotation, Quaternion.LookRotation(e._moveTargetPos - e._myTransf.position), e._property._rotSpeed * Time.deltaTime);

		e._myTransf.position += e.transform.forward * e._property._moveSpeed * Time.deltaTime;

		if (Vector3.Distance (e._myTransf.position, e._moveTargetPos) <= e._property._validMoveOffset)
		{
			e.RepeatCurState ();
		}

	}
	//---------------------------------
	public void Exit(EnemyStateManager e)
	{
	}
	//---------------------------------
	public void Skip(EnemyStateManager e) { }
    //---------------------------------

}// public class EnemyStatePatrol : FSMSingleton<EnemyStatePatrol>, IFSMState<EnemyStateManager>
//==========================================================