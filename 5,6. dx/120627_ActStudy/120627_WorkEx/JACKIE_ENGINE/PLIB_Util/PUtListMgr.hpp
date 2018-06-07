#pragma once 
#include "StdAfx.h"
#include "PUTListMgr.h"
//////////////////////////////////////////////////////////////////////////
//	CPUTListMgr
//---------------------------------------------------------------
template< typename T >
void	CPUTListMgr<T>::Add( T pEle )
{
	m_Bases.push_back( pEle );

}//	Add
//---------------------------------------------------------------
template< typename T >
T		CPUTListMgr<T>::Find( int nIDx )
{
	T pTmp = NULL;
	LIST_ITER(T) iterCur = GetIterBegin();

	for( int nCur = 0;iterCur != GetIterEnd(); ++iterCur, ++nCur )
	{
		pTmp	=	(*iterCur);
		if( nCur == nIDx )
		{
			return pTmp;
		}
	}

	return NULL;

}//	Find
//---------------------------------------------------------------
template< typename T >
void	CPUTListMgr<T>::Insert( int nIDx, T pEle )
{
	T pTmp = Find( nIDx );
	pTmp = pEle;

}//	Insert
//---------------------------------------------------------------
template< typename T >
void	CPUTListMgr<T>::Delete( int nIDx )
{ 
	LIST_ITER(T) iterCur = GetIterBegin();
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
	}
}//	Delete
//---------------------------------------------------------------
template< typename T >
void	CPUTListMgr<T>::DeleteAll()
{ 
	LIST_ITER(T) iterCur = GetIterBegin();

	while( iterCur != GetIterEnd() )
	{		
		iterCur = m_Bases.erase(iterCur);
	}
	m_Bases.clear();

}//	DeleteAll
//---------------------------------------------------------------
template< typename T >
int		CPUTListMgr<T>::GetIDx( T Element )
{
	LIST_ITER(T) iterCur = GetIterBegin();

	int nCur = 0;
	while( iterCur != GetIterEnd() )
	{		
		T tmp =	(*iterCur);
		if( tmp == Element )
			return nCur;
		++nCur;
	}//	while( iterCur != GetIterEnd() )

	return -1;
	
}//	GetIDx
//---------------------------------------------------------------
//	CPUTListMgr







template< typename T >
int		CPUTListMgrPt<T>::GetIDx( T* pElement )
{
	LIST_ITER(T*) iterCur = GetIterBegin();

	int nCur = 0;
	while( iterCur != GetIterEnd() )
	{
		T* pTmp = (*iterCur);
		if( pTmp == pElement )
			return nCur;

		++nCur;
		++iterCur;
	}

	return -1;
}//	GetIDx
//---------------------------------------------------------------
template< typename T >
void	CPUTListMgrPt<T>::Add( T* pElement )
{
	m_Bases.push_back( pElement );
}//	Add
//---------------------------------------------------------------
template< typename T >
void	CPUTListMgrPt<T>::Insert( int nIDx, T* pElement )
{
	T *pTmp = Find( nIDx );
	*pTmp = *pElement;	
}//	Insert
//---------------------------------------------------------------
template< typename T >
void	CPUTListMgrPt<T>::Delete( int nIDx )
{
	T* pTmp	= Find(nIDx);
	PUT_SAFE_DELETE( pTmp );
}//	Delete
//---------------------------------------------------------------
template< typename T >
void	CPUTListMgrPt<T>::DeleteAll()
{
	T *pTmp = NULL;
	LIST_ITER(T*) iterCur = GetIterBegin();

	while( iterCur != GetIterEnd() )
	{
		pTmp = (*iterCur);
		PUT_SAFE_DELETE(pTmp);
		iterCur = m_Bases.erase(iterCur);
	}
	m_Bases.clear();
}
//---------------------------------------------------------------
template< typename T >
T*		CPUTListMgrPt<T>::Find( int nIDx )
{
	LIST_ITER(T*) iterCur = GetIterBegin();
	int nCurIdx	= 0;

	while( iterCur != GetIterEnd() )
	{
		if( nIDx == nCurIdx )
		{
			T* pTmp	= (*iterCur);			
			return pTmp;
		}
		++iterCur;
		++nCurIdx;
	}

	return NULL;
}
//---------------------------------------------------------------
//	EOF