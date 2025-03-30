#include "PreCompile.h"
#include "Player_Unit.h"

#include "InGameStage.h"

#include "CameraMGR.h"

Player_Unit::Player_Unit(wstring _wString, UNIT_TYPE m_UNITTYPE, float _duration)
	: StarUnit(_wString, _duration)
	, m_VECTOR_MOVINGMOTION({})

	// 테스트 후 인공지능 구현할 컴포넌트
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

	// 시작시 임의 방향 설정
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
	// 유닛 선택 밑 유닛텍스트와 디버깅 표시구현 
	SelectRender();

	// 유닛재생
	// 컴포넌트 이용
	FinalTick();

	// 포인터 함수 적용 테스트 코드
	// 왜 안되지?
	// 포인터 함수로 테스트..
	// 안됨.. OTL.. 함수형 프로그래밍 구현 실패..
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
	// 글자 표시
	if (m_OnText)
	{
		if (m_IsSelected)
		{
			// 이름 구현
			SetTextColor(tDC, RGB(200, 250, 200));
			SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
			TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.4))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.35)
				, GetName().c_str(), (int)GetName().size()); // 메뉴 텍스트
		}
		else if (!m_IsSelected)
		{
			// 이름 구현
			SetTextColor(tDC, RGB(50, 250, 50));
			SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
			TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.4))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.35)
				, GetName().c_str(), (int)GetName().size()); // 메뉴 텍스트
		}

		// HP글자 구현
		wstring HPwstring = L"HP";

		SetTextColor(tDC, RGB(50, 250, 50));
		SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
		TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.15))
			, ((int)tPOS.y) + (int)(GetScale().y * 0.55)
			, HPwstring.c_str(), 2); // 메뉴 텍스트

		// 체력표시 구현

		float tHPRatio = m_IsHitPoint / m_MaxHitPoint;
		int tHP = m_IsHitPoint;

		wstring HitPointwstring = std::to_wstring(tHP);
		HitPointwstring += L" / " + std::to_wstring(m_MaxHitPoint);

		SetTextColor(tDC, RGB((int)(250 * (1 - tHPRatio)), int(250 * tHPRatio), (int)(250 * (1 - tHPRatio))));
		SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
		TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.5))
			, ((int)tPOS.y) + (int)(GetScale().y * 0.75)
			, HitPointwstring.c_str(), HitPointwstring.size()); // 메뉴 텍스트


		// 좌표 테스트용 코드
		if (m_Debugging)
		{
			{
				// 시야표시
				SELECT_PEN(PEN_COLOR::YELLOW)
					SELECT_BRUSH(BRUSH_COLOR::HOLLOW)
					Ellipse(GameEngine::GetInstance()->GetMemoryDC()
						, (int)tPOS.x - m_ViewRange, (int)tPOS.y - (int)m_ViewRange
						, (int)tPOS.x + m_ViewRange, (int)tPOS.y + (int)m_ViewRange);
			}

			// 사정거리 표시
			SELECT_PEN(PEN_COLOR::BLUE)
				SELECT_BRUSH(BRUSH_COLOR::HOLLOW)
				Ellipse(GameEngine::GetInstance()->GetMemoryDC()
					, (int)tPOS.x - m_AttackRange, (int)tPOS.y - (int)m_AttackRange
					, (int)tPOS.x + m_AttackRange, (int)tPOS.y + (int)m_AttackRange);

			// 케릭터의 x좌표 표시
			SetTextColor(tDC, RGB(100, 250, 100));
			SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
			TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.9))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.6)
				, std::to_wstring((int)(GetPosition().x)).c_str(), 3);
			// 케릭터의 y좌표 표시
			SetTextColor(tDC, RGB(100, 250, 100));
			SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
			TextOutW(tDC, ((int)(tPOS.x) + (int)(GetScale().x * 0.5))
				, ((int)tPOS.y) + (int)(GetScale().y * 0.6)
				, std::to_wstring((int)(GetPosition().y)).c_str(), 3);

			if (m_TARGETPOSITION)
			{
				FloatPoint tP = *m_TARGETPOSITION;
				// 타겟의 x좌표 표시
				SetTextColor(tDC, RGB(250, 100, 100));
				SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
				TextOutW(tDC, ((int)(tPOS.x) - (int)(GetScale().x * 0.9))
					, ((int)tPOS.y) + (int)(GetScale().y * 0.9)
					, std::to_wstring((int)tP.x).c_str(), 3);
				// 케릭터의 y좌표 표시
				SetTextColor(tDC, RGB(250, 100, 100));
				SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
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
	// 케릭터 아래 원 모양 그리기
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

	// 그림자 그리기
	// 필요시 모듈화
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
		// 혹시 모르니 방어코드
		if (200 < tCount)
		{
			tCount = 200;
		}

		wstring wString = L"!HIGH!";

		SetTextColor(tDC, RGB(255- tCount, 50, 50));
		SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
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


	// 이전 위치 갱신
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

	// 타이머
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

	// 내가 마우스오버 되었는지 확인
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

	// 적 마우스오버 여부 확인
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
	// 괜히 모듈화하다가 머릿속이 꼬이네;
	// 그냥 하드코딩으로 냅둘 걸 그랬나..
	FloatPoint tPOS = GetIngameViewPosition();

	// 마우스 왼쪽 키를 풀었을 때
	// 마우스가 내 유닛 위에 없고
	// 적 위에 마우스가 없을 때
	if (KEY_RELEASED(LBTN) && !m_WasMouseover && !m_TargetMouseover)
	{
		// 유닛이 범위안에 있는지 확인
		m_IsSelected = CheckInsideGetDragAndDropBox(tPOS);
		if (m_IsSelected)
		{
			m_IsOrder = true;
		}
	}
	// 마우스 왼쪽 키를 풀었을 때
	else if (KEY_RELEASED(LBTN) && m_WasMouseover)
	{
		// 마우스 오버되어 있고, 왼쪽키를 푼 순간
		m_IsSelected = true;
		m_IsOrder = true;
	}
	// 마우스 오른쪽 키를 풀었을 때
	// 적 위에 마우스가 있다면
	else if (KEY_RELEASED(RBTN) && m_IsSelected && m_TargetMouseover && !m_WasMouseover)
	{
		m_IsOrder = true;

		// 적군이라면 타겟으로 바꿈
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

		// 아군이라면 타겟포인트 위치로 가져옴
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
	// 마우스 오른쪽 키를 풀었을 때
	// 선택된 상태에서, 적 위에 마우스가 없고, 내 유닛 위에 마우스가 없다면
	else if (KEY_RELEASED(RBTN) && m_IsSelected && !m_TargetMouseover && !m_WasMouseover)
	{
		m_IsOrder = true;
		m_OrderMove = true;

		// 해당위치 적용
		FloatPoint tFLOATPOINT = KeyMGR::GetInstance()->GetMousePos();

		// 지금 가져온 것은 창 위치를 기반으로 한 실제좌표
		// 이 방법은 깊은 복사임
		m_TARGETPOSITION = new FloatPoint(tFLOATPOINT);
		INGAME_POS(*m_TARGETPOSITION);

		// 인게임용 좌표로 좌표 변환
		//INGAME_POS(*m_TARGETPOSITION);
	}
}



void Player_Unit::MakeMovingMotionUnit()
{
	// 유닛별 모션타입 생성
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

// 리빌딩
// 시연이 급하다!(사람이름 아님 ㅋ 농담..)
bool Player_Unit::ViewRangeCheck(Player_Unit* _TARGET)
{
	// 사정거리안에 적이 있다면
	if (AttackRangeCheck())
	{
		m_STATETYPE = ATTACK_;
	}
	// 사정거리 안에 적이 없고, 타겟이 있다면
	else if (_TARGET)
	{
		if (!m_TARGETPOSITION)
		{
			m_TARGETPOSITION = new FloatPoint;
		}
		int tX = m_TARGETPOSITION->x - m_TARGET->GetPosition().x;
		int tY = m_TARGETPOSITION->y - m_TARGET->GetPosition().y;

		// 타겟과의 거리를 구함
		int tDistance = (int)sqrt((tX * tX) + (tY * tY));

		// 타겟이 시야거리를 벗어나면
		if (m_ViewRange < tDistance)
		{
			_TARGET = nullptr;
			return false;
		}
		// 그렇지 않다면
		else
		{
			m_STATETYPE = MOVE_;
			return true;
		}
	}
	return false;
}

// 리빌딩

// 설마.. 이게 엑세스 문제발생시켰나?
//Player_Unit* Player_Unit::AttackRangeCheck()
bool Player_Unit::AttackRangeCheck()
{
	// 타겟이 있고
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

		// 타겟과의 거리를 구함
		int tDistance = (int)sqrt((tPloatPoint.x * tPloatPoint.x) + (tPloatPoint.y * tPloatPoint.y));
		if (m_AttackRange < tDistance)
		{
			return false;
		}
		return true;
	}
	// 타겟이 없을 때 
	// 타겟이 있는지 찾음(단, 적군레이어만)
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

				// 타겟과의 거리를 구함
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

// 리빌딩
void Player_Unit::Attack()
{
	if(AttackRangeCheck())
	{
			m_AttackDuration += DELTATIME;
			if (m_AttackSpeed <= m_AttackDuration)
			{
				m_AttackDuration = 0;
				m_TARGET->SetHitPoint(m_AttackPoint);
				// 타겟이 공격받고 있다는 bool값을 킴
				m_TARGET->SetIsUnderAttack(true);



			}
	}
	
	}



// 이건 리빌딩이 필요없을 듯
void Player_Unit::Move()
{
	// 타겟지점이 있고
	if (m_TARGETPOSITION)
	{
		FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();
		// 그럴린 없지만, 혹시나 싶어 체크 
		assert(m_TARGETPOSITION);

		FloatPoint* tTARGETPOINT = new FloatPoint(*m_TARGETPOSITION);
		FloatPoint tPOINT = INGAME_POS(*tTARGETPOINT);
		FloatPoint IPOSTION = GetIngameViewPosition();
		// 드디어 문제를 찾았다.. 포인터..

	//FloatPoint tPOINT = CAMERAVIEW_POS(*m_TARGETPOSITION);

	// 하도 짜증나서 방식 변경
	// Private에서 Protect로 멤버 방식 변경
		FloatPoint GAP = {};
		GAP.x = IPOSTION.x - tPOINT.x;
		GAP.y = IPOSTION.y - tPOINT.y;

		// 이동관련 제어
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


// 방향부분 MovingMotion 잘못 넣은 것을 확인했으나,
// 고치기엔 시간이 없어 그냥 방향 자체를 바꿈
// 일부 버그 발견으로 인한
// 재테스트 중임
void Player_Unit::DirectionCheck()
{
	// 다른 방식으로 시도
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

	//// 가급적 인라인으로 쓰는 버릇을 들이자.
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

	////// 디버깅용
	//////DrawDebugLine(PEN_COLOR::GREEN, tWASPOSITION, m_POSITION, 1);


	//// 라디안 각도 변환
	//tWasTheta *= 180.f;
	//tWasTheta /= PI;

	//m_DirectionAngle = tWasTheta;

	//m_DirectionAngle = fmod(m_DirectionAngle, 360.f);

	//// 360도 넘지 않게 처리
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

// FSM 테스트용 코드
// 향후 FSM 별도 컴포넌트 구현예정
// 향후 플레이어2 유닛 만들면 개선해야될 듯
void Player_Unit::TemporaryFSMCheck()
{
	// 체력기반 상태변화
	m_wasHitPoint = m_IsHitPoint;

	// 체력이 0 미만이라면
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

					// 타겟과의 거리를 구함
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
			// 타겟지점이 있다는 가정에서 시작함
			if (m_TARGETPOSITION)
			{
				//// 타겟이 있고, 공격받는 중이라면
				//if (m_TARGET && m_IsUnderAttack)
				//{
				//	 // 이 코드가 문제가 있는것 같은데..
				//	m_STATETYPE = ATTACK_;
				//	m_IsUnderAttack = false;
				//}
			 //타겟이 있지만, 공격받는 중이 아니라면
				/*if (m_TARGET && !m_IsUnderAttack)
				{
					Move();
				}*/
				// 타겟이 없고, 타겟포지션이 있다면
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
			// 타겟이 있을 경우
			if (m_TARGET)
			{
				Attack();
			}
			// 타겟이 없고, 타겟포지션이 있다면
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





// 포인터 함수 목록

// 트리거용 포인터 함수(오버로드 : 초상화재생용 포인터 함수)
void Player_Unit::SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction)
{
	// 외부 함수 포인터를 m_TriggerFunction에 할당
	m_Trigger_PointerFunction = PointFunction;
}

// 트리거용 포인터 함수(모션재생용 포인터 함수)
void Player_Unit::SetTriggerPointerFunction2(std::function<void(UNIT_TYPE, MOVINGMOTION_TYPE, POINT)> PointFunction)
{
	m_Trigger_PointerFunction2 = PointFunction;
}

// 사운드 재생용 포인터 함수
void Player_Unit::SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction)
{
	m_Sound_PointerFunction = PointFunction;
}

// 사운드 재생용 포인터 함수(유닛이 말하는 포인터 함수)
void Player_Unit::SetSoundPointerFunction2(std::function<void(UNIT_TYPE, MOVINGMOTION_TYPE)> PointFunction)
{
	m_Sound_PointerFunction2 = PointFunction;
}