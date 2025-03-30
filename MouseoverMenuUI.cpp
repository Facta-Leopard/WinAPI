#include "PreCompile.h"
#include "MouseoverMenuUI.h"

MouseoverMenuUI::MouseoverMenuUI(wstring _wString, float _duration)
	: MenuUI(_wString, _duration)
{

	// 아래 내용은 Menu 생성자에서 구현해서 제외
	
	//// 최대 프레임 자동 계산
	//m_MaxFrame = (int)(m_TEXTURE->GetHeight() / GetScale().y);

	//// 프레임 보정
	//m_MaxFrame -= 1;

	//// 프레임당 걸리는 시간
	//m_FPS_Time = m_Duration / m_MaxFrame;

	m_OnText = false;
}

MouseoverMenuUI::~MouseoverMenuUI()
{
}

void MouseoverMenuUI::Init()
{
	// 최대 프레임 자동 계산
	m_MaxFrame = (int)(m_TEXTURE->GetHeight() / GetScale().y);

	if (0.f == m_Duration)
	{
		m_MaxFrame = 1;
	}
	else
	{
		// 프레임 보정
		if (1 != m_MaxFrame)
		{
			m_MaxFrame -= 1;
		}

		// 프레임당 걸리는 시간
		m_FPS_Time = m_Duration / m_MaxFrame;
	}
}

void MouseoverMenuUI::Tick()
{
	MouseoverCheck();
	MouseClickCheck();
	if (m_IsMouseover && m_IsLeftButtonClick)
	{
		StageMGR::GetInstance()->MoveStage();  // 스테이지 전환 함수 호출
	}
}

void MouseoverMenuUI::Render()
{
	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();

	FloatPoint vPos = GetPosition();
	FloatPoint vScale = GetScale();
	m_Time += DELTATIME;
	if (m_MaxFrame < m_Index)
	{
		m_Index = 0;
	}

	if (m_FPS_Time < m_Time)
	{
		m_Time -= m_FPS_Time;
		m_Index++;
	}
	if (m_IsMouseover)
	{
		TransparentBlt(tDC
		, vPos.x - GetScale().x / 2
		, vPos.y - GetScale().y / 2
		, GetScale().x
		, GetScale().y
		, m_TEXTURE->GetDC()
		, 0, (GetScale().y * m_Index)
		, m_TEXTURE->GetWidth()
		, GetScale().y
		, RGB(0, 0, 0));
	}
}

void MouseoverMenuUI::MouseoverCheck()
{
	FloatPoint MOUSEPOS = KeyMGR::GetInstance()->GetMousePos();
	POINT tPOS = { GetPosition().x, GetPosition().y };
	FloatPoint tSCALE = { GetScale().x, GetScale().y };

	m_WasMouseover = m_IsMouseover;
	if (tPOS.x - tSCALE.x * 0.20 <= (int)MOUSEPOS.x && (int)MOUSEPOS.x <= tPOS.x + tSCALE.x * 0.20
		&& tPOS.y - tSCALE.y * 0.6 <= (int)MOUSEPOS.y && (int)MOUSEPOS.y <= tPOS.y + tSCALE.y * 0.5)
	{
		m_IsMouseover = true;
	}
	else
	{
		m_IsMouseover = false;
	}
}

void MouseoverMenuUI::MouseClickCheck()
{
	// 부모클래스에서만 작동해야하므로 오버라이드로 지워버림
}