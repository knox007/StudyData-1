/*
    SceneManager.LoadScene 

    -   씬 로딩.

    -   using UnityEngine.SceneManagement; 

    -   File - Build Settings - Scenes In Build에 씬 등록.

*/

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