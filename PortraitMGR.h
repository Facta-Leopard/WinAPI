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
	// 초상화 재생관련
	// 향후 테스트
	////vector<pair<UNIT_TYPE, MovingMotion>>		m_VECTOR_PAIR_UNITTYPE_PORTRAIT;


	//안되서 InGameStage에 구현중
	//vector<Portrait*>							m_VECTOR_PORTRAIT;

public:

	void Init();

	void Render(UNIT_TYPE _UNITTYPE, bool _talk);

	// 안되서 InGameStage에 구현중
	//void MakePortraitUnit();



	// 테스트 코드
	//void MakeMovingMotionUnit(wstring _UNITNAME, UNIT_TYPE _UNITTYPE, FloatPoint _Scale);

	//void PlayMovingMotion(UNIT_TYPE _UNITTYPE, MOVINGMOTION_TYPE _MOVINGMOTIONTYPE, POINT _POSITION);
};