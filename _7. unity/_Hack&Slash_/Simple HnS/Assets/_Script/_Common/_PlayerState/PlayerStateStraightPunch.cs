using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerStateStraightPunch : FSMSingleton<PlayerStateStraightPunch>, IFSMState<PlayerStateManager>
{
    public void Enter(PlayerStateManager e)
    {
        e._myAnimator.SetInteger("act", 1);

        //StartCoroutine(e.CheckAnimationState("Base Layer.Straight Punch", PlayerStateIdle.Instance));
    }
    public void Execute(PlayerStateManager e)
    {
        if(e._myAnimator.GetCurrentAnimatorStateInfo(0).IsName("Base Layer.Straight Punch") &&
            e._myAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime > 0.99f )
        {
            e.ChangeState(PlayerStateIdle.Instance);
        }
    }
    public void Exit(PlayerStateManager e)
    {
        e._myAnimator.SetInteger("act", 0);
    }
    public void Skip(PlayerStateManager e)
    {

    }
}
