using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lerptest : MonoBehaviour {
    public Transform _target;
    Transform _myTransf;
	// Use this for initialization
	void Start ()
    {
        _myTransf = GetComponent<Transform>();
    }
	
	// Update is called once per frame
	void Update ()
    {
        /*
        Vector3 tmpPos = new Vector3(Mathf.Lerp(transform.position.x, _target.position.x, Time.deltaTime * 0.5f), 0f,0f);
        _myTransf.position = tmpPos;
        */
        _myTransf.position = Vector3.Lerp(transform.position, _target.position, Time.deltaTime);

    }
}
