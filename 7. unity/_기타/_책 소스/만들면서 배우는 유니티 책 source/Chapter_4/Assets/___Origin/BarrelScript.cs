using UnityEngine;
using System.Collections;

public class BarrelScript : MonoBehaviour {
	void Start () { }
	void Update () { }
	
	 void OnCollisionEnter(Collision collision) {
        if (collision.transform.tag == "Bullet") {
            Camera.main.GetComponent<ScoreScript>().CurrentScore += 10;
        }
    }
}
