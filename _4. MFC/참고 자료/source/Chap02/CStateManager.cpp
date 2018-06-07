#include <stdio.h>

class CStateManager
{
private:
    /// 0: idle state
    /// 1: attack state
    /// 2: game over state
    int     m_iState;

    void State_Idle();
    void State_Attack();
    void State_GameOver();

public:
    CStateManager();
    void SetState(int state);
    void DoIt();
};//class CStateManager

void CStateManager::State_Idle()
{
    printf( "idle\n" );
}//CStateManager::State_Idle()

void CStateManager::State_Attack()
{
    printf( "attack\n" );
}//CStateManager::State_Attack()

void CStateManager::State_GameOver()
{
    printf( "game over\n" );
}//CStateManager::State_GameOver()

CStateManager::CStateManager()
{
    m_iState = 0; // idle state
}//CStateManager::CStateManager()

void CStateManager::SetState(int state)
{
    m_iState = state;
}//CStateManager::SetState()

void CStateManager::DoIt()
{
    switch ( m_iState )
    {
    case 0:
        State_Idle();
        break;
    case 1:
        State_Attack();
        break;
    case 2:
        State_GameOver();
        break;
    }//switch
}//CStateManager::DoIt()

void main()
{
    void (CStateManager::*fp)(int);

    fp = CStateManager::SetState;

    CStateManager   sman;
    //sman.SetState(1);    
    (sman.*fp)(1); // (1)
    sman.DoIt();
}//main()