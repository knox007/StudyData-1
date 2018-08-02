//===========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
//===========================================================
public class SelectStateStart : FSMSingleton<SelectStateStart>, IFSMState<SelectStateManager>
{
    //-------------------------------------------
    public void Enter(SelectStateManager e)
    {
        if (e._selectedPlayer)
        {
            e._selectedPlayer.ChangeState(PlayerStateWin.Instance);

            Invoke("OnStart", 2f);

        }
    }
    //-------------------------------------------
    public void Execute(SelectStateManager e)
    {
    }
    //-------------------------------------------
    public void Exit(SelectStateManager e)
    {
        
    }
    //-------------------------------------------
    public void Skip(SelectStateManager e)
    {

    }
    //-------------------------------------------
    void OnStart()
    {
        SceneManager.LoadScene("Game");
    }
    //-------------------------------------------

}// public class SelectStateStart : FSMSingleton<SelectStateStart>, IFSMState<SelectStateManager>
 //===========================================================