#pragma once
#include "Player_Unit.h"
class Player2_Unit :
	public Player_Unit

{
	// �ÿ������� �ð� ������
// �����弱������ ��ġ��

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

	// �̰� �����ڵ����� Ȯ�� ��
	//virtual Player_Unit* AttackRangeCheck() override;

	virtual bool CollisionCheck() override;


	virtual void TemporaryFSMCheck() override;

	virtual void MakeMovingMotionUnit() override;
};