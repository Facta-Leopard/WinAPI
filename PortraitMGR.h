#pragma once
#include "PreCompile.h"
#include "MovingMotion.h"
#include "Portrait.h"

class PortraitMGR
{
	SINGLE(PortraitMGR);

	friend class Player1Building;
	friend class Player1Unit;

private:
	//wstring						m_UNITNAME;

public:	
	// �ʻ�ȭ �������
	// ���� �׽�Ʈ
	////vector<pair<UNIT_TYPE, MovingMotion>>		m_VECTOR_PAIR_UNITTYPE_PORTRAIT;


	//�ȵǼ� InGameStage�� ������
	//vector<Portrait*>							m_VECTOR_PORTRAIT;

public:

	void Init();

	void Render(UNIT_TYPE _UNITTYPE, bool _talk);

	// �ȵǼ� InGameStage�� ������
	//void MakePortraitUnit();



	// �׽�Ʈ �ڵ�
	//void MakeMovingMotionUnit(wstring _UNITNAME, UNIT_TYPE _UNITTYPE, FloatPoint _Scale);

	//void PlayMovingMotion(UNIT_TYPE _UNITTYPE, MOVINGMOTION_TYPE _MOVINGMOTIONTYPE, POINT _POSITION);
};