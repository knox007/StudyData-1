using UnityEngine;
using System.Collections;

public class TurnManager : MonoBehaviour
{
    void Start()
    {
    }

    void Update()
    {
        // 게임 객체를 회전합니다.
        gameObject.transform.Rotate(0, 1, 0);
    }
}
