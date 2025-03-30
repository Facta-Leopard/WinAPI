#include "PreCompile.h"
#include "R_PanelUI.h"

#include "KeyMGR.h"
#include "GameEngine.h"

R_PanelUI::R_PanelUI()
{
}

R_PanelUI::~R_PanelUI()
{
}


void R_PanelUI::Tick_UI()
{
	if (IsLBtnDown())
	{
		FloatPoint VMOUSEPOS = KeyMGR::GetInstance()->GetMousePos();
		FloatPoint vDIFFERENCE = VMOUSEPOS - m_DownPos;

		FloatPoint vPos = GetPosition();
		vPos += vDIFFERENCE;
		SetPosition(vPos);

		m_DownPos = VMOUSEPOS;
	}
}

void R_PanelUI::Render_UI()
{
	FloatPoint vPos = GetFinalPos();
	FloatPoint vScale = GetScale();

	SELECT_PEN(PEN_COLOR::GREEN);

	HBRUSH hBrush = CreateSolidBrush(RGB(143, 90, 145));
	HDC dc = GameEngine::GetInstance()->GetMemoryDC();

	HBRUSH hPrevBrush = (HBRUSH)SelectObject(dc, hBrush);

	Rectangle(dc
		, (int)vPos.x, (int)vPos.y
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));

	SelectObject(dc, hPrevBrush);
	DeleteObject(hBrush);
}

void R_PanelUI::MouseLBtnDown()
{
	m_DownPos = KeyMGR::GetInstance()->GetMousePos();
}

void R_PanelUI::MouseLBtnClikced()
{
}
