using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ISTest : MonoBehaviour {

	// Use this for initialization
	void Start () {
      
      int a = 100;

      uint b = (uint)a;

      if(b is int )
          print("int");
      else
          print("not int");
      
    }

    // Update is called once per frame
    void Update () {
		
	}
}
