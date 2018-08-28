using System.Collections;
using System.Collections.Generic;
using UnityEngine;

class Global
{
    //  정적 필드.
    public static int _count = 0;

    //  정적 메소드.
    public static void StaticMethod() { }

}

class ClassA { public ClassA() { ++Global._count; } }

class ClassB { public ClassB() { ++Global._count; } }

public class StaticFieldTest : MonoBehaviour {

	// Use this for initialization
	void Start () {

        new ClassA();
        new ClassA();
        new ClassB();
        new ClassB();

        Global.StaticMethod();

        print(Global._count);
    }
	
}
