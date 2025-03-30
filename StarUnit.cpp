#include "PreCompile.h"
#include "StarUnit.h"

StarUnit::StarUnit(wstring _wString, float _duration)
	: m_Time(0.f)
	//, m_ClickSoundable(true)
	//, m_MouseoverSoundable(true)

	, m_Duration(_duration)
	, m_FPS_Time(0.f)

	, m_OnText(false)

	, m_Trigger_PointerFunction(nullptr)
{
}

StarUnit::~StarUnit()
{
}

void StarUnit::Init()
{
}

void StarUnit::Tick()
{
}

void StarUnit::Render()
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
}

void StarUnit::MouseoverCheck()
{
}

void StarUnit::MouseClickCheck()
{
}

void StarUnit::SetOnText()
{
	m_OnText = true;
}

void StarUnit::SetOffText()
{
	m_OnText = false;
}

	// SetTriggerPointerFunction 구현
void StarUnit::SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction)
{
	// 외부 함수 포인터를 m_TriggerFunction에 할당
	m_Trigger_PointerFunction = PointFunction;
}
void StarUnit::SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction)
{
	m_Sound_PointerFunction = PointFunction;
}