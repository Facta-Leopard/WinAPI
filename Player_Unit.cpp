#include "PreCompile.h"
#include "Player_Unit.h"

#include "InGameStage.h"

#include "CameraMGR.h"

Player_Unit::Player_Unit(wstring _wString, UNIT_TYPE m_UNITTYPE, float _duration)
	: StarUnit(_wString, _duration)
	, m_VECTOR_MOVINGMOTION({})

	// �׽�Ʈ �� �ΰ����� ������ ������Ʈ
	//, m_VECTOR_FSM({})

	, m_UNITTYPE(m_UNITTYPE)
	, m_STATETYPE(IDLE_)
	, m_MOVINGMOTIONTYPE(MOVINGMOTION_TYPE::IDLE_DOWN)

	, m_DirectionAngle(0.f)

	, m_Debugging(true)

	, m_MaxHitPoint(120)
	, m_IsHitPoint(120)
	, m_wasHitPoint(0)
	, m_AttackPoint(6)


	, m_Skill_On(false)
	, m_Skill_Duration(0.f)


	, m_ViewRange(150)
	, m_AttackRange(130)

	, m_MoveSpeed(50.f)
	, m_AttackSpeed(1.f)
	, m_AttackDuration(0.1f)

	, m_ShieldUpgrade(0)
	, m_DefenseUpgrade(0)
	, m_AttackUpgrade(0)

	, m_IsSelected(false)

	, m_TARGET(nullptr)
	, m_TARGETPOSITION(nullptr)

	, m_TargetMouseover(false)
	, m_IsTagetSelected(false)

	, m_KeyOrder(false)
	, m_KeyAttack(false)
	, m_KeyMove(false)

	, m_IsOrder(false)
	, m_OrderMove(false)
	, m_OrderAttack(false)

	, m_IsUnderAttack(false)

	, m_WasMouseover(false)
	, m_IsMouseover(false)

	, m_Soundable(true)
	, m_SoundDuration(0.f)
{
	SetName(_wString);
	m_OnText = true;
	MakeMovingMotionUnit();
	StageMGR::GetInstance()->AddPlayer1UnitCount();
	Init();

	m_DirectionAngle = rand() % 360;

	// ���۽� ���� ���� ����
	m_MOVINGMOTIONTYPE = (MOVINGMOTION_TYPE)((int)(GetTickCount64() % 8));
}

Player_Unit::~Player_Unit()
{
}

void Player_Unit::Init()
{
	Sound* pSound = AssetMGR::GetInstance()->LoadSound(L"Ready", L"Sound\\Marine\\Ready.wav");

	if (nullptr != pSound)
	{
		pSound->Play(false);
		pSound->SetVolume(80.f);
	}
}

void Player_Unit::Tick()
{
	TemporaryFSMCheck(); 

	KeyCheck();
	
	//MovingMotionTypeCheck();

	MouseoverCheck();

	SelectedCheck();

	DirectionCheck();

	CollisionCheck();



	PlaySound();
}

void Player_Unit::FinalTick()
{
	TextRender();
	m_VECTOR_MOVINGMOTION[(int)m_MOVINGMOTIONTYPE]->FinalTick();
}

void Player_Unit::Render()
{	
	// ���� ���� �� �����ؽ�Ʈ�� ����� ǥ�ñ��� 
	SelectRender();

	// �������
	// ������Ʈ �̿�
	FinalTick();

	// ������ �Լ� ���� �׽�Ʈ �ڵ�
	// �� �ȵ���?
	// ������ �Լ��� �׽�Ʈ..
	// �ȵ�.. OTL.. �Լ��� ���α׷��� ���� ����..
	//SetTriggerPointerFunction2(PlayMovingMotion);
	//if (m_Trigger_PointerFunction2)
	//{
	//	(this->m_Trigger_PointerFunction2)(m_UNITTYPE, m_MOVINGMOTIONTYPE, { (LONG)tPOS.x, (LONG)tPOS.y });
	//}
}

