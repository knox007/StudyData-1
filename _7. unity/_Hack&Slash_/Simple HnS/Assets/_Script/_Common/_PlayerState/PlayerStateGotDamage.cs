//====================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//====================================================================
public class PlayerStateGotDamage : FSMSingleton<PlayerStateGotDamage>, IFSMState<PlayerStateManager>
{
	//---------------------------------
	public void Enter(PlayerStateManager e)
	{
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.GETDAMAGE);
		print ("--- PlayerStateGotDamage ---");

        --e._property._hp;

        if (e._property._hp <= 0)
            e.ChangeState(PlayerStateDead.Instance);
    }
	//---------------------------------
	public void Execute(PlayerStateManager e)
	{   
        if (e._myAnimator.GetCurrentAnimatorStateInfo(0).IsName(GlobalPlayerInfo.Instance._aniNameList[(int)CharProper.eANIMSTATE.GETDAMAGE]) &&
            (e._myAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime % 1f) > 0.9f)
            e.ChangeState(PlayerStateIdle.Instance);

    }//	public void Execute(PlayerStateManager e)
	//---------------------------------
	public void Exit(PlayerStateManager e)
	{ 
	}
	//---------------------------------
	public void Skip(PlayerStateManager e) { }
	//---------------------------------

}//	public class PlayerStateGotDamage : FSMSingleton<PlayerStateGotDamage>, IFSMState<PlayerStateManager>
//====================================================================