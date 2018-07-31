using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SelectStateManager : FSM<SelectStateManager>
{
	//----------------------------
	public SelectUIManager _selectUIManager;
	//----------------------------
	void Start ()
	{
		Initialize (this, SelectStateInit.Instance);
	}
	//----------------------------
	void Update ()
	{
		FSMUpdate ();
	}
	//----------------------------

}