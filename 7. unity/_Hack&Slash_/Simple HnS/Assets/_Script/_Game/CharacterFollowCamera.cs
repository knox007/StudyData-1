//==========================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================
public class CharacterFollowCamera : MonoBehaviour
{
	//------------------------------
	public GameStateManager _gameStateManager;
	//------------------------------
	public Vector3	_offsetPos = new Vector3(0, 6.5f, -5.5f);
	//------------------------------
	public float	_speed = 2f;
	//------------------------------
	Vector3 _finalPos;
	Transform	_myTransf;
	//------------------------------
	void Start () { _myTransf = GetComponent<Transform> ();	}
    //------------------------------
    void LateUpdate ()
	{
		_finalPos.x = _gameStateManager._myPlayer.transform.position.x + _offsetPos.x;
		_finalPos.y = _gameStateManager._myPlayer.transform.position.y + _offsetPos.y;
		_finalPos.z = _gameStateManager._myPlayer.transform.position.z + _offsetPos.z;

		_myTransf.position = Vector3.Slerp ( _myTransf.position, _finalPos, Time.smoothDeltaTime * _speed );

    }// void LateUpdate ()
    //------------------------------

}// public class CharacterFollowCamera : MonoBehaviour
 //==========================================================