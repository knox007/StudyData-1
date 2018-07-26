#ifndef _STAGE_H_
#define _STAGE_H_



struct Stage
{
	int		stageInfo[12][12];	// ��
	int		PlayerPosX;			// �÷��̾���ġx
	int		PlayerPosY;			// �÷��̾���ġy
};




#define BACKGROUND	0	// ���
#define BLOCK		1	// ��
#define LANE		2	// �̵����
#define BALL		3	// ��
#define FINISH		4	// ������



int GetTotalState();

#endif