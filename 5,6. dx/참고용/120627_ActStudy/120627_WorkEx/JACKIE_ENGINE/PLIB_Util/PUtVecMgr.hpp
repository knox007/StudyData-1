#include "StdAfx.h"
#include "PUTVecMgr.h"
#include "PUTCommon.h"
//////////////////////////////////////////////////////////////////////////
//	CPUTVecMgr
//---------------------------------------------------------------
template< typename T >
void	CPUTVecMgr<T>::Add( T Ele )
{
	m_Bases.push_back( Ele );

}//	Add
//---------------------------------------------------------------
template< typename T >
T		CPUTVecMgr<T>::Find( int nIDx )
{
	return m_Bases[nIDx];
}//	Find
//---------------------------------------------------------------
template< typename T >
void	CPUTVecMgr<T>::Insert( int nIDx, T Ele )
{
	m_Bases[nIDx] = Ele;

}//	Insert
//---------------------------------------------------------------
template< typename T >
void	CPUTVecMgr<T>::Delete( int nIDx )
{
	VEC_ITER(T) iterCur = GetIterBegin();
	int nCurIdx = 0;

	while( iterCur != GetIterEnd() )
	{
		if( nIDx == nCurIdx )
		{
			m_Bases.erase( iterCur );
			break;
		}
		++nCurIdx;
		++iterCur;

	}//	while( iterCur != GetIterEnd() )

}//	Delete
//---------------------------------------------------------------
template< typename T >
void	CPUTVecMgr<T>::DeleteAll()
{	
	VEC_ITER(T) iterCur = GetIterBegin();

	while( iterCur != m_Bases.end() )
	{		
		iterCur = m_Bases.erase(iterCur);		
	}
	m_Bases.clear();

}//	DeleteAll
//---------------------------------------------------------------
template< typename T >
int		CPUTVecMgr<T>::GetIDx( T Element )
{
	VECTMPITER iterCur	= GetIterBegin();

	int nCur = 0;
	while( iterCur != GetIterEnd() )
	{
		T tmp = (*iterCur);
		if( tmp == Element )
			return nCur;

		++nCur;

	}//	while( iterCur != m_Bases.end() )

	return -1;
}//	GetIDx
//---------------------------------------------------------------
//	CPUTVecMgr





template< typename T >
int	CPUTVecMgrPt<T>::GetIDx( T* pElement )
{
	VEC_ITER(T*) iterCur	= GetIterBegin();

	int nCur = 0;
	while( iterCur != GetIterEnd() )
	{
		T* pTmp = (*iterCur);
		if( pTmp == pElement )
			return nCur;

		++nCur;
		++iterCur;

	}//	while( iterCur != m_Bases.end() )

	return -1;
}//	GetIDx
//---------------------------------------------------------------
template< typename T >
void	CPUTVecMgrPt<T>::Add( T* pElement )
{
	m_Bases.push_back( pElement );
}//	Add
//---------------------------------------------------------------
template< typename T >
T*		CPUTVecMgrPt<T>::Find( int nIDx )
{
	return m_Bases[nIDx];
}//	Find
//---------------------------------------------------------------
template< typename T >
void	CPUTVecMgrPt<T>::Delete( int nIDx )
{
	VEC_ITER(T*)	iterCur = GetIterBegin();
	int nCurIdx = 0;
	while( iterCur != GetIterEnd() )
	{
		if( nIDx == nCurIdx )
		{
			T* pTmp = m_Bases[nIDx];
			PUT_SAFE_DELETE( pTmp );
			m_Bases.erase( iterCur );
			break;
		}
		++nCurIdx;
		++iterCur;

	}//	while( iterCur != GetIterEnd() )
}//	Delete
//---------------------------------------------------------------
template< typename T >
void	CPUTVecMgrPt<T>::DeleteAll()
{
	T*	pTmp	=	NULL;
	VEC_ITER(T*) iterCur	=	GetIterBegin();

	while( iterCur != GetIterEnd() )
	{		
		pTmp	=	(*iterCur);
		PUT_SAFE_DELETE( pTmp );	
		iterCur = m_Bases.erase( iterCur );
	}
	m_Bases.clear();
}//	DeleteAll
//---------------------------------------------------------------
//	EOF