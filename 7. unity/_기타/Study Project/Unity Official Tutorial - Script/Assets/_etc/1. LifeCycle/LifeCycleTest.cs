//=====================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=====================================================
public class LifeCycleTest : MonoBehaviour
{    
    //-------------------------------
    private void Awake()    { Debug.Log("Awake is called!!"); }
    //-------------------------------
    private void OnEnable() { Debug.Log("OnEnable is called!!"); }
    //-------------------------------
    private void OnDisable() { Debug.Log("OnDisable is called!!"); }
    //-------------------------------    
    // Use this for initialization
    void Start () { Debug.Log("Start is called!!"); }
    //-------------------------------
    /*
	void Update ()
    {
        Debug.Log("Update is called!!");

        Debug.Log("Time.deltaTime = " + Time.deltaTime);
    }
    //*/
    //-------------------------------
    /*
    private void FixedUpdate()
    {
        Debug.Log("FixedUpdate is called!!");

        Debug.Log("Time.deltaTime = " + Time.deltaTime);
    }
    //*/
    //-------------------------------
    private void OnTriggerEnter(Collider other)
    {
        Debug.Log("OnTriggerEnter is called!!");
    }
    //-------------------------------
    private void OnTriggerExit(Collider other)
    {
        Debug.Log("OnTriggerExit is called!!");
    }
    //-------------------------------
    private void OnTriggerStay(Collider other)
    {
        Debug.Log("OnTriggerStay is called!!");
    }
    //-------------------------------
    private void OnCollisionEnter(Collision collision)
    {
        Debug.Log("OnCollisionEnter is called!!");
    }
    //-------------------------------
    private void OnCollisionExit(Collision collision)
    {
        Debug.Log("OnCollisionExit is called!!");
    }
    //-------------------------------
    private void OnCollisionStay(Collision collision)
    {
        Debug.Log("OnCollisionStay is called!!");
    }
    //-------------------------------

}// public class LifeCycleTest : MonoBehaviour
 //=====================================================