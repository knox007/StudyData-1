//====================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//====================================================================
public class DataType : MonoBehaviour
{
    int _intVal = 0;
    bool _boolVal = false;

    const int MAXVALUE = 1000;
    //const int MAXVALUE;
    readonly int MINVALUE;
    // Use this for initialization
    void Start ()
    {
        //------------------------------------
        //* 데이터 타입 예제
        // Bool
        bool boolVal = true;
        
        // Numeric        
        int intVal = 2147483647;
        //int intVal;
        long longVal = 1234L;      // L suffix
        float floatVal = 123.123F;   // F suffix
        double doubleVal1 = 123.123;
        double doubleVal2 = 123.123D; // D suffix

        // String        
        string stringVal = "Hello";

        print(_intVal);
        print(_boolVal);

        print(boolVal);
        print(intVal);
        print(longVal);
        print(floatVal);
        print(doubleVal1);
        print(doubleVal2);
        print(stringVal);
        //*/
        //------------------------------------


        //------------------------------------
        /* 최소/최대값.
        int _intMinVal;
        int _intMaxVal;
        float _floatMinVal;
        float _floatMaxVal;
        double _doubleMinVal;
        double _doubleMaxVal;

        _intMinVal = int.MinValue;
        _intMaxVal = int.MaxValue;

        _floatMinVal = float.MinValue;
        _floatMaxVal = float.MaxValue;

        _doubleMinVal = double.MinValue;
        _doubleMaxVal = double.MaxValue;

        print(_intMinVal);
        print(_intMaxVal);

        print(_floatMinVal);
        print(_floatMaxVal);

        print(_doubleMinVal);
        print(_doubleMaxVal);
        //*/
        //------------------------------------


        //------------------------------------
        //* 상수
        //MINVALUE = 100;

        //MAXVALUE = 10000;

        //*/
        //------------------------------------

    }// void Start ()

}// public class DataType : MonoBehaviour
 //====================================================================