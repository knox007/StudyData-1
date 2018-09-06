using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Scroll_Index : MonoBehaviour {

    public GameObject[] NamePre;
    public GameObject[] AgePre;
    public GameObject[] PhonePre;
    public MainSc Miansc;
    Scroll_View Scveiw;
    int index;

    public void Start()
    {
        Miansc = FindObjectOfType<MainSc>();
        Scveiw = FindObjectOfType<Scroll_View>();
    }

    public void OnClick()
    {
        NamePre = GameObject.FindGameObjectsWithTag("NamePre");
        AgePre = GameObject.FindGameObjectsWithTag("AgePre");
        PhonePre = GameObject.FindGameObjectsWithTag("PhonePre");

        for (int i = 0; i < NamePre.Length; i++)
        {
            NamePre[i].GetComponent<Text>().color = new Color(0, 0, 0);
            AgePre[i].GetComponent<Text>().color = new Color(0, 0, 0);
            PhonePre[i].GetComponent<Text>().color = new Color(0, 0, 0);
        }

        index = transform.GetSiblingIndex();
        NamePre[index / 3].GetComponent<Text>().color = new Color(0, 0, 255);
        AgePre[index / 3].GetComponent<Text>().color = new Color(0, 0, 255);
        PhonePre[index / 3].GetComponent<Text>().color = new Color(0, 0, 255);

        Miansc.index = index;
        Miansc.Name.text = Scveiw.addressList[index / 3].name;
        Miansc.Age.text = Scveiw.addressList[index / 3].age;
        Miansc.Phone.text = Scveiw.addressList[index / 3].phone;
    }
}
