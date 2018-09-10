using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
public class ActionTest : MonoBehaviour {

    // Use this for initialization
    void Start()
    {
        Action act1 = () => print("act1");
        act1();

        int result = 0;
        Action<int> act2 = (x) => result = x * x;
        act2(3);
        print(result);

        Action<double, double> act3 = (x, y) =>
        {
            double pi = x / y;

            print(string.Format("{0} / {1} = {2}", x, y, pi));
        };
        act3(22.0, 7.0);
    }
}
