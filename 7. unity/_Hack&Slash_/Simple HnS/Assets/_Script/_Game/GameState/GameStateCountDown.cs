//===========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//===========================================================
public class GameStateCountDown : FSMSingleton<GameStateCountDown>, IFSMState<GameStateManager>
{
    //--------------------------------
    public void Enter(GameStateManager e)
    {
		//e.ChangeState(GameStateIdle.Instance);
        StartCoroutine(e.CountDown(5));
    }
    //--------------------------------
    public void Execute(GameStateManager e)
    {

    }
    //--------------------------------
    public void Exit(GameStateManager e)
    {

    }
    //--------------------------------
    public void Skip(GameStateManager e)
    {

    }
    //--------------------------------

}// public class GameStateCountDown : FSMSingleton<GameStateCountDown>, IFSMState<GameStateManager>
 //============================================================