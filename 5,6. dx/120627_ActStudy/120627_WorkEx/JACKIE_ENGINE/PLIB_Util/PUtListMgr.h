#pragma once
#include <list>

#define LIST_CON(T)		std::list<T>
#define LIST_ITER(T)	std::list<T>::iterator
//---------------------------------------------------------------------------------------
template< typename T >
class CPUTListMgr
{
public:
	CPUTListMgr()			{ InitMembers(); }
	virtual ~CPUTListMgr()	{ ClearMembers(); }

	void	InitMembers()			{ m_Bases.clear(); }
	void	ClearMembers()		{ DeleteAll(); }

	size_t	GetSize()				{ return m_Bases.size(); }	
	int		GetIDx( T Element );
	void	Add( T pEle );
	void	Insert( int nIDx, T pEle );
	void	Delete( int nIDx );
	void	DeleteAll();	
	T		Find( int nIDx );

	typename LIST_ITER(T)	GetIterBegin()	{ return m_Bases.begin(); }
	typename LIST_ITER(T)	GetIterEnd()	{ return m_Bases.end(); }
	

private:
	LIST_CON(T)	m_Bases;
};
//	CPUTListMgr
//---------------------------------------------------------------------------------------
template< typename T >
class CPUTListMgrPt
{
public:
	CPUTListMgrPt()					{}
	virtual ~CPUTListMgrPt(void)	{}
	virtual	void	InitMembers()			{ m_Bases.clear(); }
	virtual void	ClearMembers()		{ DeleteAll(); }

	size_t			GetSize()				{ return m_Bases.size(); }
	int				GetIDx( T* pElement );
	virtual	void	Add( T* pElement );
	virtual	void	Insert( int nIDx, T* pElement );
	virtual void	Delete( int nIDx );
	virtual void	DeleteAll();
	virtual T*		Find( int nIDx );

	typename LIST_ITER(T*)	GetIterBegin()	{ return m_Bases.begin(); }
	typename LIST_ITER(T*)	GetIterEnd()	{ return m_Bases.end(); }

private:
	LIST_CON(T*)		m_Bases;
};

#include "PUTListMgr.hpp"

//EOF
