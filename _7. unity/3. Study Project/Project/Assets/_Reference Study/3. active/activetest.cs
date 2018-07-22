using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class activetest : MonoBehaviour {

    public GameObject _child;
	// Use this for initialization
	void Start ()
    {
        //_child.SetActive(false);

        print(" activeSelf = " + _child.activeSelf);
        print(" activeInHierarchy = " + _child.activeInHierarchy);        
    }


}
