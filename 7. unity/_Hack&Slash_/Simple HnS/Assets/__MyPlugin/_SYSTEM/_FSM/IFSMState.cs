//=====================================================
public interface IFSMState<T>
{	
	void Enter(T e);

	void Execute(T e);

	void Exit(T e);

	void Skip(T e);

}//	public interface IFSMState<T>
//=====================================================