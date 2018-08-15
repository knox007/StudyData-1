//====================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//====================================================
public class EnemyStateAttack : FSMSingleton<EnemyStateAttack>, IFSMState<EnemyStateManager>
{
	//---------------------------------
	public void Enter(EnemyStateManager e)
	{
		print ("--attack--");

        //	1.	Set Attack Random Idx
        int attackIdxMin = (int)CharProper.eANIMSTATE.STRAIGHTPUNCH;
        int attackIdxMax = (int)CharProper.eANIMSTATE.UPPERRIGHT + 1;
        e._curAttackIdx = Random.Range(attackIdxMin, attackIdxMax);
        print(e._curAttackIdx);

        //	2.	Apply Idx
        e._myAnimator.SetInteger("act", e._curAttackIdx);
    }
	//---------------------------------
	public void Execute(EnemyStateManager e)
	{
        //	3. 	Check if Animation is over
        if (e._myAnimator.GetCurrentAnimatorStateInfo(0).IsName(GlobalPlayerInfo.Instance._aniNameList[(int)e._curAttackIdx]) &&
            e._myAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime > 0.99f)
            //	4.	Repeat Current State
            e.RepeatCurState();

    }//	public void Execute(EnemyStateManager e)
	//---------------------------------
	public void Exit(EnemyStateManager e)
	{
	}
	//---------------------------------
	public void Skip(EnemyStateManager e) { }
	//---------------------------------

}//	public class EnemyStateAttack : FSMSingleton<EnemyStateAttack>, IFSMState<EnemyStateManager>
//====================================================