using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RocketDestruction : MonoBehaviour {

	public float _destroyTime = 3.0f;

	void Start()
	{
		Destroy (gameObject, _destroyTime);
	}
}
