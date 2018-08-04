//==========================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==========================================================================
public class GameStateManager : FSM<GameStateManager>
{
    //--------------------------------------
    //  게임씬 UI 매니져
    public GameUIManager _gameUIManager;
    //--------------------------------------
    //  플레이어 캐릭터 리스트.
    public PlayerStateManager[] _playerList;
    //--------------------------------------
    //  내가 선택한 플레이어 정보
    [HideInInspector]
    public PlayerStateManager _myPlayer;
    //--------------------------------------
    //  메인 카메라.
    public Camera _mainCamera;
    //--------------------------------------
    // Use this for initialization
    void Start ()
    {
        Initialize(this, GameStateInit.Instance);
	}
	
	// Update is called once per frame
	void Update ()
    {
        FSMUpdate();
	}

}// public class GameStateManager : FSM<GameStateManager>
//==========================================================================