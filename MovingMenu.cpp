#include "PreCompile.h"
#include "MovingMenu.h"

MovingMenuUI::MovingMenuUI(wstring _wString, FloatPoint _TARGETPOINT, float _duration, float _velocity)
    : MenuUI(_wString, _duration)
	, m_TARGETPOINT({})
	, m_Velocity(_velocity)
{
	m_TARGETPOINT = _TARGETPOINT;
	m_TEXTURE = AssetMGR::GetInstance()->LoadTexture(_wString
		, L"Texture\\Menu\\" + _wString + L"\\" + _wString + L".BMP");

}

MovingMenuUI::~MovingMenuUI()
{
}

void MovingMenuUI::Init()
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

void MovingMenuUI::Tick()
{
	float tOFFSET = abs(m_TARGETPOINT.x - GetPosition().x);
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

	if (5.f < tOFFSET)
	{
		if (m_TARGETPOINT.x > GetPosition().x)
		{
			SetPosition(GetPosition().x + DELTATIME * m_Velocity * (1.5f), GetPosition().y);
			m_Velocity -= DELTATIME * 220.f;
		}
		else
		{
			SetPosition(GetPosition().x + DELTATIME * m_Velocity * (-1.5f), GetPosition().y);
			m_Velocity += DELTATIME * 220.f;
		}	

	}
	Render();
}

void MovingMenuUI::Render()
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

void MovingMenuUI::PlaySound()
{
}

