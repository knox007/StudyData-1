using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectStateInfo :  FSMSingleton<SelectStateInfo>,IFSMState<SelectStateManager>
{
	public void Enter(SelectStateManager e)
	{
        e._selectUIManager.SetActiveInfo(true);
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