void Player_Unit::TextRender()
{
	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
	FloatPoint tPOS = GetIngameViewPosition();
	// ���� ǥ��
	if (m_OnText)
	{
		if (m_IsSelected)
		{
			// �̸� ����
			SetTextColor(tDC, RGB(200, 250, 200));
			SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
			TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.4))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.35)
				, GetName().c_str(), (int)GetName().size()); // �޴� �ؽ�Ʈ
		}
		else if (!m_IsSelected)
		{
			// �̸� ����
			SetTextColor(tDC, RGB(50, 250, 50));
			SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
			TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.4))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.35)
				, GetName().c_str(), (int)GetName().size()); // �޴� �ؽ�Ʈ
		}

		// HP���� ����
		wstring HPwstring = L"HP";

		SetTextColor(tDC, RGB(50, 250, 50));
		SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
		TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.15))
			, ((int)tPOS.y) + (int)(GetScale().y * 0.55)
			, HPwstring.c_str(), 2); // �޴� �ؽ�Ʈ

		// ü��ǥ�� ����

		float tHPRatio = m_IsHitPoint / m_MaxHitPoint;
		int tHP = m_IsHitPoint;

		wstring HitPointwstring = std::to_wstring(tHP);
		HitPointwstring += L" / " + std::to_wstring(m_MaxHitPoint);

		SetTextColor(tDC, RGB((int)(250 * (1 - tHPRatio)), int(250 * tHPRatio), (int)(250 * (1 - tHPRatio))));
		SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
		TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.5))
			, ((int)tPOS.y) + (int)(GetScale().y * 0.75)
			, HitPointwstring.c_str(), HitPointwstring.size()); // �޴� �ؽ�Ʈ


		// ��ǥ �׽�Ʈ�� �ڵ�
		if (m_Debugging)
		{
			{
				// �þ�ǥ��
				SELECT_PEN(PEN_COLOR::YELLOW)
					SELECT_BRUSH(BRUSH_COLOR::HOLLOW)
					Ellipse(GameEngine::GetInstance()->GetMemoryDC()
						, (int)tPOS.x - m_ViewRange, (int)tPOS.y - (int)m_ViewRange
						, (int)tPOS.x + m_ViewRange, (int)tPOS.y + (int)m_ViewRange);
			}

			// �����Ÿ� ǥ��
			SELECT_PEN(PEN_COLOR::BLUE)
				SELECT_BRUSH(BRUSH_COLOR::HOLLOW)
				Ellipse(GameEngine::GetInstance()->GetMemoryDC()
					, (int)tPOS.x - m_AttackRange, (int)tPOS.y - (int)m_AttackRange
					, (int)tPOS.x + m_AttackRange, (int)tPOS.y + (int)m_AttackRange);

			// �ɸ����� x��ǥ ǥ��
			SetTextColor(tDC, RGB(100, 250, 100));
			SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
			TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.9))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.6)
				, std::to_wstring((int)(GetPosition().x)).c_str(), 3);
			// �ɸ����� y��ǥ ǥ��
			SetTextColor(tDC, RGB(100, 250, 100));
			SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
			TextOutW(tDC, ((int)(tPOS.x) + (int)(GetScale().x * 0.5))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.6)
				, std::to_wstring((int)(GetPosition().y)).c_str(), 3);

			if (m_TARGETPOSITION)
			{
				FloatPoint tP = *m_TARGETPOSITION;
				// Ÿ���� x��ǥ ǥ��
				SetTextColor(tDC, RGB(250, 100, 100));
				SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
				TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.9))
					, ((int)tPOS.y) + (int)(GetScale().y * 0.9)
					, std::to_wstring((int)tP.x).c_str(), 3);
				// �ɸ����� y��ǥ ǥ��
				SetTextColor(tDC, RGB(250, 100, 100));
				SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
				TextOutW(tDC, ((int)(tPOS.x) + (int)(GetScale().x * 0.5))
					, ((int)tPOS.y) + (int)(GetScale().y * 0.9)
					, std::to_wstring((int)tP.y).c_str(), 3);
			}
		}
	}
}

void Player_Unit::SelectRender()
{
	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
	FloatPoint tPOS = GetIngameViewPosition();
	// �ɸ��� �Ʒ� �� ��� �׸���
	if (m_IsSelected)
	{
		SELECT_PEN(PEN_COLOR::GREEN)
		SELECT_BRUSH(BRUSH_COLOR::HOLLOW)
		Ellipse(tDC
				, (int)(tPOS.x) - (int)(GetScale().x * 0.2)
				, (int)(tPOS.y) + (int)(GetScale().y * 0.1)
				, (int)(tPOS.x) + (int)(GetScale().x * 0.2)
				, (int)(tPOS.y) + (int)(GetScale().y * 0.3));
	}

	// �׸��� �׸���
	// �ʿ�� ���ȭ
	SELECT_PEN(PEN_COLOR::GRAY)
	SELECT_BRUSH(BRUSH_COLOR::GRAY)
	Ellipse(tDC
			, (int)(tPOS.x) - (int)(GetScale().x * 0.15)
			, (int)(tPOS.y) + (int)(GetScale().y * 0.075)
			, (int)(tPOS.x) + (int)(GetScale().x * 0.15)
			, (int)(tPOS.y) + (int)(GetScale().y * 0.25));

	
	if (m_Skill_On)
	{
		DrawDebugLine(PEN_COLOR::GREEN, m_WASPOSITION, m_POSITION, (float)0.6);


		int tCount = (int)(m_Skill_Duration * 30);
		// Ȥ�� �𸣴� ����ڵ�
		if (200 < tCount)
		{
			tCount = 200;
		}

		wstring wString = L"!HIGH!";

		SetTextColor(tDC, RGB(255- tCount, 50, 50));
		SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
		TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.3))
			, ((int)tPOS.y) - (int)(GetScale().y * 0.65)
			, wString.c_str(), wString.length());

	}
}

bool Player_Unit::CollisionCheck()
{
	vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);

	if (0 != tVECTOR.size())
	{
		for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
		{
			if (GetID() != (*iter)->GetID())
			{
				FloatPoint tFLOATPOINT = (*iter)->GetPosition();

				FloatPoint GAP = {};
				GAP.x = GetPosition().x - tFLOATPOINT.x;
				GAP.y = GetPosition().y - tFLOATPOINT.y;

				if ((m_SCALE.x * 0.6) > abs(GAP.x))
				{
					if ((m_SCALE.y * 0.6) > abs(GAP.y))
					{
						FloatPoint tRETREAT = m_POSITION - m_WASPOSITION;
						tRETREAT *= - 0.01f;
						if (m_Skill_On)
						{
							tRETREAT *= -1;
						}
						m_POSITION += tRETREAT;
						return true;
					}

				}
			}
		}
	}
	vector<Object*> tVECTOR2 = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);

	if (0 != tVECTOR2.size())
	{
		for (vector<Object*>::iterator iter = tVECTOR2.begin(); iter != tVECTOR2.end(); iter++)
		{
			FloatPoint tFLOATPOINT = (*iter)->GetPosition();
			FloatPoint tSCALE = (*iter)->GetScale();

			FloatPoint GAP = {};
			GAP.x = GetPosition().x - tFLOATPOINT.x;
			GAP.y = GetPosition().y - tFLOATPOINT.y;

			if ((m_SCALE.x * 0.2 + tSCALE.x * 0.4) > abs(GAP.x))
			{
				if ((m_SCALE.y * 0.2 + tSCALE.y * 0.4) > abs(GAP.y))
				{
					FloatPoint tRETREAT = m_POSITION - m_WASPOSITION;
					tRETREAT *= -0.01f;
					if (m_Skill_On)
					{
						tRETREAT *= -1;
					}
					m_POSITION += tRETREAT;
					return true;
				}

			}

		}
	}


	// ���� ��ġ ����
	m_WASPOSITION = m_POSITION;
	return false;
}

