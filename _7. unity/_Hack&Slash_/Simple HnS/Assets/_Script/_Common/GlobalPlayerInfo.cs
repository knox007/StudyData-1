//============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//============================================================
public class GlobalPlayerInfo : Singleton<GlobalPlayerInfo>
{   
	//--------------------------
	public List<string>	_aniNameList;
    //--------------------------
    CharProper _charProperty;
    //--------------------------
    public GlobalPlayerInfo()
    {
        _charProperty._idx = -1;
        _charProperty._moveSpeed = 0f;
        _charProperty._pow = 0f;
        _charProperty._hp = 0f;
        _charProperty._info = "";
        _charProperty._rotSpeed = 0f;

		_aniNameList = new List<string> ();
		_aniNameList.Add("Base Layer.Idle");		
		_aniNameList.Add("Base Layer.Move Forward");

        _aniNameList.Add("Base Layer.Straight Punch");
        _aniNameList.Add("Base Layer.Hook Left Tiramis");
        _aniNameList.Add("Base Layer.Upper Right");

        _aniNameList.Add("Base Layer.Win");
    }
    //--------------------------
	public void SetData( CharProper charProperty )
	{
		_charProperty = charProperty;
	}
	//--------------------------
    public void SetData( int idx, float moveSpeed, float pow, float hp, string info )
	{
        _charProperty._idx          = idx;
        _charProperty._moveSpeed 	= moveSpeed;
        _charProperty._pow 		    = pow;
        _charProperty._hp 		    = hp;
        _charProperty._info 		= info;
	
	}//	public void SetData( float moveSpeed, float pow, float hp, string info )
	//--------------------------
	public GlobalPlayerInfo GetData()
	{
		GlobalPlayerInfo tmpInfo = new GlobalPlayerInfo();

        tmpInfo.SetData(
            _charProperty._idx,
            _charProperty._moveSpeed,
            _charProperty._pow,
            _charProperty._hp,
            _charProperty._info);

		return tmpInfo;
	
	}//	public GlobalPlayerInfo GetData()
	//--------------------------
	public void Clear()	{ SetData (-1, 0f, 0f, 0f, "");	}
    //--------------------------
    public int GetIdx() { return _charProperty._idx; }
    //--------------------------
    public float GetMoveSpeed() { return _charProperty._moveSpeed; }
    //--------------------------
    public float GetPow() { return _charProperty._pow; }
    //--------------------------
    public float GetHP() { return _charProperty._hp; }
    //--------------------------
    public string GetInfo() { return _charProperty._info; }
    //--------------------------

}//	public class GlobalPlayerInfo : Singleton<GlobalPlayerInfo>
 //============================================================