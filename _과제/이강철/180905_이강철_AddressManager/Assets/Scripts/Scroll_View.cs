using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Scroll_View : MonoBehaviour {

    public List<Saddress> addressList = new List<Saddress>();
    public Transform Content;
    public GameObject NamePrefab;
    public GameObject AgePrefab;
    public GameObject PhonePrefab;
    public GameObject[] NamePre;
    public GameObject[] AgePre;
    public GameObject[] PhonePre;

    public void List_Show()
    {
        NamePre = GameObject.FindGameObjectsWithTag("NamePre");
        AgePre = GameObject.FindGameObjectsWithTag("AgePre");
        PhonePre = GameObject.FindGameObjectsWithTag("PhonePre"); 

        for (int i = 0; i < NamePre.Length; i++)
        {
            Destroy(NamePre[i]);
            Destroy(AgePre[i]);
            Destroy(PhonePre[i]);
        }

        for (int i = 0; i < addressList.Count; i++)
        {
            var instance = Instantiate(NamePrefab);
            instance.transform.SetParent(Content);
            instance.GetComponent<Text>().text = addressList[i].name;

            var instance2 = Instantiate(AgePrefab);
            instance2.transform.SetParent(Content);
            instance2.GetComponent<Text>().text = addressList[i].age;

            var instance3 = Instantiate(PhonePrefab);
            instance3.transform.SetParent(Content);
            instance3.GetComponent<Text>().text = addressList[i].phone;
        }        
    }
}
