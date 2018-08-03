//==================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//==================================================================
public class ParticlePoolProperty : MonoBehaviour
{
    //--------------------------------------    
    [Tooltip("파티클이 자동으로 off되는 시간, -1이면 수동 off해줘야함")]
    public float _autoDestroyTime = 0f;
    //--------------------------------------
    void OnEnable()
    {
        if (_autoDestroyTime < 0)
            Invoke("DestroyAPS", _autoDestroyTime);
    }
    //--------------------------------------
    void DestroyAPS() { gameObject.DestroyAPS(); }
    //--------------------------------------

}// public class ParticlePoolProperty : MonoBehaviour
 //==================================================================