//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class PlayerStateMove : FSMSingleton<PlayerStateMove>, IFSMState<PlayerStateManager>
{
    public void Enter(PlayerStateManager e)
    {
        
    }
    public void Execute(PlayerStateManager e)
    {
        e._myTransf.position = Vector3.Lerp(e._myTransf.position, e._clickedPoint, Time.deltaTime * e._moveSpeed);

        if (Vector3.Distance(e._myTransf.position, e._clickedPoint) <= 0.1f)
            e.ChangeState(PlayerStateIdle.Instance);

    }
    public void Exit(PlayerStateManager e)
    {

    }
    public void Skip(PlayerStateManager e)
    {

    }


}// public class PlayerStateMove : FSMSingleton<PlayerStateMove>, IFSMState<PlayerStateManager>
 //==========================================================