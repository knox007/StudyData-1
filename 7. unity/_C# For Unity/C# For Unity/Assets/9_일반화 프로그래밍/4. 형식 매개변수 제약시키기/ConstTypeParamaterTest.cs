using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ConstTypeParamaterTest : MonoBehaviour {

	//---------------------------------
	class StructArray<T> where T : struct
	{
		public T[] _Array{ get; set; }
		public StructArray(int size)
		{
			_Array = new T[size];
		}
	}
	//---------------------------------
	class RefArray<T> where T : class
	{
		public T[] _Array{ get; set; }
		public RefArray(int size)
		{
			_Array = new T[size];
		}
	}
	//---------------------------------
	class CBase {}
	class CDerived : CBase {}
	class CBaseArray<U> where U : CBase
	{
		public U[] _Array{ get; set; }
		public CBaseArray(int size)
		{
			_Array = new U[size];
		}

		public void CoppyArray<T>(T[] src) where T : U
		{
			src.CopyTo (_Array, 0);
		}
	}
	//---------------------------------
	public T Createinstance<T>() where T : new() { return new T ();	}
	//---------------------------------
	void Start ()
	{
		StructArray<int> tmpStruct = new StructArray<int> (3);
		tmpStruct._Array [0] = 0;
		tmpStruct._Array [1] = 1;
		tmpStruct._Array [2] = 2;

		RefArray<StructArray<double>> tmpRef = new RefArray<StructArray<double>> (3);
		tmpRef._Array [0] = new StructArray<double> (5);
		tmpRef._Array [1] = new StructArray<double> (10);
		tmpRef._Array [2] = new StructArray<double> (1005);

		CBaseArray<CBase> tmpBase = new CBaseArray<CBase> (3);
		tmpBase._Array [0] = new CBase ();
		tmpBase._Array [1] = new CDerived();
		tmpBase._Array [2] = Createinstance<CBase>();

		CBaseArray<CDerived> tmpDerived = new CBaseArray<CDerived> (3);
		tmpDerived._Array [0] = new CDerived ();
		//tmpDerived._Array [0] = new CBase();
		tmpDerived._Array [1] = Createinstance<CDerived>();
		tmpDerived._Array [2] = Createinstance<CDerived>();

		CBaseArray<CDerived> tmpDerived2 = new CBaseArray<CDerived> (3);
		tmpDerived2.CoppyArray<CDerived> (tmpDerived._Array);
		
	}
}
