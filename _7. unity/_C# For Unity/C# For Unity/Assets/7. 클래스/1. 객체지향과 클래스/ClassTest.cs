//=======================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=======================================================
//  class 클래스 이름
class Cat
{
    //  필드( 멤버변수 )
    //  접근_제한자  변수형 변수명;
    public string _name;
    public string _color;

    //  메소드( 멤버함수 )
    //  접근_제한자  반환형 함수명(매개변수 정보)
    public string Meow()
    {
        return _color + " " + _name + ", Meow !!";
    }
}

public class ClassTest : MonoBehaviour {

	// Use this for initialization
	void Start ()
    {
        Cat kitty = new Cat();
        kitty._color = "하얀색";
        kitty._name = "키티";
        print(kitty.Meow());


        Cat nero = new Cat();
        nero._color = "검은색";
        nero._name = "네로";
        print(nero.Meow());
    }
	
}
//=======================================================
/*
 *  (추가 설명)
 *  
 *  모든 클래스는 복합 데이터 형식
 *  
 *  -   복합 데이터 형식은 참조형식.
 *  
 *  -   kitty 자체에 메모리가 할당되는 것이 아닌
 *  
 *      할당된 메모리를 가리키는 역할. 
 *  
 *  -   new와 생성자를 통해 힙에 객체를 생성,
 *  
 *      kitty는 힙에 생성된 객체를 가리킴.(참조)
 * 
 */
