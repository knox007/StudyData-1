using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerStateStraightPunch : FSMSingleton<PlayerStateStraightPunch>, IFSMState<PlayerStateManager>
{
    public void Enter(PlayerStateManager e)
    {
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.STRAIGHTPUNCH);

        //StartCoroutine(e.CheckAnimationState("Base Layer.Straight Punch", PlayerStateIdle.Instance));
    }
    public void Execute(PlayerStateManager e)
    {
		if(e._myAnimator.GetCurrentAnimatorStateInfo(0).IsName(GlobalPlayerInfo.Instance._aniNameList [(int)CharProper.eANIMSTATE.STRAIGHTPUNCH]) &&
			e._myAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime > 0.99f )
            e.ChangeState(PlayerStateIdle.Instance);
        
    }
    public void Exit(PlayerStateManager e)
    {
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.IDLE);
    }
    public void Skip(PlayerStateManager e)
    {

    }
}
