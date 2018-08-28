//=====================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//=====================================================
class Dog
{
    public string _name;
    public string _color;
    
    //*
    public Dog()
    {
        _name = "noname";
        _color = "nocolor";
    }
    //*/

    ~Dog()
    {
        ConstructNFinalize._Instance.Print("Bye");
    }
    public Dog( string name, string color )
    {
        _name = name;
        _color = color;
    }

    public string Bow()
    {
        return _color + " " + _name + ", Bow!!!";
    }

}
//=====================================================
public class ConstructNFinalize : MonoBehaviour {

    public static ConstructNFinalize _Instance;

    // Use this for initialization
    void Start () {
        _Instance = this;

        Dog noname = new Dog();
        print(noname.Bow());

        Dog white = new Dog("흰둥이", "하얀색");
        print(white.Bow());

        Dog black = new Dog("검둥이", "검은색");
        print(black.Bow());

    }
    public void Print(string str)
    {
        print(str);
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
//=====================================================