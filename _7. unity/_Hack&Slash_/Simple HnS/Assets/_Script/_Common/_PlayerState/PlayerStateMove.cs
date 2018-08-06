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
        e._myAnimator.SetInteger("act", 2);
    }
    public void Execute(PlayerStateManager e)
    {
        e._myTransf.rotation = Quaternion.Slerp(e._myTransf.rotation, Quaternion.LookRotation(e._clickedPoint - e._myTransf.position), e._rotSpeed * Time.deltaTime);

        e._myTransf.position += e.transform.forward * e._moveSpeed * Time.deltaTime;

        if (Vector3.Distance(e._myTransf.position, e._clickedPoint) <= 0.01f)
            e.ChangeState(PlayerStateIdle.Instance);

    }
    public void Exit(PlayerStateManager e)
    {
        e._myAnimator.SetInteger("act", 0);
    }
    public void Skip(PlayerStateManager e)
    {

    }


}// public class PlayerStateMove : FSMSingleton<PlayerStateMove>, IFSMState<PlayerStateManager>
 //==========================================================