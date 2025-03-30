#include "PreCompile.h"

#include "R_UI.h"

R_UI::R_UI()
	: m_ParentUI(nullptr)
	, m_MouseHover(false)
	, m_LBtnDown(false)
{
}

R_UI::~R_UI()
{
	Delete_Vector(m_vecChildUI);
}

void R_UI::Tick()
{
	// 최종 좌표 계산하기
	m_FINALPOS = GetPosition();

	if (m_ParentUI)
	{
		m_FINALPOS += m_ParentUI->GetFinalPos();
	}

	// 마우스가 UI 위에 올라왔는지 체크하기
	MouseoverCheck();

	// 실제 UI 가 추가적으로 할일
	Tick_UI();

	// 자식 UI Tick 호출
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Tick();
	}
}

void R_UI::Render()
{
	// UI 본인 렌더링
	Render_UI();

	// 자식 UI Render 호출
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render();
	}
}

void R_UI::Render_UI()
{
	// GetPosition() : 부모 UI 로부터 상대 좌표, 부모가 없는 UI 경우 최종 좌표
	// GetFinalPos() : 최종 좌표, 부모의 위치가 누적되고 거기에 자신의 상대좌표를 더한 값
	FloatPoint vPos = GetFinalPos();
	FloatPoint vScale = GetScale();

	SELECT_PEN(PEN_COLOR::GREEN);
	SELECT_BRUSH(BRUSH_COLOR::HOLLOW);

	Rectangle(GameEngine::GetInstance()->GetMemoryDC()
		, (int)vPos.x, (int)vPos.y
		, (int)(vPos.x + vScale.x)
		, (int)(vPos.y + vScale.y));
}

void R_UI::MouseoverCheck()
{
	FloatPoint VMOUSEPOS = KeyMGR::GetInstance()->GetMousePos();

	FloatPoint vPos = GetFinalPos();
	FloatPoint vScale = GetScale();

	if (vPos.x <= VMOUSEPOS.x && VMOUSEPOS.x <= vPos.x + vScale.x
		&& vPos.y <= VMOUSEPOS.y && VMOUSEPOS.y <= vPos.y + vScale.y)
	{
		m_MouseHover = true;
	}
	else
	{
		m_MouseHover = false;
	}
}