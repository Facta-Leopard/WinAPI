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
//	// �ִ� ������ �ڵ� ���
//	m_MaxFrame = (int)(m_TEXTURE->GetHeight() / GetScale().y);
//
//	if (0.f == m_Duration)
//	{
//		m_MaxFrame = 1;
//	}
//	else
//	{
//		// ������ ����
//		if (1 != m_MaxFrame)
//		{
//			m_MaxFrame -= 1;
//		}
//
//		// �����Ӵ� �ɸ��� �ð�
//		m_FPS_Time = m_Duration / m_MaxFrame;
//	}
}

void Player1_Building::Tick()
{
	MouseoverCheck();
	MouseClickCheck();
	Render();

	// Ŭ���� �Ҹ���� �κ�
	// �� �͵� ����, �������Լ��� �����ؾ��� ��
	// �ΰ��ӿ��� ���� Ŭ���� �Ҹ����� �ȵǴϱ�..
	// ���� PlayTapSound()�Լ��� �������Լ��� ���� ������ ���� ��������..
	// ���콺 ������ �����ϰ� ������ ����� ���̴� ������ ����..
	// timer�� �ذ��� �����Ϸ���.. �ϴ� Ÿ�̸Ӵ� �����߰�,
	// �ٽñ� ���� ��õ��غ�

	// ��ü ���� ������!

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

	// m_Trigger_PointerFunction�� nullptr�� �ƴ� ��쿡�� ȣ��
	// �� ����ڵ尡 ��� ��������.. ��
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

	// �ؽ�Ʈ ���� �κ�
	if (!m_OnText)
	{
	}
	//else
	//{
	//	if (m_IsMouseover)
	//	{
	//		// �ؽ�Ʈ ����
	//		SetTextColor(tDC, RGB(150, 250, 150));
	//		SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
	//		TextOutW(tDC, ((GetPosition().x - GetScale().x * 0.2f) + GetName().size())
	//			, (GetPosition().y + GetScale().y * 0.5f)
	//			, GetName().c_str(), GetName().size()); // �޴� �ؽ�Ʈ
	//	}
	//	else
	//	{
	//		// �ؽ�Ʈ ����
	//		SetTextColor(tDC, RGB(0, 250, 0));
	//		SetBkMode(tDC, TRANSPARENT); // ��� ��带 �������� ����
	//		TextOutW(tDC, ((GetPosition().x - GetScale().x * 0.2f) + GetName().size())
	//			, (GetPosition().y + GetScale().y * 0.5f)
	//			, GetName().c_str(), GetName().size()); // �޴� �ؽ�Ʈ
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
	// ���콺 ���ʹ�ư�� TAP ������ ��
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

// SetTriggerPointerFunction ����
void Player1_Building::SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction)
{
	// �ܺ� �Լ� �����͸� m_TriggerFunction�� �Ҵ�
	m_Trigger_PointerFunction = PointFunction;
}
void Player1_Building::SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction)
{
	m_Sound_PointerFunction = PointFunction;
}