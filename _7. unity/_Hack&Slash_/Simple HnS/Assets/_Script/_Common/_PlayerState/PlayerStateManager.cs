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
    public CharProper _property;
    //---------------------------------
    public float _validOffset = 0.2f;
    //---------------------------------
    public Transform _myTransf;
    //---------------------------------
    public GameStateManager _gameStateManager;
    //---------------------------------
    public LayerMask _moveTargetLayer;
    //---------------------------------
    [HideInInspector]
    public Vector3 _clickedPoint;    
    //---------------------------------
    void Start () { Initialize(this, PlayerStateIdle.Instance); }
    //---------------------------------
    void Update ()
    {
        FSMUpdate();

        if ( Input.GetMouseButtonUp(0))
        {
            if (_gameStateManager)
            {
                Ray ray = _gameStateManager._mainCamera.ScreenPointToRay(Input.mousePosition);

                RaycastHit hitInfo;

                if (Physics.Raycast(ray, out hitInfo, 100f))
                {
                    int layerNumber = (int)Mathf.Log((float)_moveTargetLayer.value, 2);

                    if (hitInfo.transform.gameObject.layer.Equals(layerNumber))
                    {
                        _clickedPoint = hitInfo.point;

                        ChangeState(PlayerStateMove.Instance);

                    }// if (hitInfo.transform.gameObject.layer.Equals(layerNumber))

                }// if (Physics.Raycast(ray, out hitInfo, 100f))

            }// if (_gameStateManager)

        }// if ( Input.GetMouseButtonUp(0))

    }// void Update ()
    //---------------------------------
    public void SetData( int idx, float moveSpeed, float pow, float hp, string info )
    {
        _property._idx = idx;
        _property._moveSpeed = moveSpeed;
        _property._pow = pow;
        _property._hp = hp;
        _property._info = info;
    }
    //---------------------------------
    public IEnumerator CheckAnimationState(string aniName, IFSMState<PlayerStateManager> state)
    {
        if (_myAnimator.GetCurrentAnimatorStateInfo(0).IsName(aniName))
        {
            while (_myAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime < 1f)
            {
                //애니메이션 재생 중 실행되는 부분
                yield return null;
            }

            //애니메이션 완료 후 실행되는 부분
            ChangeState(state);

        }
        yield return null;

    }// public IEnumerator CheckAnimationState(string aniName, IFSMState<PlayerStateManager> state)
    //---------------------------------

}// public class PlayerStateManager : FSM <PlayerStateManager>
 //====================================================================