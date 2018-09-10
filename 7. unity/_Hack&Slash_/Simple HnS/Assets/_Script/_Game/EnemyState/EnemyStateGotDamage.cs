//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class EnemyStateGotDamage : FSMSingleton<EnemyStateGotDamage>, IFSMState<EnemyStateManager>
{
	//---------------------------------
	public void Enter(EnemyStateManager e)
	{
		e._myAnimator.SetInteger("act", (int)CharProper.eANIMSTATE.GETDAMAGE);

		print ("-- EnemyStateGotDamage --");

		--e._property._hp;
        print("-- Enemy HP : " + e._property._hp);

        if(e._property._hp <= 0)
            e.ChangeState(EnemyStateDead.Instance);

    }
	//---------------------------------
	public void Execute(EnemyStateManager e)
	{   
		if (e._myAnimator.GetCurrentAnimatorStateInfo (0).IsName (GlobalPlayerInfo.Instance._aniNameList [(int)CharProper.eANIMSTATE.GETDAMAGE]) &&
		    (e._myAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime % 1f) > 0.9f)
            e.ChangeState (EnemyStateInit.Instance);
	}
	//---------------------------------
	public void Exit(EnemyStateManager e)
	{
	}
	//---------------------------------
	public void Skip(EnemyStateManager e) { }
	//---------------------------------

}
//==========================================================