void Player_Unit::PlaySound()
{
	if (m_Dead)
	{
		Sound* pSound = AssetMGR::GetInstance()->LoadSound(L"Death", L"Sound\\Marine\\Death.wav");

		if (nullptr != pSound)
		{
			pSound->Play(false);
			pSound->SetVolume(80.f);
		}
	}


	if ((0 == m_AttackDuration) && (STATE_TYPE::ATTACK_ == m_STATETYPE))
	{
		Sound* pSoundFire = AssetMGR::GetInstance()->LoadSound(L"Fire", L"Sound\\Marine\\Fire.wav");

		if (nullptr != pSoundFire)
		{
			pSoundFire->Play(false);
			pSoundFire->SetVolume(60.f);
		}
	}

	// Ÿ�̸�
	m_SoundDuration += DELTATIME;
	if (2.0f < m_SoundDuration)
	{
		m_Soundable = true;
		m_SoundDuration = 0.f;
	}

	if (!m_Dead && m_Soundable)
	{
		if (m_IsSelected && m_Skill_On && (m_Skill_Duration == 0))
		{
			Sound* pSoundSkill = nullptr;
			int tInt = ((int)GetTickCount64()) % 2;

			switch (tInt)
			{
			case 0:
				pSoundSkill = AssetMGR::GetInstance()->LoadSound(L"StimulantPack", L"Sound\\Marine\\StimulantPack.wav");
				break;

			case 1:
			default:
				pSoundSkill = AssetMGR::GetInstance()->LoadSound(L"StimulantPack2", L"Sound\\Marine\\StimulantPack2.wav");
				if (nullptr != pSoundSkill)
				{
					pSoundSkill->Play(false);
					pSoundSkill->SetVolume(80.f);
				}
				break;
			}
			m_Soundable = false;
			return;
		}
		else if (m_IsSelected && m_IsOrder)
		{
			if (m_OrderMove)
			{
				Sound* pSoundMove = nullptr;

				int tInt = ((int)GetTickCount64()) % 4;

				switch (tInt)
				{
				case 1:
					pSoundMove = AssetMGR::GetInstance()->LoadSound(L"Move", L"Sound\\Marine\\Move.wav");
					break;
				case 2:
					pSoundMove = AssetMGR::GetInstance()->LoadSound(L"Move2", L"Sound\\Marine\\Move2.wav");
					break;
				case 3:
					pSoundMove = AssetMGR::GetInstance()->LoadSound(L"Move3", L"Sound\\Marine\\Move3.wav");
					break;
				default:
					pSoundMove = AssetMGR::GetInstance()->LoadSound(L"Move4", L"Sound\\Marine\\Move4.wav");
					break;
				}

				if (nullptr != pSoundMove)
				{
					pSoundMove->Play(false);
					pSoundMove->SetVolume(80.f);
				}
				m_Soundable = false;
				return;
			}
			if (m_OrderAttack)
			{
				Sound* pSoundAttack = nullptr;

				int tInt = ((int)GetTickCount64()) % 6;

				switch (tInt)
				{
				case 1:
					pSoundAttack = AssetMGR::GetInstance()->LoadSound(L"Attack", L"Sound\\Marine\\Attack.wav");
					break;
				case 2:
					pSoundAttack = AssetMGR::GetInstance()->LoadSound(L"Attack2", L"Sound\\Marine\\Attack2.wav");
					break;
				case 3:
					pSoundAttack = AssetMGR::GetInstance()->LoadSound(L"Attack3", L"Sound\\Marine\\Attack3.wav");
					break;
				case 4:
					pSoundAttack = AssetMGR::GetInstance()->LoadSound(L"Attack4", L"Sound\\Marine\\Attack4.wav");
					break;
				case 5:
					pSoundAttack = AssetMGR::GetInstance()->LoadSound(L"Attack5", L"Sound\\Marine\\Attack5.wav");
					break;
				case 6:
					pSoundAttack = AssetMGR::GetInstance()->LoadSound(L"Attack6", L"Sound\\Marine\\Attack6.wav");
					break;
				default:
					pSoundAttack = AssetMGR::GetInstance()->LoadSound(L"Attack7", L"Sound\\Marine\\Attack7.wav");
					break;
				}

				if (nullptr != pSoundAttack)
				{
					pSoundAttack->Play(false);
					pSoundAttack->SetVolume(80.f);
				}
				m_Soundable = false;
				return;
			}
			if (m_IsSelected)
			{
				Sound* pSound = nullptr;

				int tInt = ((int)GetTickCount64()) % 4;

				switch (tInt)
				{
				case 1:
					pSound = AssetMGR::GetInstance()->LoadSound(L"Select", L"Sound\\Marine\\Select.wav");
					break;
				case 2:
					pSound = AssetMGR::GetInstance()->LoadSound(L"Select2", L"Sound\\Marine\\Select2.wav");
					break;
				case 3:
					pSound = AssetMGR::GetInstance()->LoadSound(L"Select3", L"Sound\\Marine\\Select3.wav");
					break;
				default:
					pSound = AssetMGR::GetInstance()->LoadSound(L"Select4", L"Sound\\Marine\\Select4.wav");
					break;
				}

				if (nullptr != pSound)
				{
					pSound->Play(false);
					pSound->SetVolume(80.f);
				}
				m_Soundable = false;
				return;
			}				
		}
	}
}

