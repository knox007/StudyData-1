//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	������Ʈ ����
	---------------

		-	��Ȳ�߻�

			-	�������� ���¿� ���� �ٸ� ������ �ؾ��ϴ� ���,

				�Ϲ������� �� ���ۿ� ���� �б⸦ ����ϰ� ��.

*/
//=================================================
/*
enum NPC_STATE
{
	NPCSTATE_WANDERING = 0,	//��ȸ�ϱ� 
	NPCSTATE_DETECTING,		//��Ž����ƾ�˻�
	NPCSTATE_RUSH,			//���ݸ��. Ÿ�ٿ��Ե����ϴ»��� 
	NPCSTATE_FIGHT,			//�������Ÿ����������
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

	
	������Ʈ ���� ����

		-	���¿� ���� �ٸ� �Լ� ȣ���� �ϴ� ���� �ƴ϶�,
		
			�� ���º� ������ ���� ��ü�� ���� �صΰ� ���°� ������ �� ��ü�� ��ü.
			
			�׸��� ������ ���� ��ü�� �Լ��� ȣ�� �����ν� �б⹮�� �����Ѵ�.
		

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
		//��ȸ����
	}
};
//---------------------
class NpcStateDetecting : public NpcState
{
public:
	virtual void Act()
	{
		//Ž������
	}
};
//---------------------
class NpcStateRush : public NpcState
{
public:
	virtual void Act()
	{
		//��������
	}
};
//---------------------
class NpcStateFight : public NpcState
{
public:
	virtual void Act()
	{
		//��������
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
/*	����

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
	���� ���� �ӽ��� ���������� Ȯ���� ��.
	
		���ѻ��¸ӽ� ���� ��ũ	
		http://blog.naver.com/jerrypoiu/221235988023

		uml
		http://1ilsang.blog.me/221104669002

*/
//=================================================