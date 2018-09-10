//===========================================================
//	jackie	싱글턴 템플릿.	160510.
//===========================================================
using System;
using UnityEngine;
//===========================================================
public class Singleton<T> where T : class, new()
{
	//--------------------------
	public static T Instance
	{
		get;
		private set;

	}//	public static T Instance
	//--------------------------
	static Singleton()
	{
		if( Singleton<T>.Instance == null )
			Singleton<T>.Instance = new T();

	}//	static Singleton()
	//--------------------------
	public virtual void Clear()
	{
		Singleton<T>.Instance = null;
		Singleton<T>.Instance = new T();

	}//	public virtual void Clear()
	//--------------------------

}//	public class Singleton<T> where try : class, new()
//===========================================================
public abstract class SingletonGOB<T> : MonoBehaviour where T : SingletonGOB<T>
{
	//------------------------------------------
	private static T m_Instance = null;
	//------------------------------------------
	public static T Instance
    {
		get
		{
			if( m_Instance == null )
			{
				m_Instance = GameObject.FindObjectOfType(typeof(T)) as T;
				
				if( m_Instance == null )
				{
					m_Instance = new GameObject("SingleTon Of " + typeof(T).ToString(), typeof(T)).GetComponent<T>();
				
					if( m_Instance == null )
						Debug.LogError("Problem during the creation of " + typeof(T).ToString());
				
				}//	if( m_Instance == null )

                m_Instance.Init();
			
			}//	if( m_Instance == null )
			
			return m_Instance;
		
		}//	get
	
	}//	public static T instance
	//------------------------------------------
	private void Awake()
	{
		if( m_Instance == null )
		{
			m_Instance = this as T;

			DontDestroyOnLoad( gameObject );
		
		}//	if( m_Instance == null )
	
	}//	private void Awake()
	//------------------------------------------	
	protected virtual void Init()       {}
	//------------------------------------------
	private void OnApplicationQuit()    { m_Instance = null; }
	//------------------------------------------
	
}//	public abstract class SingletonGOB<T> : MonoBehaviour where T : SingletonGOB<T>
//===========================================================