//============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
//============================================================
public class SelectUIManager : MonoBehaviour {
    //--------------------------------------
    [Header(" --- Panel Init --- ")]
    public GameObject _panelInit;
    public Text _descInit;
    [Header(" --- Panel Info --- ")]
    public GameObject _panelInfo;
    public Text _descInfo;
    //--------------------------------------
    public void SetActiveInit( bool isActive )
	{
		_panelInit.SetActive (isActive);
	}
	//--------------------------------------
	public void SetActiveInfo( bool isActive )
	{
		_panelInfo.SetActive (isActive);
	}
	//--------------------------------------
	void Start () {
		SetActiveInit (false);
		SetActiveInfo (false);
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
//============================================================