void Player_Unit::MouseoverCheck()
{
	FloatPoint MOUSEPOS = KeyMGR::GetInstance()->GetMousePos();
	FloatPoint tPOS = GetIngameViewPosition();
	FloatPoint tSCALE = { GetScale().x, GetScale().y };

	m_WasMouseover = m_IsMouseover;

	// ���� ���콺���� �Ǿ����� Ȯ��
	m_IsMouseover = CheckMouseover(MOUSEPOS, tPOS, tSCALE);
	if (m_IsMouseover)
	{
		KeyMGR::GetInstance()->SetCursorType(CURSOR_TYPE::STARCRAFT_WORKING);
	}
	else
	{
		if (m_WasMouseover)
		{
			KeyMGR::GetInstance()->SetCursorType(CURSOR_TYPE::STARCRAFT_CURSOR);
		}
		m_IsMouseover = false;
	}

	// �� ���콺���� ���� Ȯ��
	vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);
	if (0 != tVECTOR.size())
	{
		for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
		{
			FloatPoint tTARGETFLOATPOINT = (*iter)->GetPosition();
			FloatPoint tTARGETSCALE = (*iter)->GetScale();
			if (CheckMouseover(MOUSEPOS, tTARGETFLOATPOINT, tTARGETSCALE))
			{
				m_TargetMouseover = true;

				if (KEY_TAP(LBTN) && (m_IsSelected || m_KeyOrder))
				{
					m_TARGET = nullptr;
					m_TARGET = dynamic_cast<Player_Unit*>(*iter);
					m_IsOrder = true;
					m_OrderAttack = true;

					m_KeyOrder = false;

				}

				break;
			}
			else
			{
				m_TargetMouseover = false;
			}
		}
	}
}

void Player_Unit::KeyCheck()
{
	if (m_Skill_On)
	{
		m_Skill_Duration += DELTATIME;
		m_MoveSpeed = 80.f;
		m_AttackSpeed = 0.5f;
	}
	if (!m_Skill_On)
	{
		m_MoveSpeed = 50.f;
		m_AttackSpeed = 1.f;
	}

	if (5.f < m_Skill_Duration)
	{
		m_Skill_Duration = 0.f;;
		m_Skill_On = false;
	}

	if (KEY_TAP(T) && m_IsSelected && !m_Skill_On)
	{
		m_Skill_On = true;
		m_IsHitPoint -= 5;
	}
	else if (KEY_TAP(A) && m_IsSelected)
	{
		m_KeyOrder = true;
		m_KeyAttack = true;
		m_KeyMove = false;
	}
	else if (KEY_RELEASED(M) && m_IsSelected)
	{
		m_KeyOrder = true;
		m_KeyMove = true;
		m_KeyAttack = false;
	}
	else if (KEY_TAP(ESC) || (KEY_RELEASED(LBTN) || KEY_RELEASED(RBTN) && !m_TargetMouseover))
	{
		m_KeyOrder = false;
		m_KeyAttack = false;
		m_KeyMove = false;
	}
}

void Player_Unit::SelectedCheck()
{
	// ���� ���ȭ�ϴٰ� �Ӹ����� ���̳�;
	// �׳� �ϵ��ڵ����� ���� �� �׷���..
	FloatPoint tPOS = GetIngameViewPosition();

	// ���콺 ���� Ű�� Ǯ���� ��
	// ���콺�� �� ���� ���� ����
	// �� ���� ���콺�� ���� ��
	if (KEY_RELEASED(LBTN) && !m_WasMouseover && !m_TargetMouseover)
	{
		// ������ �����ȿ� �ִ��� Ȯ��
		m_IsSelected = CheckInsideGetDragAndDropBox(tPOS);
		if (m_IsSelected)
		{
			m_IsOrder = true;
		}
	}
	// ���콺 ���� Ű�� Ǯ���� ��
	else if (KEY_RELEASED(LBTN) && m_WasMouseover)
	{
		// ���콺 �����Ǿ� �ְ�, ����Ű�� Ǭ ����
		m_IsSelected = true;
		m_IsOrder = true;
	}
	// ���콺 ������ Ű�� Ǯ���� ��
	// �� ���� ���콺�� �ִٸ�
	else if (KEY_RELEASED(RBTN) && m_IsSelected && m_TargetMouseover && !m_WasMouseover)
	{
		m_IsOrder = true;

		// �����̶�� Ÿ������ �ٲ�
		vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);
		if (0 != tVECTOR.size())
		{
			for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
			{
				FloatPoint tTARGETFLOATPOINT = (*iter)->GetPosition();
				FloatPoint tTARGETSCALE = (*iter)->GetScale();

				if (CheckMouseover(KeyMGR::GetInstance()->GetMousePos(), tTARGETFLOATPOINT, tTARGETSCALE))
				{
					m_TARGET = nullptr;
					m_TARGET = dynamic_cast<Player_Unit*>(*iter);
					break;
				}
			}

			m_OrderAttack = true;
		}

		// �Ʊ��̶�� Ÿ������Ʈ ��ġ�� ������
		vector<Object*> tVECTOR3 = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);
		if (0 != tVECTOR.size())
		{
			for (vector<Object*>::iterator iter = tVECTOR3.begin(); iter != tVECTOR3.end(); iter++)
			{
				FloatPoint tTARGETFLOATPOINT = (*iter)->GetPosition();
				FloatPoint tTARGETSCALE = (*iter)->GetScale();

				if (CheckMouseover(KeyMGR::GetInstance()->GetMousePos(), tTARGETFLOATPOINT, tTARGETSCALE))
				{
					*m_TARGETPOSITION = tTARGETFLOATPOINT;
					break;
				}
			}
			m_OrderMove = true;
		}
	}
	// ���콺 ������ Ű�� Ǯ���� ��
	// ���õ� ���¿���, �� ���� ���콺�� ����, �� ���� ���� ���콺�� ���ٸ�
	else if (KEY_RELEASED(RBTN) && m_IsSelected && !m_TargetMouseover && !m_WasMouseover)
	{
		m_IsOrder = true;
		m_OrderMove = true;

		// �ش���ġ ����
		FloatPoint tFLOATPOINT = KeyMGR::GetInstance()->GetMousePos();

		// ���� ������ ���� â ��ġ�� ������� �� ������ǥ
		// �� ����� ���� ������
		m_TARGETPOSITION = new FloatPoint(tFLOATPOINT);
		INGAME_POS(*m_TARGETPOSITION);

		// �ΰ��ӿ� ��ǥ�� ��ǥ ��ȯ
		//INGAME_POS(*m_TARGETPOSITION);
	}
}



