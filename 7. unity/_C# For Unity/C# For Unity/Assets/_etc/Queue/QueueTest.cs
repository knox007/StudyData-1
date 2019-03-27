//============================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//============================================================
public class QueueTest : MonoBehaviour
{
    //------------------------
    Queue<int> _queue = new Queue<int>();
    //------------------------
    void Start()
    {
        _queue.Enqueue(1);
        _queue.Enqueue(2);
        _queue.Enqueue(3);
        _queue.Enqueue(4);
        ShowDatas();

        _queue.Dequeue();
        ShowDatas();

        _queue.Enqueue(5);
        ShowDatas();

    }// void Start()
    //------------------------
    void ShowDatas()
    {
        print("------------");
        foreach (int tmp in _queue)
            print(tmp);
        print("------------");
    }
    //------------------------

}// public class QueueTest : MonoBehaviour
 //============================================================