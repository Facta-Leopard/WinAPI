#pragma once
#include "Player_Unit.h"
class Player2_Unit :
	public Player_Unit

{
	// 시연때문에 시간 없으니
// 프랜드선언으로 퉁치자

	friend class Player_Unit;
public :
	Player2_Unit(wstring _wString, UNIT_TYPE m_UNITTYPE, float _duration = 0.5f);
	~Player2_Unit();

public :
	virtual void Init() override;

	virtual void SelectRender() override;

	virtual void TextRender() override;

	virtual void PlaySound() override;

	virtual void MouseoverCheck() override;

	virtual void KeyCheck() override;

	virtual void SelectedCheck() override;

	virtual bool AttackRangeCheck() override;

	// 이게 문제코드인지 확인 중
	//virtual Player_Unit* AttackRangeCheck() override;

	virtual bool CollisionCheck() override;


	virtual void TemporaryFSMCheck() override;

	virtual void MakeMovingMotionUnit() override;
};