//============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//============================================================
[System.Serializable]
public struct CharProper
{
    //--------------------------
	public enum eANIMSTATE
	{
		IDLE,
        MOVEFORWARD,

        STRAIGHTPUNCH,		
		HOOKLEFTTIRAMIS,
        UPPERRIGHT,

		WIN,
	}
	//--------------------------
    public int _idx;
    public float _moveSpeed;
    public float _pow;
    public float _hp;
    public string _info;
    public float _rotSpeed;
	public float _validMoveOffset;
	public float _attackTargetDistOffset;
	public float _stopToAttackDist;
    //--------------------------

}// public struct CharProper
//============================================================