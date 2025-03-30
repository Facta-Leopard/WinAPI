#include "PreCompile.h"
#include "MenuUI.h"

MenuUI::MenuUI(wstring _wString, float _duration)
	: StarUnit(_wString, _duration)

	, m_ClickSoundable(true)
	, m_MouseoverSoundable(true)

	, m_WasMouseover(false)
	, m_IsMouseover(false)
	, m_IsLeftButtonClick(false)
	, m_WasLeftButtonClick(false)

	, m_TEXTURE(nullptr)

	, m_Index(0)
	, m_MaxFrame(0)
{
	m_TEXTURE = AssetMGR::GetInstance()->LoadTexture(_wString
		, L"Texture\\Menu\\" + _wString + L"\\" + _wString + L".BMP");
	m_OnText = true;
}

MenuUI::~MenuUI()
{
}

void MenuUI::Init()
{
	// �ִ� ������ �ڵ� ���
	m_MaxFrame = (int)(m_TEXTURE->GetHeight() / GetScale().y);

	if (0.f == m_Duration)
	{
		m_MaxFrame = 1;
	}
	else
	{
		// ������ ����
		if (1 != m_MaxFrame)
		{
			m_MaxFrame -= 1;
		}

		// �����Ӵ� �ɸ��� �ð�
		m_FPS_Time = m_Duration / m_MaxFrame;
	}
}

void MenuUI::Tick()
{
	m_Time += DELTATIME;

	if (1 == m_MaxFrame)
	{
		m_Index = 0;
	}
	else
	{
		if (m_MaxFrame <= m_Index)
		{
			m_Index = 0;
		}

		if (m_FPS_Time < m_Time)
		{
			m_Time = 0;
			m_Index++;
		}
	}

	MouseoverCheck();
	MouseClickCheck();
	Render();

	// Ŭ���� �Ҹ���� �κ�
	PlaySound();
}

void MenuUI::Render()
{
	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();

	FloatPoint tPOS = GetPosition();

	TransparentBlt(tDC
		, tPOS.x - GetScale().x * 0.5
		, tPOS.y - GetScale().y * 0.5
		, GetScale().x
		, GetScale().y
		, m_TEXTURE->GetDC()
		, 0, (GetScale().y * m_Index)
		, m_TEXTURE->GetWidth()
		, GetScale().y
		, RGB(0, 0, 0));

	// �ؽ�Ʈ ���� �κ�
	if (!m_OnText)
	{
	}
	else
	{
		if (m_IsMouseover)
		{
			// �ؽ�Ʈ ����
			SetTextColor(tDC, RGB(150, 250, 150));
			SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
			TextOutW(tDC, ((tPOS.x - GetScale().x * 0.2f) + GetName().size())
				, (tPOS.y + GetScale().y * 0.5f)
				, GetName().c_str(), GetName().size()); // �޴� �ؽ�Ʈ
		}
		else
		{
			// �ؽ�Ʈ ����
			SetTextColor(tDC, RGB(0, 250, 0));
			SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
			TextOutW(tDC, ((tPOS.x - GetScale().x * 0.2f) + GetName().size())
				, (tPOS.y + GetScale().y * 0.5f)
				, GetName().c_str(), GetName().size()); // �޴� �ؽ�Ʈ
		}
	}
}

void MenuUI::PlaySound()
{
	if (m_IsLeftButtonClick && m_IsMouseover && m_ClickSoundable)
	{
		m_ClickSoundable = false;

		Sound* pSound = AssetMGR::GetInstance()->LoadSound(L"MouseTap", L"Sound\\MouseTap.wav");

		if (nullptr != pSound)
		{
			pSound->Play(false);
			pSound->SetVolume(80.f);
		}
	}

	// ���콺������ �Ҹ���� �κ�

	if (m_IsMouseover && m_MouseoverSoundable)
	{
		m_MouseoverSoundable = false;

		Sound* pSound = AssetMGR::GetInstance()->LoadSound(L"Mouseover", L"Sound\\Mouseover.wav");

		if (nullptr != pSound)
		{
			pSound->Play(false);
			pSound->SetVolume(80.f);
		}
	}

	// m_Trigger_PointerFunction�� nullptr�� �ƴ� ��쿡�� ȣ��
	// �� ����ڵ尡 ��� ��������.. ��
	if (m_IsMouseover && m_IsLeftButtonClick && m_Trigger_PointerFunction)
	{
		(this->m_Trigger_PointerFunction)(m_LAYERTYPE);
	}
}

void MenuUI::MouseoverCheck()
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

	if (!m_WasMouseover)
	{
		m_MouseoverSoundable = true;
	}
}

void MenuUI::SetOnText()
{
	m_OnText = true;
}

void MenuUI::SetOffText()
{
	m_OnText = false;
}

void MenuUI::MouseClickCheck()
{
	// ���콺 ���ʹ�ư�� TAP ������ ��
	if (KEY_TAP(LBTN))
	{
		m_IsLeftButtonClick = true;
	}
	if (KEY_PRESSED(LBTN))
	{
		// �� �� ����
		// ���� : Ű�� ���� ���� Ŭ������ �����ؾ� ���߿� �巡�� ����� �� ��
		// ����, �巡�׾ص�� ������ �ڵ带 ��������
		if (m_IsMouseover)
		{
			m_WasLeftButtonClick = true;
		}
	}
	else if (KEY_RELEASED(LBTN))
	{
		if (m_IsMouseover && m_WasLeftButtonClick)
		{
			KeyMGR::GetInstance()->SetCursorType(CURSOR_TYPE::STARCRAFT_CURSOR);
		}
		else if (!m_IsMouseover)
		{
			m_IsLeftButtonClick = false;
			m_WasLeftButtonClick = false;
		}
	}
}

// SetTriggerPointerFunction ����
void MenuUI::SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction)
{
	// �ܺ� �Լ� �����͸� m_TriggerFunction�� �Ҵ�
	m_Trigger_PointerFunction = PointFunction;
}
void MenuUI::SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction)
{
	m_Sound_PointerFunction = PointFunction;
}