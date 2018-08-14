//============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//============================================================
public class GameStateIdle : FSMSingleton<GameStateIdle>, IFSMState<GameStateManager>
{
    //--------------------------------
    public void Enter(GameStateManager e)
    {
        //  적 생성기 비활성화.
        e._enemyGenerator.gameObject.SetActive(true);

    }// public void Enter(GameStateManager e)
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

}// public class GameStateIdle : FSMSingleton<GameStateIdle>, IFSMState<GameStateManager>
 //============================================================