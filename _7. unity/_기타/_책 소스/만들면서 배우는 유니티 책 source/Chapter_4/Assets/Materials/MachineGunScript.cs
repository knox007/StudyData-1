using UnityEngine;
using System.Collections;

public class MachineGunScript : MonoBehaviour {
    public Rigidbody Bullet;
    public float BulletSpeed;

    void Update() {
        if (Input.GetMouseButtonDown(0)) {
            // Rigidbody 복제하기
            Rigidbody cb = (Rigidbody)Instantiate(Bullet, transform.position, transform.rotation);

            // VelocitY 값 변경해서 발사 효과 주기
            cb.velocity = transform.TransformDirection(new Vector3(0, 0, BulletSpeed));
			
			// 소리 재생
			AudioSource.PlayClipAtPoint(audio.clip, transform.position);
        }
    }
}
