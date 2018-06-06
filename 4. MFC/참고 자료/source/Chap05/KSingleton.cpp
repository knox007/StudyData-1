#include <stdio.h>
#include <assert.h>
#include "vector"

#define AfxGetApp()   KSingleton<CWinApp>::GetSingleton()

template<typename T>
class KSingleton
{
private:
    static T*   ms_pSingleton;

public:
    KSingleton()
    {
        assert( NULL == KSingleton<T>::ms_pSingleton );
        KSingleton<T>::ms_pSingleton = (T*)this;
    }//KSingleton()

    ~KSingleton()
    {
        KSingleton<T>::ms_pSingleton = NULL;
    }//~KSingleton()

    static T* GetSingleton()
    {
        return ms_pSingleton;
    }//GetSingleton()
};//class KSingleton

/*static*/ template<typename T> T* KSingleton<T>::ms_pSingleton = NULL;


class CWinApp : public KSingleton<CWinApp>
{
public:
    void Print()
    {
        printf( "hello\n" );
    }//Print()
};//class CWinApp


CWinApp theApp;

void main()
{
    //KSingleton<CWinApp>::GetSingleton()->Print();
    AfxGetApp()->Print();
}//main()