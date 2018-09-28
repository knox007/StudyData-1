//===============================================
using UnityEngine;
using UnityEngine.UI;
using System.Collections;
//===============================================
public class DualAxisExample : MonoBehaviour 
{
	public float range;
	public Text _dualAxisState;

	void Update () 
	{
		float h = Input.GetAxis("Horizontal");
		float v = Input.GetAxis("Vertical");
		float xPos = h * range;
		float yPos = v * range;

		transform.localPosition = new Vector3(xPos, yPos, 0);
		_dualAxisState.text = "Horizontal Value Returned: "+h.ToString("F2")+"\nVertical Value Returned: "+v.ToString("F2");    
	}
}
//===============================================