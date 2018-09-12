using UnityEngine;
using System.Collections;

public class RocketScript : MonoBehaviour {
	void Start () { }
	void Update () { }
	
	void OnCollisionEnter(Collision collision) {
    	if (collision.transform.tag != "Rocket"){
			Destroy(gameObject);
		}
		
		if(collision.transform.tag == "Player") {
			Camera.main.GetComponent<HealthScript>().CurrentHealth -= 10;
		}
	}
}
