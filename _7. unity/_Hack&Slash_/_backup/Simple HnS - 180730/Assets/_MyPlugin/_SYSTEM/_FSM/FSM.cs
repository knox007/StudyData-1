//=========================================================================
using UnityEngine;
//=========================================================================
public class FSM <T>  : MonoBehaviour
{
	//---------------------------------------
	private T owner;
	private IFSMState<T> currentState = null;
	private IFSMState<T> previousState = null;
	//---------------------------------------
	public IFSMState<T> CurrentState{ get {return currentState;} }
	public IFSMState<T> PreviousState{ get {return previousState;} }
	//---------------------------------------
	protected void Initialize(T owner, IFSMState<T> initialState)
	{
		this.owner = owner;
		ChangeState(initialState);
	}
	//---------------------------------------
	protected void  FSMUpdate() { if (currentState != null) currentState.Execute(owner); }
	//--------------------------------------- 
	public void  ChangeState(IFSMState<T> newState)
	{	
		previousState = currentState;
 
		if (currentState != null)
			currentState.Exit(owner);
 
		currentState = newState;
 
		if (currentState != null)
			currentState.Enter(owner);
	
	}//	public void  ChangeState(IState<T> newState)
	//--------------------------------------- 
	public void  RevertState()
	{
		if (previousState != null)
			ChangeState(previousState);
	
	}//	public void  RevertState()
	//---------------------------------------
	protected void OnDisable()
	{/*
		if (currentState != null)
			currentState.Exit(owner);
	*/
	}//	public void OnDisable()
     //---------------------------------------
    protected void Skip()
	{
		if (currentState != null)
			currentState.Skip(owner);
	
	}//	public void Skip()
	//---------------------------------------
	public override string ToString() { return currentState.ToString(); }
	//---------------------------------------

}//	public class FSM <T>  : MonoBehaviour
//=========================================================================