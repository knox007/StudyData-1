//============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//============================================================
public class SelectPlayer : MonoBehaviour
{
    //--------------------------------
    public Camera _mainCam;
    public SelectStateManager _selectStateManager;
    public PlayerStateManager _playerStateManager;
    //--------------------------------
    void Start ()
    {
		
	}
    //--------------------------------
    void Update ()
    {
        if (true == Input.GetMouseButtonDown(0))
        {
            GameObject tmp = GetClickedObject();
            if (tmp)
            {
                PlayerStateManager tmpState = tmp.GetComponent<PlayerStateManager>();

                _selectStateManager.ChangeState(SelectStateInfo.Instance);

                _selectStateManager._selectUIManager._descInfo.text = tmpState._info;

                _playerStateManager.ChangeState(PlayerStateStraightPunch.Instance);

            }
        }
    }
    //--------------------------------
    GameObject GetClickedObject()
    {
        RaycastHit hit;

        GameObject target = null;

        Ray ray = _mainCam.ScreenPointToRay(Input.mousePosition);

        if( Physics.Raycast(ray.origin, ray.direction * 10, out hit ))
            target = hit.collider.gameObject;

        return target;

    }// GameObject GetClickedObject()
    //--------------------------------

}// public class SelectPlayer : MonoBehaviour
 //============================================================