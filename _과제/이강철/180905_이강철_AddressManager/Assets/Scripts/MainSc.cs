using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System.Text;

public struct Saddress
{   
    public string name;
    public string phone;
    public string age;
};

public class MainSc : MonoBehaviour {

    // Scrollbar ScrollBar;
    Scroll_View Scveiw;
    public InputField Name;
    public InputField Age;
    public InputField Phone;
    public int index;

    void Start() {
        index = -1;
        Scveiw = FindObjectOfType<Scroll_View>();
        Name = GameObject.FindGameObjectWithTag("Name").GetComponent<InputField>();
        Age = GameObject.FindGameObjectWithTag("Age").GetComponent<InputField>();
        Phone = GameObject.FindGameObjectWithTag("Phone").GetComponent<InputField>();
    }

    public void OnClickAdd()
    {
        if (Name.text != "" && Age.text != "" && Phone.text != "")
        {
            Saddress addr;

            addr.name = Name.text;
            addr.age = Age.text;
            addr.phone = Phone.text;

            Scveiw.addressList.Add(addr);
            index = -1;

            Name.text = "";
            Age.text = "";
            Phone.text = "";

            Scveiw.List_Show();            
        }        
    }

    public void OnClickAllDelete()
    {
        Scveiw.addressList.Clear();
        index = -1;

        Name.text = "";
        Age.text = "";
        Phone.text = "";

        Scveiw.List_Show();
    }

    public void OnClickDelete()
    {
        if (index != -1)
        {
            Scveiw.addressList.RemoveAt(index / 3);
            index = -1;

            Name.text = "";
            Age.text = "";
            Phone.text = "";

            Scveiw.List_Show();
        }
    }

    public void OnClickEdit()
    {
        if (index != -1)
        {
            if (Name.text != "" && Age.text != "" && Phone.text != "")
            {
                Saddress addr;

                addr.name = Name.text;
                addr.age = Age.text;
                addr.phone = Phone.text;

                Scveiw.addressList[index / 3] = addr;
                index = -1;

                Scveiw.List_Show();
            }
        }
    }

    public void OnClickSave()
    {
        for (int i = 0; i < Scveiw.addressList.Count; i++)
        {
            PlayerPrefs.SetString("Name" + i, Scveiw.addressList[i].name);
            PlayerPrefs.SetString("Age" + i, Scveiw.addressList[i].age);
            PlayerPrefs.SetString("Phone" + i, Scveiw.addressList[i].phone);
        }
        PlayerPrefs.Save();
    }

    public void OnClickLoad()
    {
        int i = 0;
        string tempName = "Name" + i;
        string tempAge = "Age" + i;
        string tempPhone = "Phone" + i;

        while (PlayerPrefs.HasKey(tempName)) {           
            Saddress addr;

            addr.name = PlayerPrefs.GetString(tempName);
            addr.age = PlayerPrefs.GetString(tempAge);
            addr.phone = PlayerPrefs.GetString(tempPhone);
            Scveiw.addressList.Add(addr);

            i++;
            tempName = "Name" + i;
            tempAge = "Age" + i;
            tempPhone = "Phone" + i;

            PlayerPrefs.Save();
        }       

        Scveiw.List_Show();
    }
}