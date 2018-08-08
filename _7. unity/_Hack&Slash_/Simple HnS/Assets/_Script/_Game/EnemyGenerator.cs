//========================================================================
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
        ENEMY
    }
    //----------------------------
    [Header("[ 등장 위치]")]
    public GameObject[] _spawnPoint;
    //  스폰 포인트 갯수.
    int _spawnPointCount;
    //  현재 스폰 포인트 인덱스.
    int _curSpawnPointIdx;
    //----------------------------    
    //  참조할 오브젝트 풀.
    PoolingSystem _myPoolingSystem;
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

            _myPoolingSystem.InstantiateAPS("Enemy", _spawnPoint[_curSpawnPointIdx].transform.position, Quaternion.identity);


            if (_isRandom)
                _curGeneratorTime = Random.Range(_minGeneratorTime, _minGeneratorTime + _intervalTime);
            else
                _curGeneratorTime = _minGeneratorTime;

            _curSpawnPointIdx = Random.Range(0, _spawnPointCount);

        }// while(true)

    }// IEnumerator GenerateEnemy()
    //----------------------------



}// public class EnemyGenerator : MonoBehaviour
 //========================================================================