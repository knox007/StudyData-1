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
	public SceneLoader _sceneLoader;
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
    //  적 생성기.
    public EnemyGenerator _enemyGenerator;
    //--------------------------------------
	[HideInInspector]
	public EnemyStateManager _selectedEnemy;
	//--------------------------------------
    // Use this for initialization
    void Start ()
    {
        Initialize(this, GameStateInit.Instance);

		_selectedEnemy = null;
	}
    //--------------------------------------
    // Update is called once per frame
    void Update ()
    {
		if (true == Input.GetMouseButtonUp (0))
		{
			GameObject tmpGObj = GetClickedObject ();

			if (tmpGObj.CompareTag ("Enemy"))
			{
				print (tmpGObj.name);
				_selectedEnemy = tmpGObj.GetComponent<EnemyStateManager> ();

				_myPlayer.ChangeState (PlayerStateTrace.Instance);
			
			}//	if (tmpGObj.CompareTag ("Enemy"))
		
		}//	if (true == Input.GetMouseButtonUp (0))
		
        FSMUpdate();
	
	}//	void Update ()
    //--------------------------------------
    public IEnumerator CountDown(int destTime)
    {
        yield return new WaitForSeconds(3);

        int time = destTime;
        while(time > 0)
        {
            _gameUIManager._desc.text = time.ToString();
            yield return new WaitForSeconds(1);

            --time;
        }
        _gameUIManager._desc.text = "Start!!";
        yield return new WaitForSeconds(2);
        _gameUIManager._desc.text = "";

        ChangeState(GameStateIdle.Instance);
    
	}//	public IEnumerator CountDown(int destTime)
    //--------------------------------------
	GameObject GetClickedObject()
	{
		RaycastHit hit;

		GameObject target = null;

		Ray ray = _mainCamera.ScreenPointToRay(Input.mousePosition);

		if( Physics.Raycast(ray.origin, ray.direction * 10, out hit ))
			target = hit.collider.gameObject;

		return target;

	}// GameObject GetClickedObject()
	//--------------------------------
	//--------------------------------------

}// public class GameStateManager : FSM<GameStateManager>
 //==========================================================================