using UnityEngine;
using System.Collections;

public class BarrelScript : MonoBehaviour {
    public bool IsClick = false;
    public bool IsFail = false;
    
    void Start() { }
    void Update() {
        if (IsClick == true) {
            if (IsFail == false) {
                gameObject.transform.Rotate(0, 1, 0);
            } else if (IsFail == true) {
                Application.LoadLevel("GameOverScene");
            }
        }
    }
}
