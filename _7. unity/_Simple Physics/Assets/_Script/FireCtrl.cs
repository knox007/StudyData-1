using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FireCtrl : MonoBehaviour {

    public GameObject   _bullet;

    public Transform _firePos;

	
	// Update is called once per frame
	void Update ()
    {
        /*
            GetMouseButton(int button)          -   마우스 버튼을 클릭하고 있을때 계속 발생.
            GetMouseButtonDown(int button)      -   마우스 버튼을 클릭했을때 한번 발생.
            GetMouseButtonUp(int button)        -   마우스 버튼을 떼었을때 한번 발생.
         */
        if (Input.GetMouseButtonDown(0))        //  0   :   왼쪽
            Fire();                             //  1   :   우측 
                                                //  2   :   가운데 버튼
	}

    void Fire()
    {
        Instantiate(_bullet, _firePos.position, _firePos.rotation);
    }
}
