//====================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//====================================================================
public class PlayerStateManager : FSM <PlayerStateManager>
{
    //---------------------------------
    public Animator _myAnimator;
    //---------------------------------
    public float _moveSpeed;
    public float _pow;
    public float _hp;
    public string _info;
    //---------------------------------
    void Start () { Initialize(this, PlayerStateIdle.Instance); }
    //---------------------------------
    void Update () { FSMUpdate(); }
    //---------------------------------
    public IEnumerator CheckAnimationState( string aniName, IFSMState<PlayerStateManager> state )
    {

        while (!_myAnimator.GetCurrentAnimatorStateInfo(0).IsName(aniName))
        {
            //전환 중일 때 실행되는 부분
            yield return null;
        }

        while (_myAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime < 1f)
        {
            //애니메이션 재생 중 실행되는 부분
            yield return null;
        }

        //애니메이션 완료 후 실행되는 부분
        ChangeState(state);

    }

    //---------------------------------

}// public class PlayerStateManager : FSM <PlayerStateManager>
 //====================================================================