void Player_Unit::MakeMovingMotionUnit()
{
	// ���ֺ� ���Ÿ�� ����
	for (int i = (int)MOVINGMOTION_TYPE::IDLE_DOWN; i <= (int)MOVINGMOTION_TYPE::ATTACK_DOWNRIGHT; i++)
	{
		MovingMotion* tMovingMotion = new MovingMotion(GetName()
			, m_UNITTYPE
			, (MOVINGMOTION_TYPE)(i)
			, GetScale());
		tMovingMotion->SetOwner(this);

		m_VECTOR_MOVINGMOTION.push_back(tMovingMotion);
	}
}

// ������
// �ÿ��� ���ϴ�!(����̸� �ƴ� �� ���..)
bool Player_Unit::ViewRangeCheck(Player_Unit* _TARGET)
{
	// �����Ÿ��ȿ� ���� �ִٸ�
	if (AttackRangeCheck())
	{
		m_STATETYPE = ATTACK_;
	}
	// �����Ÿ� �ȿ� ���� ����, Ÿ���� �ִٸ�
	else if (_TARGET)
	{
		if (!m_TARGETPOSITION)
		{
			m_TARGETPOSITION = new FloatPoint;
		}
		int tX = m_TARGETPOSITION->x - m_TARGET->GetPosition().x;
		int tY = m_TARGETPOSITION->y - m_TARGET->GetPosition().y;

		// Ÿ�ٰ��� �Ÿ��� ����
		int tDistance = (int)sqrt((tX * tX) + (tY * tY));

		// Ÿ���� �þ߰Ÿ��� �����
		if (m_ViewRange < tDistance)
		{
			_TARGET = nullptr;
			return false;
		}
		// �׷��� �ʴٸ�
		else
		{
			m_STATETYPE = MOVE_;
			return true;
		}
	}
	return false;
}

// ������

// ����.. �̰� ������ �����߻����׳�?
//Player_Unit* Player_Unit::AttackRangeCheck()
bool Player_Unit::AttackRangeCheck()
{
	// Ÿ���� �ְ�
	if (m_TARGET)
	{
		m_TARGETPOSITION = new FloatPoint;
		m_TARGETPOSITION->x = m_TARGET->GetPosition().x;
		m_TARGETPOSITION->y = m_TARGET->GetPosition().y;

		FloatPoint tPloatPoint = {};
		tPloatPoint.x = m_TARGETPOSITION->x;
		tPloatPoint.y = m_TARGETPOSITION->y;

		tPloatPoint.x -= GetPosition().x;
		tPloatPoint.y -= GetPosition().y;

		// Ÿ�ٰ��� �Ÿ��� ����
		int tDistance = (int)sqrt((tPloatPoint.x * tPloatPoint.x) + (tPloatPoint.y * tPloatPoint.y));
		if (m_AttackRange < tDistance)
		{
			return false;
		}
		return true;
	}
	// Ÿ���� ���� �� 
	// Ÿ���� �ִ��� ã��(��, �������̾)
	else if (nullptr == m_TARGET)
	{
		vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);
		if (0 != tVECTOR.size())
		{
			for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
			{
				FloatPoint tTARGETFLOATPOINT = (*iter)->GetPosition();

				tTARGETFLOATPOINT.x -= GetPosition().x;
				tTARGETFLOATPOINT.y -= GetPosition().y;

				// Ÿ�ٰ��� �Ÿ��� ����
				int tDistance = (int)sqrt((tTARGETFLOATPOINT.x * tTARGETFLOATPOINT.x)
					+ (tTARGETFLOATPOINT.y * tTARGETFLOATPOINT.y));

				if (tDistance < m_AttackRange)
				{
					return true;
					break;
				}
			}
			return false;
		}
		tVECTOR.clear();

	}
}

// ������
void Player_Unit::Attack()
{
	if(AttackRangeCheck())
	{
			m_AttackDuration += DELTATIME;
			if (m_AttackSpeed <= m_AttackDuration)
			{
				m_AttackDuration = 0;
				m_TARGET->SetHitPoint(m_AttackPoint);
				// Ÿ���� ���ݹް� �ִٴ� bool���� Ŵ
				m_TARGET->SetIsUnderAttack(true);



			}
	}
	
	}



