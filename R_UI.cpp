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
	// ���� ��ǥ ����ϱ�
	m_FINALPOS = GetPosition();

	if (m_ParentUI)
	{
		m_FINALPOS += m_ParentUI->GetFinalPos();
	}

	// ���콺�� UI ���� �ö�Դ��� üũ�ϱ�
	MouseoverCheck();

	// ���� UI �� �߰������� ����
	Tick_UI();

	// �ڽ� UI Tick ȣ��
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Tick();
	}
}

void R_UI::Render()
{
	// UI ���� ������
	Render_UI();

	// �ڽ� UI Render ȣ��
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->Render();
	}
}

void R_UI::Render_UI()
{
	// GetPosition() : �θ� UI �κ��� ��� ��ǥ, �θ� ���� UI ��� ���� ��ǥ
	// GetFinalPos() : ���� ��ǥ, �θ��� ��ġ�� �����ǰ� �ű⿡ �ڽ��� �����ǥ�� ���� ��
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