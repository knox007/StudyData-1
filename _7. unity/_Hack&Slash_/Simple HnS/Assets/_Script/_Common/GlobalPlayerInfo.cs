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
		_charProperty._validMoveOffset = 0f;
		_charProperty._attackTargetDistOffset = 0f;
		_charProperty._stopToAttackDist = 0f;

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
	public GlobalPlayerInfo GetData()
	{
		GlobalPlayerInfo tmpInfo = new GlobalPlayerInfo();

        tmpInfo.SetData( _charProperty );

		return tmpInfo;
	
	}//	public GlobalPlayerInfo GetData()
	//--------------------------
	public CharProper GetProper() { return _charProperty; }
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