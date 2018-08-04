using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectStateInfo :  FSMSingleton<SelectStateInfo>,IFSMState<SelectStateManager>
{
	public void Enter(SelectStateManager e)
	{
        e._selectUIManager.SetActiveInfo(true);
                
        e._selectUIManager._descInfo.text = e._selectedPlayer._info;

		//	Set Info About Character I selected.
		GlobalPlayerInfo.Instance.SetData (
            e._selectedPlayer._idx,
            e._selectedPlayer._moveSpeed, 
			e._selectedPlayer._pow, 
			e._selectedPlayer._hp, 
			e._selectedPlayer._info);

        e._selectedPlayer.ChangeState(PlayerStateStraightPunch.Instance);
    }

	public void Execute(SelectStateManager e)
	{
	}

	public void Exit(SelectStateManager e)
	{
        e._selectUIManager.SetActiveInfo(false);
    }

	public void Skip(SelectStateManager e)
	{

	}
}
