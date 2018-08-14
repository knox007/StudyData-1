﻿//=================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=================================================================
public class PlayerStateIdle : FSMSingleton<PlayerStateIdle>, IFSMState<PlayerStateManager>
{
    public void Enter(PlayerStateManager e)
    {
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.IDLE);
    }
    public void Execute(PlayerStateManager e)
    {

    }
    public void Exit(PlayerStateManager e)
    {

    }
    public void Skip(PlayerStateManager e)
    {

    }

}// public class PlayerStateIdle : FSMSingleton<PlayerStateIdle>, IFSMState<PlayerStateManager>
//=================================================================