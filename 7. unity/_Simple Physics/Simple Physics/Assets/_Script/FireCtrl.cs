using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FireCtrl : MonoBehaviour {

	public GameObject   	_bullet;

	public Transform 		_firePos;

	ParticleSystem 			_muzzleFlash;

    public ParticleSystem 	_cartridge;

    //  총소리.
    public AudioClip        _fire;

    AudioSource             _audioSrc;

    private void Start()
    {
        //  GetComponentInChildren
        //  -   해당 게임 오브젝트 차일드중에서 컴포넌트를 탐색.
        //  -   찾는 것과 동일한 컴포넌트가 여러개 있다면 최상단 컴포넌트가 반환됨.
        _muzzleFlash = _firePos.GetComponentInChildren<ParticleSystem>();

        _audioSrc = GetComponent<AudioSource>();
    }


    // Update is called once per frame
    void Update ()
    {
        /*
            GetMouseButton(int button)          -   마우스 버튼을 클릭하고 있을때 계속 발생.
            GetMouseButtonDown(int button)      -   마우스 버튼을 클릭했을때 한번 발생.
            GetMouseButtonUp(int button)        -   마우스 버튼을 떼었을때 한번 발생.
         */
        if (Input.GetMouseButtonDown(0))        //  0   :   왼쪽
            Fire();                             //  1   :   우측 
                                                //  2   :   가운데 버튼
	}

    void Fire()
    {
        Instantiate(_bullet, _firePos.position, _firePos.rotation);

        if(_cartridge!=null)
            _cartridge.Play();

        if(_muzzleFlash!=null)
            _muzzleFlash.Play();

        FireSfx();
    }

    void FireSfx()
    {
        if (_fire != null)
            _audioSrc.PlayOneShot(_fire, 1.0f);        
    }
}
