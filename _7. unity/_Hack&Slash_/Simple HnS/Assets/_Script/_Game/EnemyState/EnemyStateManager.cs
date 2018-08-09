//====================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//====================================================================
public class EnemyStateManager : FSM<EnemyStateManager>
{
    //---------------------------------
	public Animator _myAnimator;
	//---------------------------------
    public CharProper _property;
    //---------------------------------
	[HideInInspector]
	public Transform _myTransf;
	//---------------------------------
	[Header("------- 이동관련 변수 -------")]
	[HideInInspector]
	public Vector3	_moveTargetPos;
	[Header("-- 이동 옵셋 --")]
	public Vector2	_minOffset = new Vector3(-5f, -5f);
	public Vector2	_maxOffset = new Vector3(5f, 5f);
	//---------------------------------
    void OnEnable ()
    {
		_myTransf = GetComponent<Transform> ();
		
        Initialize(this, EnemyStateInit.Instance);
	}
    //---------------------------------
    void Update ()
    {
        FSMUpdate();
	}
    //---------------------------------

}// public class EnemyStateManager : MonoBehaviour
//====================================================================