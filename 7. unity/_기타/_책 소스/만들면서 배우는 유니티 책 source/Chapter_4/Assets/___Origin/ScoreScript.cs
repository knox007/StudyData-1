using UnityEngine;
using System.Collections;

public class ScoreScript : MonoBehaviour {
	public int CurrentScore = 0;
	public Rect ScorePosition;
	
	void Start () {
		ScorePosition = new Rect(Screen.width - 110, 10, 100, 30);
	}
	void Update () { }
	
	void OnGUI() {
		GUI.Label(ScorePosition, CurrentScore.ToString());
	}
}
