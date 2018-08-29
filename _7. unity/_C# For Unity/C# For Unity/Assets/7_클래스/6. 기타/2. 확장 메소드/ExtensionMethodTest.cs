/*
    확장 메소드
    
        -   기존 클래스의 기능 확장.

        -   상속과는 다름.
            
            -   부모 클래스를 물려받아 자식 클래스를 만든뒤
            
                자식 클래스에 필드나 메소드를 추가하는 방식.

            -   "기존클래스" 자체의 기능을 확장.

        -   선언 방법

            -   public static class 클래스_이름
                {
                    public static 반환형 메소드이름( this 대상형식 식별자, 매개변수목록 )
                    {

                    }
                }

                대상형식

                    -   확장하고자 하는 클래스 또는 형식


*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public static class IntExtension
{
    public static int Square( this int tmpInt ) { return tmpInt * tmpInt; }

    public static int Pow( this int tmpInt, int count )
    {
        int result = tmpInt;

        for (int cur = 1; cur < count; ++cur)
            result = result * tmpInt;

        return result;        
    }
}

public class ExtensionMethodTest : MonoBehaviour {

	// Use this for initialization
	void Start () {

        print(3.Square());
        print(3.Pow(2));
        print(2.Pow(4));

    }
	
}


/*
    quiz)

        확장 메소드를 사용하여 다음을 구현한다.

        string hello = "hello";

        print(hello.add(", world"));

        ->  hello, world 출력
*/