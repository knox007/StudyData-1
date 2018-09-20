using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
    activeSelf

        -   현재 오브젝트의 Active 상태 반환.

    activeInHierarchy

        -   현재 오브젝트의 Hierachy상의 상태 반환.

        -   부모 오브젝트의 상태에 영향을 받음.

            -   자신의 Active가 True라도 부모가 False라면 False 적용됨.
*/
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
