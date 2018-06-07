#include <iostream>
#include <conio.h>

#define KEY_ESC     27

using std::cout;
using std::endl;

class CAccount
{
public:
    struct StateMap
    {
        int input;
        void (CAccount::*mfp)();
    };
    static StateMap map[];

    enum
    {
        STATE_IDLE,
        STATE_INPUT,
        STATE_WAIT_ACK
    };

public:
    int     m_iState;

    CAccount();
    void OnIdle();
    void OnInput();
    void OnWaitAck();
};//class CAccount

CAccount::CAccount()
{
    m_iState = STATE_IDLE;
}

void CAccount::OnIdle()
{
    cout << "OnIdle()" << endl;
}

void CAccount::OnInput()
{
    cout << "OnInput()" << endl;
}

void CAccount::OnWaitAck()
{
    cout << "OnWaitAck()" << endl;
}

/*static*/ CAccount::StateMap CAccount::map[] =
{
    '1', CAccount::OnIdle,
    '2', CAccount::OnInput,
    '3', CAccount::OnWaitAck,
    0, NULL // sentinel
};//CAccount::map[]

void main()
{
    int         ch = 0;
    int         i;
    CAccount    account;

    while ( ch != KEY_ESC )
    {
        ch = getch();
        i  = 0;
        while ( CAccount::map[i].input != 0 )
        {
            if ( ch == CAccount::map[i].input )
            {
                (account.*(CAccount::map[i].mfp))();
            }//if
            ++i;
        }//while
    }//while
}//main()