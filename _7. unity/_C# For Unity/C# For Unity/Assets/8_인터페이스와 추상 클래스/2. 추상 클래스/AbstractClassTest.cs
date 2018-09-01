/*
    1.  추상 클래스.
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

abstract class AbstractParent
{
    protected string ProtectedMethod()
    {
        return "AbstractParent.ProtectedMethod()";
    }

    public string PublicMethod()
    {
        return "AbstractParent.PublicMethod()";
    }

    public abstract string AbstractMethod();
}

class CChild : AbstractParent
{
    public override string AbstractMethod()
    {
        return ProtectedMethod() + "___" + "CChild.AbstractMethod()";
    }
}

public class AbstractClassTest : MonoBehaviour {

	// Use this for initialization
	void Start () {

        AbstractParent obj = new CChild();

        print(obj.AbstractMethod());

        print(obj.PublicMethod());

	}

}
