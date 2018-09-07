	using UnityEngine;
	using System.Collections;

public class BoardGameManager : MonoBehaviour {
    // Rect 객체를 생성합니다.
    Rect rectangle_0 = new Rect(50, 300, 100, 30);
    Rect rectangle_1 = new Rect(200, 300, 100, 30);
    Rect rectangle_2 = new Rect(350, 300, 100, 30);
    Rect rectangle_3 = new Rect(500, 300, 100, 30);

    // MyBarrel 객체
    public GameObject Barrel_0;
    public GameObject Barrel_1;
    public GameObject Barrel_2;
    public GameObject Barrel_3;

	void Start() {
	    // 임의의 숫자를 생성합니다.
	    int randomNum = Random.Range(0, 4);
	
	    if(randomNum == 0) {
	        Barrel_0.GetComponent<BarrelScript>().IsFail = true;
	    } else if(randomNum == 1) {
	        Barrel_1.GetComponent<BarrelScript>().IsFail = true;
	    } else if(randomNum == 2){
	        Barrel_2.GetComponent<BarrelScript>().IsFail = true;
	    } else if(randomNum == 3){
	        Barrel_3.GetComponent<BarrelScript>().IsFail = true;
	    }
	}
    void Update() { }

    void OnGUI() {
        if (GUI.Button(rectangle_0, "Button0")) {
            Barrel_0.GetComponent<BarrelScript>().IsClick = true;
        }

        if (GUI.Button(rectangle_1, "Button1")) {
            Barrel_1.GetComponent<BarrelScript>().IsClick = true;
        }

        if (GUI.Button(rectangle_2, "Button2")) {
            Barrel_2.GetComponent<BarrelScript>().IsClick = true;
        }

        if (GUI.Button(rectangle_3, "Button3")) {
            Barrel_3.GetComponent<BarrelScript>().IsClick = true;
        }
    }
}
