//==========================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================================
public class SelectStateManager : FSM<SelectStateManager>
{
	//----------------------------
	public SelectUIManager _selectUIManager;

    [HideInInspector]
    public PlayerStateManager _selectedPlayer;
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
    public void SetSelectedPlayer(PlayerStateManager selectedPlayer) { _selectedPlayer = selectedPlayer; }
    //----------------------------
    public void OnStart()
    {
        ChangeState(SelectStateStart.Instance);
    }
    //----------------------------

}// public class SelectStateManager : FSM<SelectStateManager>
 //==========================================================================