// �̰� �������� �ʿ���� ��
void Player_Unit::Move()
{
	// Ÿ�������� �ְ�
	if (m_TARGETPOSITION)
	{
		FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();
		// �׷��� ������, Ȥ�ó� �;� üũ 
		assert(m_TARGETPOSITION);

		FloatPoint* tTARGETPOINT = new FloatPoint(*m_TARGETPOSITION);
		FloatPoint tPOINT = INGAME_POS(*tTARGETPOINT);
		FloatPoint IPOSTION = GetIngameViewPosition();
		// ���� ������ ã�Ҵ�.. ������..

	//FloatPoint tPOINT = CAMERAVIEW_POS(*m_TARGETPOSITION);

	// �ϵ� ¥������ ��� ����
	// Private���� Protect�� ��� ��� ����
		FloatPoint GAP = {};
		GAP.x = IPOSTION.x - tPOINT.x;
		GAP.y = IPOSTION.y - tPOINT.y;

		// �̵����� ����
		if (1 > abs(GAP.x))
		{
			GAP.x = 0;
		}
		if (1 > abs(GAP.y))
		{
			GAP.y = 0;
		}

		if (0 < GAP.x)
		{
			m_POSITION.x -= DELTATIME * m_MoveSpeed;
		}
		else if (0 > GAP.x)
		{
			m_POSITION.x += DELTATIME * m_MoveSpeed;
		}

		if (0 < GAP.y)
		{
			m_POSITION.y -= DELTATIME * m_MoveSpeed;
		}
		else if (0 > GAP.y)
		{
			m_POSITION.y += DELTATIME * m_MoveSpeed;
		}

		if ((0 == GAP.x) && (0 == GAP.y))
		{
			m_STATETYPE = STATE_TYPE::IDLE_;
		}
		delete tTARGETPOINT;
	}
}


