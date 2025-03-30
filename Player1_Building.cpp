#include "PreCompile.h"
#include "Player1_Building.h"

Player1_Building::Player1_Building(wstring _wString, UNIT_TYPE m_UNITTYPE, float _duration)
	: StarUnit(_wString, _duration)
	, m_ClickSoundable(true)

	, m_WasMouseover(false)
	, m_IsMouseover(false)
	, m_IsLeftButtonClick(false)
	, m_WasLeftButtonClick(false)
{
}

Player1_Building::~Player1_Building()
{
}

void Player1_Building::Init()
{
//	// 최대 프레임 자동 계산
//	m_MaxFrame = (int)(m_TEXTURE->GetHeight() / GetScale().y);
//
//	if (0.f == m_Duration)
//	{
//		m_MaxFrame = 1;
//	}
//	else
//	{
//		// 프레임 보정
//		if (1 != m_MaxFrame)
//		{
//			m_MaxFrame -= 1;
//		}
//
//		// 프레임당 걸리는 시간
//		m_FPS_Time = m_Duration / m_MaxFrame;
//	}
}

void Player1_Building::Tick()
{
	MouseoverCheck();
	MouseClickCheck();
	Render();

	// 클릭시 소리재생 부분
	// 이 것도 향후, 포인터함수로 구현해야할 듯
	// 인게임에서 유닛 클릭시 소리나면 안되니까..
	// 향후 PlayTapSound()함수로 포인터함수를 만들어서 가독성 좋게 정리하자..
	// 마우스 오버와 동일하게 구현시 재생이 쌓이는 문제가 있음..
	// timer로 해결이 가능하려나.. 일단 타이머는 구현했고,
	// 다시금 구현 재시도해봄

	// 대체 뭐가 문젠데!

	//if (m_IsLeftButtonClick && m_ClickSoundable)
	//{
	//	m_ClickSoundable = false;
	//	Sound* pTap = AssetMGR::GetInstance()->LoadSound(L"MouseTap", L"Sound\\MouseTap.wav");
	//	if (nullptr != pTap)
	//	{
	//		pTap->SetVolume(70.f);
	//		pTap->PlayToBGM(true);
	//	}
	//}

	// m_Trigger_PointerFunction이 nullptr이 아닌 경우에만 호출
	// 이 방어코드가 없어서 에러났음.. ㅠ
	if (m_IsMouseover && m_IsLeftButtonClick && m_Trigger_PointerFunction)
	{
		(this->m_Trigger_PointerFunction)(m_LAYERTYPE);
	}
}

void Player1_Building::Render()
{
	//HDC tDC = GameEngine::GetInstance()->GetMemoryDC();

	//FloatPoint vPos = GetCameraViewPosition();
	//FloatPoint vScale = GetScale();
	//m_Time += DELTATIME;

	//if (1 == m_MaxFrame)
	//{
	//	m_Index = 0;
	//}
	//else
	//{
	//	if (m_MaxFrame <= m_Index)
	//	{
	//		m_Index = 0;
	//	}

	//	if (m_FPS_Time < m_Time)
	//	{
	//		m_Time = 0;
	//		m_Index++;
	//	}
	//}

	//TransparentBlt(tDC
	//	, vPos.x - GetScale().x / 2
	//	, vPos.y - GetScale().y / 2
	//	, GetScale().x
	//	, GetScale().y
	//	, m_TEXTURE->GetDC()
	//	, 0, (GetScale().y * m_Index)
	//	, m_TEXTURE->GetWidth()
	//	, GetScale().y
	//	, RGB(0, 0, 0));

	// 텍스트 구현 부분
	if (!m_OnText)
	{
	}
	//else
	//{
	//	if (m_IsMouseover)
	//	{
	//		// 텍스트 구현
	//		SetTextColor(tDC, RGB(150, 250, 150));
	//		SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
	//		TextOutW(tDC, ((GetPosition().x - GetScale().x * 0.2f) + GetName().size())
	//			, (GetPosition().y + GetScale().y * 0.5f)
	//			, GetName().c_str(), GetName().size()); // 메뉴 텍스트
	//	}
	//	else
	//	{
	//		// 텍스트 구현
	//		SetTextColor(tDC, RGB(0, 250, 0));
	//		SetBkMode(tDC, TRANSPARENT); // 배경 모드를 투명으로 설정
	//		TextOutW(tDC, ((GetPosition().x - GetScale().x * 0.2f) + GetName().size())
	//			, (GetPosition().y + GetScale().y * 0.5f)
	//			, GetName().c_str(), GetName().size()); // 메뉴 텍스트
	//	}
	//}
}

void Player1_Building::MouseoverCheck()
{
	FloatPoint MOUSEPOS = KeyMGR::GetInstance()->GetMousePos();
	POINT tPOS = { GetPosition().x, GetPosition().y };
	FloatPoint tSCALE = { GetScale().x, GetScale().y };

	m_WasMouseover = m_IsMouseover;
	if (tPOS.x - tSCALE.x / 2 <= (int)MOUSEPOS.x && (int)MOUSEPOS.x <= tPOS.x + tSCALE.x / 2
		&& tPOS.y - tSCALE.y / 2 <= (int)MOUSEPOS.y && (int)MOUSEPOS.y <= tPOS.y + tSCALE.y / 2)
	{
		m_IsMouseover = true;
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
}

void Player1_Building::MouseClickCheck()
{
	// 마우스 왼쪽버튼이 TAP 상태일 때
	if (KEY_PRESSED(LBTN))
	{
		// 좀 더 보강
		// 사유 : 키를 놨을 때를 클릭으로 정의해야 나중에 드래그 드랍이 될 듯
		// 향후, 드래그앤드랍 구현시 코드를 조정하자
		if (m_IsMouseover)
		{
			m_WasLeftButtonClick = true;
		}
	}
	else if (KEY_RELEASED(LBTN))
	{
		if (m_IsMouseover && m_WasLeftButtonClick)
		{
			m_IsLeftButtonClick = true;
			KeyMGR::GetInstance()->SetCursorType(CURSOR_TYPE::STARCRAFT_CURSOR);
		}
		else if (!m_IsMouseover)
		{
			m_IsLeftButtonClick = false;
			m_WasLeftButtonClick = false;
		}
	}
}

// SetTriggerPointerFunction 구현
void Player1_Building::SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction)
{
	// 외부 함수 포인터를 m_TriggerFunction에 할당
	m_Trigger_PointerFunction = PointFunction;
}
void Player1_Building::SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction)
{
	m_Sound_PointerFunction = PointFunction;
}