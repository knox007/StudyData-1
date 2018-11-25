//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	스테이트 패턴
	---------------

		-	상황발생

			-	내부적인 상태에 따라 다른 동작을 해야하는 경우,

				일반적으로 각 동작에 대한 분기를 고려하게 됨.

*/
//=================================================
/*
enum NPC_STATE
{
	NPCSTATE_WANDERING = 0,	//배회하기 
	NPCSTATE_DETECTING,		//적탐지루틴검사
	NPCSTATE_RUSH,			//돌격모드. 타겟에게돌격하는상태 
	NPCSTATE_FIGHT,			//전투모드타겟을적으로
};

class Npc
{
	NPC_STATE m_NpcState; 

	void Wandering();
	void Detecting();
	void Rush();
	void Fight();

public:
		void SetNpcState(NPC_STATE NpcState){ m_NpcState = NpcState; }		
		
		void Act()
		{
			switch(m_NpcState)
			{
				case NPCSTATE_WANDERING: Wandering(); break;
				
				case NPCSTATE_DETECTING: Detecting(); break;
				
				case NPCSTATE_RUSH: Rush(); break;
				
				case NPCSTATE_FIGHT: Fight(); break;
			}
		}
};

int main()
{
	Npc npc;

	npc.SetNpcState(NPCSTATE_WANDERING);
	npc.Act();

	npc.SetNpcState(NPCSTATE_DETECTING);
	npc.Act();

	npc.SetNpcState(NPCSTATE_FIGHT);
	npc.Act();

	return 0;
}
//*/
//=================================================
/*

	
	스테이트 패턴 적용

		-	상태에 따라 다른 함수 호출을 하는 것이 아니라,
		
			각 상태별 동작을 상태 객체로 정의 해두고 상태가 변했을 때 객체를 교체.
			
			그리고 설정된 상태 객체의 함수를 호출 함으로써 분기문을 제거한다.
		

*/
//=================================================
/*
//---------------------
class NpcState
{
public: 
	virtual void Act() = 0;
};
//---------------------
class NpcStateWandering : public NpcState
{
public: 
	virtual void Act()
	{ 
		//배회동작
	}
};
//---------------------
class NpcStateDetecting : public NpcState
{
public:
	virtual void Act()
	{
		//탐지동작
	}
};
//---------------------
class NpcStateRush : public NpcState
{
public:
	virtual void Act()
	{
		//러쉬동작
	}
};
//---------------------
class NpcStateFight : public NpcState
{
public:
	virtual void Act()
	{
		//전투동작
	}
};
//---------------------
class Npc
{
	NpcState* m_pNpcState;
public:
	void SetNpcState(NpcState *pNpcState)
	{
		m_pNpcState = pNpcState;
	}

	void Act()
	{
		if (m_pNpcState)
		{
			m_pNpcState->Act();
		}
	}
};
//*/
//=================================================
/*	적용

int main()
{
	Npc npc;

	npc.SetNpcState(new NpcStateFight());
	npc.Act();
	
	npc.SetNpcState(new NpcStateWandering());
	npc.Act();
	
	return 0;
}
*/
//=================================================
/*
	유한 상태 머신은 상태패턴을 확장한 것.
	
		유한상태머신 참고 링크	
		http://blog.naver.com/jerrypoiu/221235988023

		uml
		http://1ilsang.blog.me/221104669002

*/
//=================================================