// ����κ� MovingMotion �߸� ���� ���� Ȯ��������,
// ��ġ�⿣ �ð��� ���� �׳� ���� ��ü�� �ٲ�
// �Ϻ� ���� �߰����� ����
// ���׽�Ʈ ����
void Player_Unit::DirectionCheck()
{
	// �ٸ� ������� �õ�
	float tGapX = m_POSITION.x - m_WASPOSITION.x;
	float tGapY = m_POSITION.y - m_WASPOSITION.y;

	bool isRight = false
		, isLeft = false
		, isUP = false
		, isDown = false;

	if (0 < tGapX)
	{
		isRight = true;
		isLeft = false;
	}
	else if (tGapX < 0)
	{
		isRight = false;
		isLeft = true;
	}
	else
	{
		isRight = false;
		isLeft = false;
	}
	if (0 < tGapY)
	{
		isUP = true;
		isDown = false;
	}
	else if (tGapY < 0)
	{
		isUP = false;
		isDown = true;
	}
	else
	{
		isUP = false;
		isDown = false;
	}
	MOVINGMOTION_TYPE tMOVINGMOTION = m_MOVINGMOTIONTYPE;

	switch (m_STATETYPE)
	{
	case IDLE_:
		if (MOVINGMOTION_TYPE::MOVE_RIGHT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_RIGHT;
		}
		else if (MOVINGMOTION_TYPE::MOVE_DOWNRIGHT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_DOWNRIGHT;
		}
		else if (MOVINGMOTION_TYPE::MOVE_DOWN == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_DOWN;
		}
		else if (MOVINGMOTION_TYPE::MOVE_LEFT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_LEFT;
		}
		else if (MOVINGMOTION_TYPE::MOVE_UPLEFT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_UPLEFT;
		}
		else if (MOVINGMOTION_TYPE::MOVE_DOWNLEFT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_DOWNLEFT;
		}
		else if (MOVINGMOTION_TYPE::MOVE_UP == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_UP;
		}
		else if (MOVINGMOTION_TYPE::MOVE_UPRIGHT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_UPRIGHT;
		}
		break;

	case MOVE_:
		if (isRight && !isUP && !isDown)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_RIGHT;
		}
		else if (isUP && isRight)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_DOWNRIGHT;
		}
		else if (isUP && !isRight && !isLeft)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_DOWN;
		}
		else if (isUP && isLeft)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_LEFT;
		}
		else if (isLeft && !isUP && isDown)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_UPLEFT;
		}
		else if (isDown && isLeft)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_DOWNLEFT;
		}
		else if (isDown && !isRight && !isLeft)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_UP;
		}
		else if (isDown && isRight)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_UPRIGHT;
		}
		break;

	case ATTACK_:
		if (MOVINGMOTION_TYPE::MOVE_RIGHT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_RIGHT;
		}
		else if (MOVINGMOTION_TYPE::MOVE_DOWNRIGHT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_DOWNRIGHT;
		}
		else if (MOVINGMOTION_TYPE::MOVE_DOWN == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_DOWN;
		}
		else if (MOVINGMOTION_TYPE::MOVE_LEFT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_LEFT;
		}
		else if (MOVINGMOTION_TYPE::MOVE_UPLEFT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_UPLEFT;
		}
		else if (MOVINGMOTION_TYPE::MOVE_DOWNLEFT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_DOWNLEFT;
		}
		else if (MOVINGMOTION_TYPE::MOVE_UP == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_UP;
		}
		else if (MOVINGMOTION_TYPE::MOVE_UPRIGHT == tMOVINGMOTION)
		{
			m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_UPRIGHT;
		}
		break;
	}






	//FloatPoint tWASPOSITION = m_WASPOSITION;

	//float tWasTheta = 0;

	//// ������ �ζ������� ���� ������ ������.
	//tWasTheta = acosf((tWASPOSITION.x / tWASPOSITION.Length()));

	//float tIsTheta = 0;

	//if (m_TARGET)
	//{
	//	FloatPoint tFLOATPOINT = m_TARGET->GetPosition();
	//	tIsTheta = acosf((tFLOATPOINT.x / tFLOATPOINT.Length()));

	//	if (0.f > tWASPOSITION.CrossProduct(tFLOATPOINT))
	//	{
	//		tWasTheta *= -1;
	//	}
	//}
	//else if (m_TARGETPOSITION)
	//{
	//	FloatPoint tFLOATPOINT = *m_TARGETPOSITION;
	//	tIsTheta = acosf((tFLOATPOINT.x / tFLOATPOINT.Length()));

	//	if (0.f > tWASPOSITION.CrossProduct(tFLOATPOINT))
	//	{
	//		tWasTheta *= -1;
	//	}
	//}
	//else
	//{
	//	FloatPoint tFLOATPOINT = m_POSITION;
	//	tIsTheta = acosf((tFLOATPOINT.x / tFLOATPOINT.Length()));

	//	if (0.f > tWASPOSITION.CrossProduct(tFLOATPOINT))
	//	{
	//		tWasTheta *= -1;
	//	}
	//}

	//tWasTheta += tIsTheta;

	////// ������
	//////DrawDebugLine(PEN_COLOR::GREEN, tWASPOSITION, m_POSITION, 1);


	//// ���� ���� ��ȯ
	//tWasTheta *= 180.f;
	//tWasTheta /= PI;

	//m_DirectionAngle = tWasTheta;

	//m_DirectionAngle = fmod(m_DirectionAngle, 360.f);

	//// 360�� ���� �ʰ� ó��
	//if (m_DirectionAngle < 0.f)
	//{
	//	m_DirectionAngle += 360.f;
	//}


	//switch (m_STATETYPE)
	//{
	//case IDLE_:
	//	if (0.f <= m_DirectionAngle && m_DirectionAngle < 22.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_RIGHT;
	//	}
	//	else if (22.5f <= m_DirectionAngle && m_DirectionAngle < 67.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_DOWNRIGHT;
	//	}
	//	else if (67.5f <= m_DirectionAngle && m_DirectionAngle < 112.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_DOWN;
	//	}
	//	else if (112.5f <= m_DirectionAngle && m_DirectionAngle < 157.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_LEFT;
	//	}
	//	else if (157.5f <= m_DirectionAngle && m_DirectionAngle < 202.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_UPLEFT;
	//	}
	//	else if (202.5f <= m_DirectionAngle && m_DirectionAngle < 247.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_DOWNLEFT;
	//	}
	//	else if (247.5f <= m_DirectionAngle && m_DirectionAngle < 292.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_UP;
	//	}
	//	else if (292.5f <= m_DirectionAngle && m_DirectionAngle < 337.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_UPRIGHT;
	//	}
	//	else
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::IDLE_RIGHT;
	//	}
	//	break;

	//case MOVE_:
	//	if (0.f <= m_DirectionAngle && m_DirectionAngle < 22.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_RIGHT;
	//	}
	//	else if (22.5f <= m_DirectionAngle && m_DirectionAngle < 67.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_DOWNRIGHT;
	//	}
	//	else if (67.5f <= m_DirectionAngle && m_DirectionAngle < 112.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_DOWN;
	//	}
	//	else if (112.5f <= m_DirectionAngle && m_DirectionAngle < 157.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_LEFT;
	//	}
	//	else if (157.5f <= m_DirectionAngle && m_DirectionAngle < 202.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_UPLEFT;
	//	}
	//	else if (202.5f <= m_DirectionAngle && m_DirectionAngle < 247.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_DOWNLEFT;
	//	}
	//	else if (247.5f <= m_DirectionAngle && m_DirectionAngle < 292.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_UP;
	//	}
	//	else if (292.5f <= m_DirectionAngle && m_DirectionAngle < 337.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_UPRIGHT;
	//	}
	//	else
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::MOVE_RIGHT;
	//	}
	//	break;

	//case ATTACK_:
	//	if (0.f <= m_DirectionAngle && m_DirectionAngle < 22.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_RIGHT;
	//	}
	//	else if (22.5f <= m_DirectionAngle && m_DirectionAngle < 67.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_DOWNRIGHT;
	//	}
	//	else if (67.5f <= m_DirectionAngle && m_DirectionAngle < 112.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_DOWN;
	//	}
	//	else if (112.5f <= m_DirectionAngle && m_DirectionAngle < 157.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_LEFT;
	//	}
	//	else if (157.5f <= m_DirectionAngle && m_DirectionAngle < 202.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_UPLEFT;
	//	}
	//	else if (202.5f <= m_DirectionAngle && m_DirectionAngle < 247.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_DOWNLEFT;
	//	}
	//	else if (247.5f <= m_DirectionAngle && m_DirectionAngle < 292.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_UP;
	//	}
	//	else if (292.5f <= m_DirectionAngle && m_DirectionAngle < 337.5f)
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_UPRIGHT;
	//	}
	//	else
	//	{
	//		m_MOVINGMOTIONTYPE = MOVINGMOTION_TYPE::ATTACK_RIGHT;
	//	}
	//	break;
	//}

}

