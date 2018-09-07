using UnityEngine;
using System.Collections;

public class AimScript : MonoBehaviour
{
    public Texture2D AimTexture;
    public Rect AimRect;

    void Start() {
		Screen.showCursor = false;
		
		// Rect에 사용될 값을 미리 설정하기
        float left = (Screen.width - AimTexture.width) / 2;
        float top = (Screen.height - AimTexture.height) / 2;
        float width = AimTexture.width;
        float height = AimTexture.height;

        // Rect 생성
        AimRect = new Rect(left, top, width, height);
    }

    void OnGUI() {

        	GUI.DrawTexture(AimRect, AimTexture);
    }
}
