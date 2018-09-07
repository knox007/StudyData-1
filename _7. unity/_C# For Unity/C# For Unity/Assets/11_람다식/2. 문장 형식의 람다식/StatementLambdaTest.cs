/*
    1.  문장 형식의 람다식.

        -   연산이나 비교등의 "표현"형식 이 아닌

            문장 형식의 람다식.

        -   선언

            (매개변수_목록)   =>  {
                                    문장;
                                    
                                    문장;
                                    
                                    ..........

                                    };

        -   표현 형식의 람다식으로는 반환 형식이 없는 무명 함수를 만들수 없음.

            -   문장형식은 가능.

*/

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StatementLambdaTest : MonoBehaviour
{
    delegate void StateLambda();
    delegate string StateLambdaWithReturn(string [] tmp);
    // Use this for initialization
    void Start ()
    {
        //  No Return.
        StateLambda doIt = () =>
        {
            print("Print");
            print("Something");
            print("like this");

        };

        doIt();

        //  Return value Exists.
        StateLambdaWithReturn doItwithReturn = (tmp) =>
        {
            string result = "";
            foreach( string s in tmp)
                result += s;

            return result;
        };

        string[] test = { "aaa","bbb","ccc" };
        print(doItwithReturn(test));

    }

}
