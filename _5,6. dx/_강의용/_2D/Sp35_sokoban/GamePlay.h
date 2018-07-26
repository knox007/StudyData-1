// Interface for the CGamePlay class.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_


class CGamePlay : public IGameStage
{
protected:
	LPDIRECT3DTEXTURE9		m_pTxMap;		// ��
	LPDIRECT3DTEXTURE9		m_pTxBlock;		// ��
	LPDIRECT3DTEXTURE9		m_pTxPlayer;	// �÷��̾�
	LPDIRECT3DTEXTURE9		m_pTxBall;		// ��
	LPDIRECT3DTEXTURE9		m_pTxFinish;	// ������

	INT						m_nSt;			// ��������
	INT						m_nStTot;		// ��Ż ��������
	Stage*					m_pStCur;		// ���� ����
	Stage*					m_pStDst;		// ���� ����
	INT						m_nDstTot;		// �������� ����
	INT						m_nDstCur;		// ���� �����Ͽ� ä�� ����
	

public:
	CGamePlay();
	virtual ~CGamePlay();

	virtual	INT		Init();
	virtual	void	Destroy();

	virtual	INT		FrameMove();
	virtual	void	Render();

public:
	void			SetupStage();
	BOOL			Crash(INT move);
};

#endif