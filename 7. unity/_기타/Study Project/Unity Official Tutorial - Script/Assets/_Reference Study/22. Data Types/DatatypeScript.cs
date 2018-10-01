using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DatatypeScript : MonoBehaviour {

    public Transform _transfCube;
    public Transform _transfSphere;
    void Start()
    {
        //Value type variable
        Vector3 pos = _transfCube.position;
        pos = new Vector3(0, 2, 0);

        //Reference type variable
        //  C# For Unity
        //    ->  1_기본 데이터 형식 ->  0. 기본 데이터   -> 2. 데이터 참고.
        Transform tran = _transfSphere;
        tran.position = new Vector3(0, 2, 0);
    }
}
