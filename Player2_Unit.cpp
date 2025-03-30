#include "PreCompile.h"
#include "Player2_Unit.h"

#include "InGameStage.h"

Player2_Unit::Player2_Unit(wstring _wString, UNIT_TYPE m_UNITTYPE, float _duration)
	: Player_Unit(_wString, m_UNITTYPE, _duration)
{
	SetName(_wString);
	m_MaxHitPoint = 150;
	m_IsHitPoint = 150;
	m_ViewRange = 180;
	m_AttackRange = 140;
	m_AttackPoint = 8;

	m_OnText = true;
	MakeMovingMotionUnit();
	StageMGR::GetInstance()->AddPlayer1UnitCount();
	Init();
}

Player2_Unit::~Player2_Unit()
{
}

void Player2_Unit::Init()
{
	Sound* pSound = AssetMGR::GetInstance()->LoadSound(L"HydraliskReady", L"Sound\\Hydralisk\\Ready.wav");

	if (nullptr != pSound)
	{
		pSound->Play(false);
		pSound->SetVolume(80.f);
	}
}

void Player2_Unit::SelectRender()
{
	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
	FloatPoint tPOS = GetIngameViewPosition();
	// �ɸ��� �Ʒ� �� ��� �׸���
	if (m_IsSelected)
	{
		SELECT_PEN(PEN_COLOR::RED)
			SELECT_BRUSH(BRUSH_COLOR::RED)
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

	// ���� ǥ��
	if (m_OnText)
	{
		if (m_IsSelected)
		{
			// �ؽ�Ʈ ����
			SetTextColor(tDC, RGB(250, 200, 200));
			SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
			TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.35)
				, GetName().c_str(), (int)GetName().size()); // �޴� �ؽ�Ʈ
		}
		else
		{
			// �ؽ�Ʈ ����
			SetTextColor(tDC, RGB(250, 50, 50));
			SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
			TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.35)
				, GetName().c_str(), (int)GetName().size()); // �޴� �ؽ�Ʈ
		}


	}
}

