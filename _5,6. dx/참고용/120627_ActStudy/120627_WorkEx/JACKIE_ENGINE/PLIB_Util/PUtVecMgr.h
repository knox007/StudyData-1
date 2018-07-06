#pragma once
#include <vector>

#define VEC_CONT(T)	std::vector<T>
#define VEC_ITER(T)	std::vector<T>::iterator

//---------------------------------------------------------------------------------------
template< typename T >
class CPUTVecMgr
{
public:

	CPUTVecMgr()				{}
	virtual ~CPUTVecMgr(void)	{}
	virtual	void	InitMembers()		{ m_Bases.clear(); }
	virtual void	ClearMembers()	{ DeleteAll(); }

	size_t			GetSize()			{ return m_Bases.size(); }
	int				GetIDx( T Element );
	virtual	void	Add( T pElement );
	virtual	void	Insert( int nIDx, T pElement );
	virtual void	Delete( int nIDx );
	virtual void	DeleteAll();
	virtual T		Find( int nIDx );

	typename VEC_ITER(T)	GetIterBegin()	{ return m_Bases.begin(); }
	typename VEC_ITER(T)	GetIterEnd()	{ return m_Bases.end(); }

private:	
	VEC_CONT(T)	m_Bases;
};
//	CPUTVecMgr
//---------------------------------------------------------------------------------------
template< typename T >
class CPUTVecMgrPt
{
public:
	CPUTVecMgrPt()				{InitMembers();}
	virtual ~CPUTVecMgrPt(void)	{}
	virtual	void	InitMembers()		{ DeleteAll(); }
	virtual void	ClearMembers()	{ DeleteAll(); }

	size_t			GetSize()			{ return m_Bases.size(); }
	int				GetIDx( T* pElement );
	virtual	void	Add( T* pElement );	
	virtual void	Delete( int nIDx );
	virtual void	DeleteAll();
	virtual T*		Find( int nIDx );
	virtual void	Clear()	{ m_Bases.clear(); }

	typename VEC_ITER(T*)	GetIterBegin()	{ return m_Bases.begin(); }
	typename VEC_ITER(T*)	GetIterEnd()	{ return m_Bases.end(); }

private:
	VEC_CONT(T*)		m_Bases;
};
//CPUTVecMgrPt
//---------------------------------------------------------------------------------------
#include "PUTVecMgr.hpp"
