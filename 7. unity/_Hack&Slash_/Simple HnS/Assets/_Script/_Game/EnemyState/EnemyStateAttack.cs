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
        //	1.	Set Attack Random Idx
        int attackIdxMin = (int)CharProper.eANIMSTATE.STRAIGHTPUNCH;
        int attackIdxMax = (int)CharProper.eANIMSTATE.UPPERRIGHT + 1;
        e._curAttackIdx = Random.Range(attackIdxMin, attackIdxMax);        

        //	2.	Apply Idx
        e._myAnimator.SetInteger("act", e._curAttackIdx);

        print("--- EnemyStateAttack ---");
    }
	//---------------------------------
	public void Execute(EnemyStateManager e)
	{
        //print (e._myAnimator.GetCurrentAnimatorStateInfo (0).normalizedTime);
        if (e._gameStateManager._myPlayer.CurrentState == PlayerStateDead.Instance)
            e.ChangeState(EnemyStateInit.Instance);
        else
        {

            //	플레이어 추적 범위 체크.
            float distPlayer = Vector3.Distance(e._myTransf.position, e._gameStateManager._myPlayer.transform.position);
            if (distPlayer >= e._property._attackTargetDistOffset)
                e.ChangeState(EnemyStatePatrol.Instance);
            else
            {
                //	3. 	Check if Animation is over
                if (e._myAnimator.GetCurrentAnimatorStateInfo(0).IsName(GlobalPlayerInfo.Instance._aniNameList[(int)e._curAttackIdx]) &&
                    (e._myAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime % 1f) > 0.9f)
                {
                    if (e._gameStateManager._myPlayer.CurrentState != PlayerStateMove.Instance)
                        e._gameStateManager._myPlayer.ChangeState(PlayerStateGotDamage.Instance);

                    //	4.	Repeat Current State
                    e.RepeatCurState();
                }

            }
            
        }       

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