void Player2_Unit::TextRender()
{
	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
	FloatPoint tPOS = GetIngameViewPosition();
	// ���� ǥ��
	if (m_OnText)
	{
		if (m_IsSelected)
		{
			// �̸� ����
			SetTextColor(tDC, RGB(250, 200, 200));
			SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
			TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.35)
				, GetName().c_str(), (int)GetName().size());
		}
		else
		{
			// �̸� ����
			SetTextColor(tDC, RGB(250, 50, 50));
			SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
			TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.35)
				, GetName().c_str(), (int)GetName().size());
		}

		// HP���� ����
		wstring HPwstring = L"HP";

		SetTextColor(tDC, RGB(50, 250, 50));
		SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
		TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.15))
			, ((int)tPOS.y) + (int)(GetScale().y * 0.55)
			, HPwstring.c_str(), 2); // �޴� �ؽ�Ʈ

		// ü��ǥ�� ����

		float tHPRatio = (float)(m_IsHitPoint / m_MaxHitPoint);
		int tHP = m_IsHitPoint;

		wstring HitPointwstring = std::to_wstring(tHP);
		HitPointwstring += L" / " + std::to_wstring(m_MaxHitPoint);

		SetTextColor(tDC, RGB((int)(250 * (1 - tHPRatio)), int(250 * tHPRatio), (int)(250 * (1 - tHPRatio))));
		SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
		TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.5))
			, ((int)tPOS.y) + (int)(GetScale().y * 0.75)
			, HitPointwstring.c_str(), (int)HitPointwstring.size()); // �޴� �ؽ�Ʈ


		// ��ǥ �׽�Ʈ�� �ڵ�
		if (m_Debugging)
		{
			{// �þ�ǥ��
				SELECT_PEN(PEN_COLOR::YELLOW)
					SELECT_BRUSH(BRUSH_COLOR::HOLLOW)
					Ellipse(GameEngine::GetInstance()->GetMemoryDC()
						, (int)tPOS.x - m_ViewRange, (int)tPOS.y - (int)m_ViewRange
						, (int)tPOS.x + m_ViewRange, (int)tPOS.y + (int)m_ViewRange);
			}
			// �����Ÿ� ǥ��
			SELECT_PEN(PEN_COLOR::RED)
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

void Player2_Unit::PlaySound()
{
	if (m_STATETYPE == STATE_TYPE::ATTACK_)
	{
		Sound* pSoundYes = nullptr;

		int tInt = ((int)GetTickCount64()) % 3;

		if (0.1f == m_AttackDuration)
		{
			switch (tInt)
			{
			case 1:
				pSoundYes = AssetMGR::GetInstance()->LoadSound(L"Yes", L"Sound\\Hydralisk\\Yes.wav");
					break;
			case 2:
				pSoundYes = AssetMGR::GetInstance()->LoadSound(L"Yes2", L"Sound\\Hydralisk\\Yes.wav");
					break;
			default:
				pSoundYes = AssetMGR::GetInstance()->LoadSound(L"Move4", L"Sound\\Hydralisk\\Yes.wav");
				break;
			}
		}

		if (nullptr != pSoundYes)
		{
			pSoundYes->Play(false);
			pSoundYes->SetVolume(60.f);
		}

	}
	if (m_Dead)
	{
		Sound* pSound = AssetMGR::GetInstance()->LoadSound(L"HydraliskDeath", L"Sound\\Hydralisk\\Death.wav");

		if (nullptr != pSound)
		{
			pSound->Play(false);
			pSound->SetVolume(80.f);
		}
	}


}

void Player2_Unit::MouseoverCheck()
{
	FloatPoint MOUSEPOS = KeyMGR::GetInstance()->GetMousePos();
	FloatPoint tPOS = GetIngameViewPosition();
	FloatPoint tSCALE = { GetScale().x, GetScale().y };

	m_WasMouseover = m_IsMouseover;

	m_IsMouseover = CheckMouseover(MOUSEPOS, tPOS, tSCALE);
	if (m_IsMouseover)
	{
		KeyMGR::GetInstance()->SetCursorType(CURSOR_TYPE::STARCRAFT_CURSOR_RED);
	}
	else
	{
		if (m_WasMouseover)
		{
			KeyMGR::GetInstance()->SetCursorType(CURSOR_TYPE::STARCRAFT_CURSOR);
		}
		m_IsMouseover = false;
	}
}

void Player2_Unit::KeyCheck()
{
}

void Player2_Unit::SelectedCheck()
{
	FloatPoint tPOS = GetIngameViewPosition();
	if (KEY_RELEASED(LBTN) && m_WasMouseover)
	{
		m_IsSelected = true;
	}
	// ���콺 ���� Ű�� Ǯ���� ��
	else if ((KEY_RELEASED(LBTN) || KEY_RELEASED(RBTN) ) && !m_WasMouseover && m_IsSelected)
	{
		m_IsSelected = false;
	}
}

// ������ �Ϸ�
// �ڵ� �����ִ��� Ȯ�� ��
bool Player2_Unit::AttackRangeCheck()
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
		vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);
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
				}
			}
		}
		tVECTOR.clear();
		return false;
	}
}

bool Player2_Unit::CollisionCheck()
{
	if (m_STATETYPE == STATE_TYPE::MOVE_)
	{
		vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);

		if (0 != tVECTOR.size())
		{
			for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
			{
				if (dynamic_cast<Player_Unit*>(*iter)->m_STATETYPE == STATE_TYPE::MOVE_)
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
							if ((0 == GAP.x) && (0 == GAP.y))
							{
							}
							else
							{
								m_POSITION = m_WASPOSITION;
							}
							return true;
						}

					}
				}
				}
			}
		}
		vector<Object*> tVECTOR2 = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);

		if (0 != tVECTOR2.size())
		{
			for (vector<Object*>::iterator iter = tVECTOR2.begin(); iter != tVECTOR2.end(); iter++)
			{
				FloatPoint tFLOATPOINT = (*iter)->GetPosition();
				FloatPoint tSCALE = (*iter)->GetScale();

				FloatPoint GAP = {};
				GAP.x = GetPosition().x - tFLOATPOINT.x;
				GAP.y = GetPosition().y - tFLOATPOINT.y;
				if ((m_SCALE.x * 0.2 + tSCALE.x * 0.3) > abs(GAP.x))
				{
					if ((m_SCALE.y * 0.2 + tSCALE.y * 0.3) > abs(GAP.y))
					{
						if ((m_SCALE.y * 0.4) > abs(GAP.y))
						{
							if ((0 == GAP.x) && (0 == GAP.y))
							{
								m_POSITION - 10;
							}
							else
							{
								m_POSITION = m_WASPOSITION;
							}
							return true;
						}
					}

				}

			}
		}

	}

	// ���� ��ġ ����
	m_WASPOSITION = m_POSITION;
	return false;
}

