//=================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=================================================================
public class PlayerStateDead : FSMSingleton<PlayerStateDead>, IFSMState<PlayerStateManager>
{
	//-----------------------------
	PlayerStateManager _e;
	//-----------------------------
	public void Enter(PlayerStateManager e)
	{
		_e = e;
		
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.KNOCKDOWN);

		e._gameStateManager._gameUIManager._desc.text = "Game Over";

		Invoke ("GoResultScene", 2f);
			

        print("-- PlayerStateDead --");
    }
	//-----------------------------
	public void Execute(PlayerStateManager e)
	{

	}
	//-----------------------------
	public void Exit(PlayerStateManager e)
	{

	}
	//-----------------------------
	public void Skip(PlayerStateManager e)
	{

	}
	//-----------------------------
	public void GoResultScene()
	{
		_e._gameStateManager._sceneLoader.OnLoad ();
	}
	//-----------------------------

}// public class PlayerStateIdle : FSMSingleton<PlayerStateIdle>, IFSMState<PlayerStateManager>
//=================================================================