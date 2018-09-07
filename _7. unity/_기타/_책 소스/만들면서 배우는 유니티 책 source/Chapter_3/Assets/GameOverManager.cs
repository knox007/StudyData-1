using UnityEngine;
using System.Collections;

public class GameOverManager : MonoBehaviour {
	void Start () { }
	void Update () {}
	
	void OnGUI()
	{
	    if (GUI.Button(new Rect(350, 300, 100, 50), "Replay") == true)
	    {
	        Debug.Log("Replay");
	    }
	}

}
