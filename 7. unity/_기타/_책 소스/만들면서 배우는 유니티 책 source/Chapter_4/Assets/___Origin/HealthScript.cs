//=============================================
using UnityEngine;
using System.Collections;
using UnityEngine.UI;
//=============================================
public class HealthScript : MonoBehaviour
{
    //--------------------------------
	public int MaxHealth = 100;
	public int CurrentHealth = 100;
    //--------------------------------
    public Image _curImgHP;
    public Text _curTxtHP;
    //--------------------------------
    void Start () {	}
    //--------------------------------
    void Update ()
    {
        if (CurrentHealth < 0)
            CurrentHealth = 0;
        else if (MaxHealth < CurrentHealth)
            CurrentHealth = MaxHealth;

        _curImgHP.fillAmount = (float)CurrentHealth / MaxHealth;
        _curTxtHP.text = CurrentHealth.ToString();

    }// void Update ()
    //--------------------------------

}// public class HealthScript : MonoBehaviour
 //=============================================