//====================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
//====================================================
public class UIManager1 : MonoBehaviour
{
    //---------------------------
    //  제한시간.
    public Text _txtLimitTime;
    //  착한 두더지 카운트.
    public Text _txtGoodCount;
    //  나쁜 두더지 카운트.
    public Text _txtBadCount;
    //  최종 점수.
    public Text _txtFinalScore;
    //---------------------------
    public GameObject _resultNode;
    //---------------------------
    private void Start()
    {
        _resultNode.SetActive(false);
    }
    //---------------------------
    //  제한 시간 설정.
    public void SetLimitTime(string time) { _txtLimitTime.text = time; }
    //---------------------------
    //  최종 결과 세팅.
    public void ShotResult(int goodCount, int badCount, int finalScore)
    {
        _resultNode.SetActive(true);
        _txtGoodCount.text = goodCount.ToString();
        _txtBadCount.text = badCount.ToString();
        _txtFinalScore.text = finalScore.ToString();

    }// public void SetResult(int goodCount, int badCount, int finalScore)
    //---------------------------
    public void OnReplay()
    {
        SceneManager.LoadScene("Mole Game 10");
    }
}
//====================================================