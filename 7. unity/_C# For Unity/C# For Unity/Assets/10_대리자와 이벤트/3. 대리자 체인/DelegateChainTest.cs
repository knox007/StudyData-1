/*
	1.	대리자 체인

		-	대리자 하나로 여러개의 메소드를 동시에 참조.

		-	체인 연결 방법.

			1)	+= 연산자

			2)	+, = 연산자.

			3)	Delegate.Combine() 메소드.

		-	체인 해제 방법.

			1)	-= 연산자

			2)	-, = 연산자.

			3)	Delegate.Remove() 메소드.
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

delegate void Notify( string msg );

class CNotifier { public Notify _EventOccured; }

public class DelegateChainTest : MonoBehaviour {

	class CEventListener
	{
		string _name;

		public CEventListener(string name) { _name = name; }

		public void DoAction(string msg) { print(string.Format("{0} DoAction : {1}", _name, msg)); }
	}

	void Start ()
	{
		CNotifier notifier = new CNotifier ();

		CEventListener listener1 = new CEventListener ("listener 1");
		CEventListener listener2 = new CEventListener ("listener 2");
		CEventListener listener3 = new CEventListener ("listener 3");

		//	체인 연결 : +=
		print("----- += -----");
		notifier._EventOccured += listener1.DoAction;
		notifier._EventOccured += listener2.DoAction;
		notifier._EventOccured += listener3.DoAction;
		notifier._EventOccured ("+=");

		//	체인 해제 : -=
		print("----- -= -----");
		notifier._EventOccured -= listener2.DoAction;
		notifier._EventOccured ("-=");


		//	체인 연결 : +, =
		print("----- +, = -----");
		notifier._EventOccured = new Notify( listener1.DoAction ) + new Notify(listener2.DoAction);
		notifier._EventOccured ("+, =");


		//	체인 해제 : -, =
		print("----- -, = -----");
		notifier._EventOccured = notifier._EventOccured - new Notify(listener1.DoAction);
		notifier._EventOccured ("-, =");


		Notify notify1 = new Notify (listener1.DoAction);
		Notify notify2 = new Notify (listener2.DoAction);

		//	체인 연결 : Delegate.Combine()
		print("----- Delegate.Combine() -----");
		notifier._EventOccured = (Notify)Delegate.Combine(notify1, notify2);
		notifier._EventOccured ("Delegate.Combine()");

		//	체인 해제 : Delegate.Remove()
		print("----- Delegate.Remove() -----");
		notifier._EventOccured = (Notify)Delegate.Remove(notifier._EventOccured, notify1);
		notifier._EventOccured ("Delegate.Remove()");

	}
}
