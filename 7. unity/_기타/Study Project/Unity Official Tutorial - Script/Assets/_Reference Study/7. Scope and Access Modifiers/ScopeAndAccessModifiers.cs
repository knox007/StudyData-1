using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
    접근 지정자     |    내부 접근 가능    |   외부 접근 가능    |   자식 클래스 접근 가능    |
    -------------------------------------------------------------------------------------------
    public          |       가능           |          가능       |          가능              |
    private         |       가능           |          불가능     |          불가능            |
    protected       |       가능           |          불가능     |          가능              |
 
*/
public class ScopeAndAccessModifiers : MonoBehaviour
{
    public int alpha = 5;
    
    private int beta = 0;
    private int gamma = 5;
    
    private AnotherClass myOtherClass;

    void Start()
    {
        alpha = 29;

        myOtherClass = new AnotherClass();
        myOtherClass.FruitMachine(alpha, myOtherClass.apples);
    }


    void Example(int pens, int crayons)
    {
        int answer;
        answer = pens * crayons * alpha;
        Debug.Log(answer);
    }


    void Update()
    {
        Debug.Log("Alpha is set to: " + alpha);
    }
}
