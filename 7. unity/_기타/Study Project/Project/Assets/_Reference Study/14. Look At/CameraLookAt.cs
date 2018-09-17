using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraLookAt : MonoBehaviour {

    public Transform target;

    void Update()
    {
        //  transform을 회전해서 target의 현재 위치를 전방벡터가 가리키도록 함.

        transform.LookAt(target);
    }
}