void Player2_Unit::TemporaryFSMCheck()
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

			if (AttackRangeCheck())
			{
				Attack();
				//m_STATETYPE = ATTACK_;
			}
			else if (ViewRangeCheck(m_TARGET))
			{
				FloatPoint tTARGETPOSITION = m_TARGET->GetPosition();
				*m_TARGETPOSITION = tTARGETPOSITION;

				Move();
			}
			{

				vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER1);
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
							m_TARGET = nullptr;
							m_TARGET = dynamic_cast<Player_Unit*>(*iter);

							break;
						}
					}
				}



			}



		break;

	case MOVE_:
		// Ÿ�������� �ִٴ� �������� ������
		if (m_TARGETPOSITION)
		{

			// Ÿ���� �ְ�, ���ݹ޴� ���̶��
			if (m_TARGET && m_IsUnderAttack)
			{
				m_STATETYPE = ATTACK_;
				m_IsUnderAttack = false;
			}// Ÿ���� ������, ���ݹ޴� ���� �ƴ϶��
			else if (m_TARGET)
			{
				if (AttackRangeCheck())
				{
					m_STATETYPE = ATTACK_;
				}
				else
				{
					m_STATETYPE = IDLE_;
					
				}
			}
			// Ÿ���� ����
			else if (nullptr == m_TARGET)
			{
				Move();
			}
		}
		else if (m_TARGET)
		{
			if (AttackRangeCheck())
			{
				m_STATETYPE = ATTACK_;
			}
			else
			{
				m_STATETYPE = IDLE_;
				/*FloatPoint TPoint = m_TARGET->GetPosition();
				*m_TARGETPOSITION = TPoint;*/
			}
		}

		break;

	case ATTACK_:

		if (!AttackRangeCheck())
		{
			//m_TARGETPOSITION = nullptr;
			m_STATETYPE = IDLE_;

			break;
		}
		// Ÿ���� ���� ���
		//if (m_TARGET)
		//{
			//if (AttackRangeCheck())
			//{
				Attack();
			//}
			//else
			//{

				m_STATETYPE = IDLE_;
			//}
				break;

		//}
		//// Ÿ���� ����, Ÿ���������� �ִٸ�
		//if (nullptr != m_TARGET && m_TARGETPOSITION)
		//{
		//	m_STATETYPE = MOVE_;
		//}
		//break;

	case DIE_:
		m_Dead = true;
		break;
	case STATE_EOL:
	default:
		m_Dead = true;
		break;


		// ü�±�� ���º�ȭ
		m_wasHitPoint = m_IsHitPoint;

		// ü���� 0 �̸��̶��
		if (m_IsHitPoint <= 0)
		{
			m_Dead = true;
			m_STATETYPE = DIE_;
		}
	}
}

void Player2_Unit::MakeMovingMotionUnit()
{
	// ���ֺ� ���Ÿ�� ����
	for (int i = (int)MOVINGMOTION_TYPE::IDLE_DOWN; i != (int)MOVINGMOTION_TYPE::ATTACK_DOWNRIGHT; i++)
	{
		MovingMotion* tMovingMotion = new MovingMotion(GetName()
			, m_UNITTYPE
			, (MOVINGMOTION_TYPE)(i)
			, GetScale());
		tMovingMotion->SetOwner(this);

		m_VECTOR_MOVINGMOTION.push_back(tMovingMotion);
	}
}

