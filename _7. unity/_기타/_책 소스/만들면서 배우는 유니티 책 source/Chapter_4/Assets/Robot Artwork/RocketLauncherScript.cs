using UnityEngine;
using System.Collections;

public class RocketLauncherScript : MonoBehaviour {
    public Rigidbody Bullet;
    public float BulletSpeed = 20;

    void Start() { }
	void Update() { }
    public void Fire() {
        Rigidbody rigidbody = (Rigidbody)Instantiate(Bullet, transform.position, transform.rotation);
        rigidbody.velocity = transform.TransformDirection(new Vector3(0, 0, BulletSpeed));
    }
}
