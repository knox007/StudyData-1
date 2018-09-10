using UnityEngine;
using System.Collections;

public class HealthScript : MonoBehaviour {
	// 변수를 선언합니다.
	public int MaxHealth = 100;
	public int CurrentHealth = 100;
	
	public float HealthBarLength;
	
	void Start () {
		HealthBarLength = Screen.width / 2;
	}
	
	void Update () { }
	
	void OnGUI() {
		if(CurrentHealth < 0) {
			CurrentHealth = 0;
		} else if(MaxHealth < CurrentHealth) {
			CurrentHealth = MaxHealth;	
		}
		
		GUI.Box (new Rect(10, 10, HealthBarLength / ((float)MaxHealth / CurrentHealth), 20), CurrentHealth + "/" + MaxHealth);
	}
}
