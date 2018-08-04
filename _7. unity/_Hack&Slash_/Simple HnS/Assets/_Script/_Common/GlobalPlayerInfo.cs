//============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//============================================================
public class GlobalPlayerInfo : Singleton<GlobalPlayerInfo>
{
    //--------------------------
    private int _idx = -1;
    private float _moveSpeed;
    private float _pow;
    private float _hp;
    private string _info;
	//--------------------------
	public void SetData( int idx, float moveSpeed, float pow, float hp, string info )
	{
        _idx        = idx;
		_moveSpeed 	= moveSpeed;
		_pow 		= pow;
		_hp 		= hp;
		_info 		= info;
	
	}//	public void SetData( float moveSpeed, float pow, float hp, string info )
	//--------------------------
	public GlobalPlayerInfo GetData()
	{
		GlobalPlayerInfo tmpInfo = new GlobalPlayerInfo();

        tmpInfo.SetData(_idx, _moveSpeed, _pow, _hp, _info);

		return tmpInfo;
	
	}//	public GlobalPlayerInfo GetData()
	//--------------------------
	public void Clear()	{ SetData (-1, 0f, 0f, 0f, "");	}
    //--------------------------
    public int GetIdx() { return _idx; }
    //--------------------------
    public float GetMoveSpeed() { return _moveSpeed; }
    //--------------------------
    public float GetPow() { return _pow; }
    //--------------------------
    public float GetHP() { return _hp; }
    //--------------------------
    public string GetInfo() { return _info; }
    //--------------------------

}//	public class GlobalPlayerInfo : Singleton<GlobalPlayerInfo>
 //============================================================