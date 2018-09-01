using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Text;

public class StringBuilderTest : MonoBehaviour {

    //  http://grayt.tistory.com/110 참고.

    StringBuilder _sb1 = new StringBuilder();
    StringBuilder _sb2 = new StringBuilder(128);
    
    // Use this for initialization
    void Start () {

        print("_sb1.Length : " + _sb1.Length.ToString() + "_sb1.Capacity : " + _sb1.Capacity.ToString());
        print("_sb2.Length : " + _sb2.Length.ToString() + "_sb2.Capacity : " + _sb2.Capacity.ToString());

        _sb1.AppendFormat("abcdefghijklmnopqrstuvwxyz");
        print("_sb1.Length : " + _sb1.Length.ToString() + "_sb1.Capacity : " + _sb1.Capacity.ToString());
        _sb1.Remove(0, _sb1.Length);
        print("_sb1.Length : " + _sb1.Length.ToString() + "_sb1.Capacity : " + _sb1.Capacity.ToString());

        _sb2.AppendFormat("abcdefghijklmnopqrstuvwxyz");
        print("_sb2.Length : " + _sb2.Length.ToString() + "_sb2.Capacity : " + _sb2.Capacity.ToString());
        _sb2.Remove(0, _sb2.Length);
        print("_sb2.Length : " + _sb2.Length.ToString() + "_sb2.Capacity : " + _sb2.Capacity.ToString());

    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
