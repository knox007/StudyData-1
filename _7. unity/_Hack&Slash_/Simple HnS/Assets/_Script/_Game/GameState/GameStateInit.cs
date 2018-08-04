//============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//============================================================
public class GameStateInit : FSMSingleton<GameStateInit>, IFSMState<GameStateManager>
{
    //--------------------------------
    public void Enter(GameStateManager e)
    {
        //  선택씬에서 선택한 플레이어 정보를 가져온다.
        GlobalPlayerInfo tmpPlayerInfo = GlobalPlayerInfo.Instance.GetData();
        if( tmpPlayerInfo.GetIdx() != -1)
        {
            //  선택한 플레이어의 정보를 UI에 출력한다.
            e._gameUIManager._desc.text = tmpPlayerInfo.GetInfo();

            //  플레이어 리스트를 조회한다.
            for (int cur = 0; cur < e._playerList.Length; ++cur)
            {
                //  선택한 플레이어의 인덱스와 비교한다.
                if (tmpPlayerInfo.GetIdx() == e._playerList[cur]._idx)
                {
                    //  인덱스가 같은 캐릭터를 찾아서 게임에서 컨트롤 할 캐릭터로 설정한다.
                    e._myPlayer = e._playerList[cur];

                    //  active true
                    e._myPlayer.gameObject.SetActive(true);

                    //  데이터를 세팅한다.
                    e._myPlayer.SetData(
                        tmpPlayerInfo.GetIdx(),
                        tmpPlayerInfo.GetMoveSpeed(),
                        tmpPlayerInfo.GetPow(),
                        tmpPlayerInfo.GetHP(),
                        tmpPlayerInfo.GetInfo());

                }// if(tmpPlayerInfo.GetIdx() == e._playerList[cur]._idx )
                else
                {
                    //  인덱스가 다르면 비활성화 시킨다.
                    e._playerList[cur].gameObject.SetActive(false);
                }

            }// for( int cur = 0; cur < e._playerList.Length; ++cur)

        }// if( tmpPlayerInfo != null)
        else
        {
            for (int cur = 0; cur < e._playerList.Length; ++cur)
            {
                e._playerList[cur].gameObject.SetActive(false);
            }
            e._playerList[0].gameObject.SetActive(true);

        }// ~if( tmpPlayerInfo != null)


    }// public void Enter(GameStateManager e)
    //--------------------------------
    public void Execute(GameStateManager e)
    {

    }
    //--------------------------------
    public void Exit(GameStateManager e)
    {

    }
    //--------------------------------
    public void Skip(GameStateManager e)
    {

    }
    //--------------------------------

}// public class GameStateInit : FSMSingleton<GameStateInit>, IFSMState<GameStateManager>
//============================================================