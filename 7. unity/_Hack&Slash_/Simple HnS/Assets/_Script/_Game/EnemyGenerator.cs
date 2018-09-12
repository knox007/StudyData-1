﻿//========================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//========================================================================
//  해당 컴포넌트가 없으면 자동추가
[RequireComponent(typeof(PoolingSystem))]
//========================================================================
public class EnemyGenerator : MonoBehaviour
{
    //----------------------------
    [Header("[ 최소 등장시간 ]")]
	[Tooltip("[ 최소 등장시간이랑께롱!! ]")]
    public float _minGeneratorTime = 1f;
    //----------------------------
    [Header("[ 등장 간격 ]")]
    [Range(1f, 3f)]
    public float _intervalTime;
    //  현재 등장시간.
    float _curGeneratorTime;    
    //----------------------------
    [Header("[ 랜덤 등장 적용 ]")]
    public bool _isRandom = true;
    //----------------------------
    [Header("[ 등장시킬 적 오브젝트 이름 ]")]
    public string[] _enemyNames;
    //----------------------------
    public enum eENEMY
    {
        ENEMY_A,
		ENEMY_B,

		SIZE
    }
    //----------------------------
    [Header("[ 등장 위치]")]
    public GameObject[] _spawnPoint;
    //  스폰 포인트 갯수.
    int _spawnPointCount;
    //  현재 스폰 포인트 인덱스.
    int _curSpawnPointIdx;

	int _curEnemyIdx;
    //----------------------------
    //  참조할 오브젝트 풀.
    PoolingSystem _myPoolingSystem;
    //----------------------------
	[Header("[ 게임 상태 매니져 ] ")]
	public GameStateManager _gameStateManager;
	//----------------------------
    private void Awake()
    {
        _myPoolingSystem = GetComponent<PoolingSystem>();

        if (_isRandom)
            _curGeneratorTime = Random.Range(_minGeneratorTime, _minGeneratorTime + _intervalTime);
        else
            _curGeneratorTime = _minGeneratorTime;

        _spawnPointCount = _spawnPoint.Length;

        _curSpawnPointIdx = Random.Range(0, _spawnPointCount);

		_curEnemyIdx = Random.Range (0, (int)eENEMY.SIZE);


    }// void Awake()
    //----------------------------
    private void Start()
    {
        StartCoroutine(GenerateEnemy());
    }
    //----------------------------
    IEnumerator GenerateEnemy()
    {
        while(true)
        {
            yield return new WaitForSeconds(_curGeneratorTime);

			GameObject tmp = _myPoolingSystem.InstantiateAPS(_enemyNames[_curEnemyIdx], _spawnPoint[_curSpawnPointIdx].transform.position, Quaternion.identity);

			if (tmp != null)
			{
				EnemyStateManager enemyState = tmp.GetComponent<EnemyStateManager> ();

				enemyState._gameStateManager = _gameStateManager;

			}//	if (tmp != null)

			if (_isRandom)
				_curGeneratorTime = Random.Range(_minGeneratorTime, _minGeneratorTime + _intervalTime);
			else
				_curGeneratorTime = _minGeneratorTime;

			_curSpawnPointIdx = Random.Range(0, _spawnPointCount);

			_curEnemyIdx = Random.Range (0, (int)eENEMY.SIZE);

        }// while(true)

    }// IEnumerator GenerateEnemy()
    //----------------------------



}// public class EnemyGenerator : MonoBehaviour
 //========================================================================