// FSM �׽�Ʈ�� �ڵ�
// ���� FSM ���� ������Ʈ ��������
// ���� �÷��̾�2 ���� ����� �����ؾߵ� ��
void Player_Unit::TemporaryFSMCheck()
{
	// ü�±�� ���º�ȭ
	m_wasHitPoint = m_IsHitPoint;

	// ü���� 0 �̸��̶��
	if (m_IsHitPoint <= 0)
	{
		m_Dead = true;
		m_STATETYPE = DIE_;
	}

	switch (m_STATETYPE)
	{
	case IDLE_:
		if (m_KeyOrder)
		{
			if (KEY_TAP(LBTN) || KEY_TAP(RBTN))
			{
				if (m_KeyAttack)
				{
					m_STATETYPE = ATTACK_;
					m_KeyAttack = false;
					m_KeyOrder = false;
				}
				else if (m_KeyMove)
				{
					m_STATETYPE = MOVE_;
					m_KeyMove = false;
					m_KeyOrder = false;
				}
			}
		}
		if (m_IsOrder)
		{
			if (m_OrderAttack)
			{
				m_STATETYPE = ATTACK_;

				m_OrderAttack = false;

			}
			else if (m_OrderMove)
			{
				m_STATETYPE = MOVE_;

				m_OrderMove = false;
			}
			m_IsOrder = false;
		}
		else
		{

			vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);
			if (0 != tVECTOR.size())
			{
				for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
				{
					FloatPoint tTARGETFLOATPOINT = (*iter)->GetPosition();

					tTARGETFLOATPOINT.x -= GetPosition().x;
					tTARGETFLOATPOINT.y -= GetPosition().y;

					// Ÿ�ٰ��� �Ÿ��� ����
					int tDistance = (int)sqrt((tTARGETFLOATPOINT.x * tTARGETFLOATPOINT.x) + (tTARGETFLOATPOINT.y * tTARGETFLOATPOINT.y));

					if (tDistance <= m_AttackRange)
					{
						m_TARGET = dynamic_cast<Player_Unit*>(*iter);

						break;
					}
				}
			}
			if (AttackRangeCheck())
			{

				m_STATETYPE = ATTACK_;
			}
		}



		break;

	case MOVE_:
		if (m_KeyOrder)
		{
			if (KEY_TAP(LBTN) || KEY_TAP(RBTN))
			{
				if (m_KeyAttack)
				{
					m_STATETYPE = ATTACK_;
					m_KeyAttack = false;
					m_KeyOrder = false;
				}
				else if (m_KeyMove)
				{
					m_STATETYPE = MOVE_;
					m_KeyMove = false;
					m_KeyOrder = false;
				}
				m_KeyOrder = false;
			}
		}
		else if (m_IsOrder)
		{
			if (m_OrderAttack)
			{
				m_STATETYPE = ATTACK_;

				m_OrderAttack = false;

			}
			else if (m_OrderMove)
			{
				m_STATETYPE = MOVE_;

				m_OrderMove = false;
			}
			m_IsOrder = false;
		}
		else
		{
			// Ÿ�������� �ִٴ� �������� ������
			if (m_TARGETPOSITION)
			{
				//// Ÿ���� �ְ�, ���ݹ޴� ���̶��
				//if (m_TARGET && m_IsUnderAttack)
				//{
				//	 // �� �ڵ尡 ������ �ִ°� ������..
				//	m_STATETYPE = ATTACK_;
				//	m_IsUnderAttack = false;
				//}
			 //Ÿ���� ������, ���ݹ޴� ���� �ƴ϶��
				/*if (m_TARGET && !m_IsUnderAttack)
				{
					Move();
				}*/
				// Ÿ���� ����, Ÿ���������� �ִٸ�
	/*			if (nullptr == m_TARGET)
				{*/
				Move();
				/*		}
				*/
			}
			else
			{
				m_STATETYPE = IDLE_;
			}
		}
		break;

	case ATTACK_:
		if (m_KeyOrder)
		{
			if (KEY_TAP(LBTN) || KEY_TAP(RBTN))
			{
				if (m_KeyAttack)
				{
					m_STATETYPE = ATTACK_;
					m_KeyAttack = false;
					m_KeyOrder = false;
				}
				else if (m_KeyMove)
				{
					m_STATETYPE = MOVE_;
					m_KeyMove = false;
					m_KeyOrder = false;
				}
				m_KeyOrder = false;
			}
		}
		else if (m_IsOrder)
		{
			if (m_OrderAttack)
			{
				m_STATETYPE = ATTACK_;

				m_OrderAttack = false;

			}
			else if (m_OrderMove)
			{
				m_STATETYPE = MOVE_;

				m_OrderMove = false;
			}
			m_IsOrder = false;
		}
		else
		{
			// Ÿ���� ���� ���
			if (m_TARGET)
			{
				Attack();
			}
			// Ÿ���� ����, Ÿ���������� �ִٸ�
			else if (nullptr != m_TARGET && m_TARGETPOSITION)
			{
				m_STATETYPE = MOVE_;
			}
		}
		break;

	case DIE_:
		m_Dead = true;
		break;
	case STATE_EOL:
	default:
		m_Dead = true;
		break;
	}

}





// ������ �Լ� ���

// Ʈ���ſ� ������ �Լ�(�����ε� : �ʻ�ȭ����� ������ �Լ�)
void Player_Unit::SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction)
{
	// �ܺ� �Լ� �����͸� m_TriggerFunction�� �Ҵ�
	m_Trigger_PointerFunction = PointFunction;
}

// Ʈ���ſ� ������ �Լ�(�������� ������ �Լ�)
void Player_Unit::SetTriggerPointerFunction2(std::function<void(UNIT_TYPE, MOVINGMOTION_TYPE, POINT)> PointFunction)
{
	m_Trigger_PointerFunction2 = PointFunction;
}

// ���� ����� ������ �Լ�
void Player_Unit::SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction)
{
	m_Sound_PointerFunction = PointFunction;
}

// ���� ����� ������ �Լ�(������ ���ϴ� ������ �Լ�)
void Player_Unit::SetSoundPointerFunction2(std::function<void(UNIT_TYPE, MOVINGMOTION_TYPE)> PointFunction)
{
	m_Sound_PointerFunction2 = PointFunction;
}