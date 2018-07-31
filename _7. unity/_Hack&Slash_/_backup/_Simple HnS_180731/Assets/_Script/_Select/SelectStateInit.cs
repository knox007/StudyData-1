﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectStateInit : FSMSingleton<SelectStateInit>,IFSMState<SelectStateManager>
{
	public void Enter(SelectStateManager e)
	{
		e._selectUIManager.SetActiveInit (true);
	}

	public void Execute(SelectStateManager e)
	{
	}

	public void Exit(SelectStateManager e)
	{
	}

	public void Skip(SelectStateManager e)
	{
		
	}
}
