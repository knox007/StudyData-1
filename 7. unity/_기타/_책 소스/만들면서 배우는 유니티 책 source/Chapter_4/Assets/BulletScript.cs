using UnityEngine;
using System.Collections;

public class BulletScript : MonoBehaviour {
    // 원본 파티클 효과
    public GameObject originSpark;
    // 복제될 파티클 효과
    private GameObject cloneSpark;
    // 파티클을 제어하기 위한 Emitter
    private ParticleEmitter pe;

    void Start() {
        cloneSpark = (GameObject)Instantiate(originSpark, originSpark.transform.position, originSpark.transform.rotation);
        pe = cloneSpark.GetComponent<ParticleEmitter>();
        pe.emit = false;
    }


    void Update() { }

    void OnCollisionEnter(Collision collision) {
        if (collision.transform.tag == "Bullet") {
            return;
		}

        cloneSpark.transform.position = transform.position;
        pe.Emit();
        Destroy(transform.gameObject);
	}
}
  