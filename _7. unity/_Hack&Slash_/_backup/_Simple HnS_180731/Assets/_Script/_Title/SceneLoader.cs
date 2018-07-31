//====================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
//====================================================================
public class SceneLoader : MonoBehaviour {

	//---------------------------------
	public string _sceneName;
	//---------------------------------
	public void OnLoad()
	{
		SceneManager.LoadScene (_sceneName);
		
	}//	public void OnLoad()
	//---------------------------------
	void Start ()
	{
		
	}
	//---------------------------------

}
//====================================================================