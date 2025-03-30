#include "PreCompile.h"
#include "R_ButtonUI.h"

R_ButtonUI::R_ButtonUI()
	: m_Func(nullptr)
	, m_MemFunc(nullptr)
{
}

R_ButtonUI::~R_ButtonUI()
{
}

void R_ButtonUI::Tick_UI()
{

}

void R_ButtonUI::Render_UI()
{
	FloatPoint vPos = GetFinalPos();
	FloatPoint vScale = GetScale();

	SELECT_PEN(PEN_COLOR::GREEN);

	HBRUSH hBrush = CreateSolidBrush(RGB(143, 36, 32));
	HDC dc = GameEngine::GetInstance()->GetMemoryDC();

	HBRUSH hPrevBrush = (HBRUSH)SelectObject(dc, hBrush);

	Rectangle(dc
		, (int)vPos.x, (int)vPos.y
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));

	SelectObject(dc, hPrevBrush);
	DeleteObject(hBrush);
}

void R_ButtonUI::MouseLBtnClikced()
{
	if (nullptr != m_Func)
		m_Func();

	if (m_Inst && m_MemFunc)
	{
		(m_Inst->*m_MemFunc)();
	}
}