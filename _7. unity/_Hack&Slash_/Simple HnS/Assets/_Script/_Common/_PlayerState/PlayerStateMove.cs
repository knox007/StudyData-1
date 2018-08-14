//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class PlayerStateMove : FSMSingleton<PlayerStateMove>, IFSMState<PlayerStateManager>
{
    //---------------------------------
    Quaternion newRot;
    //---------------------------------
    public void Enter(PlayerStateManager e)
	{
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.MOVEFORWARD);
	}
    //---------------------------------
    public void Execute(PlayerStateManager e)
    {
		if (Vector3.Distance (e._myTransf.position, e._clickedPoint) > e._property._validMoveOffset)
		{
			e._myTransf.rotation = Quaternion.Slerp (e._myTransf.rotation, Quaternion.LookRotation (e._clickedPoint - e._myTransf.position), e._property._rotSpeed * Time.deltaTime);

			e._myTransf.position += e.transform.forward * e._property._moveSpeed * Time.deltaTime;

		}
		else
		{
			e._myTransf.position = e._clickedPoint;            

			e.ChangeState(PlayerStateIdle.Instance);
		}

    }// public void Execute(PlayerStateManager e)
    //---------------------------------
	public void Exit(PlayerStateManager e) { e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.IDLE); }
    //---------------------------------
    public void Skip(PlayerStateManager e) { }
    //---------------------------------

}// public class PlayerStateMove : FSMSingleton<PlayerStateMove>, IFSMState<PlayerStateManager>
 //==========================================================