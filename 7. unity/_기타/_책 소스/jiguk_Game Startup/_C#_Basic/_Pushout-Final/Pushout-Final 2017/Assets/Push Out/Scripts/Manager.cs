using UnityEngine;
using System.Collections;

public class Manager : MonoBehaviour {
	
	public int Count;               //떨어지는 박스의 갯수 세기.
	public float _time;             //박스가 떨어지기까지 걸리는 시간재기.
	bool End;                       //박스가 다 떨어졌는지 체크하기.
	public GUIText Text_time;       //시간 표기를 위한 GUIText.
	public GameObject ClearGUI;     //클리어 했을 시 나올 GUI 모음.
	public GameObject FailGUI;      //실패 했을 시 나올 GUI 모음.
	
	void OnTriggerEnter(Collider Get){
		
		//부딪힌 오브젝트의 태그가 Box인 경우 Count를 1씩 증가시킨다. 
		if(Get.GetComponent<Collider>().tag == "Box"){
				Count+=1;
			}
		
		//부딪힌 오브젝트의 태그가 Player인 경우 End를 활성화 한다.
		if(Get.GetComponent<Collider>().tag == "Player" && End ==false){
				End =true;
				FailGUI.SetActive(true);
			}	
			
		//Count가 16보다 커지면 End 를 활성화한다.	
		if(Count>=16 && End ==false){
				End =true;
				ClearGUI.SetActive(true);
			}		
	}
	
	
	void Update(){	
		
		//끝나지 않은 상태라면 계속 시간을 더해준다.	
		if(End==false){
			_time+=Time.deltaTime;
		}
		
		//_time 의 값을 GUIText의 글씨에 표기해준다.			
		Text_time.text = _time.ToString();
	
	}
	
}



				
	






