#include "PreCompile.h"
#include "Portrait.h"

Portrait::Portrait()
	: Component(COMPONENT_TYPE::PORTRAIT)
	, m_Time(0.f)
	, m_Duration(3.f)
	, m_FPS_Time(0.f)
	, m_Index(0)
	, m_MaxFrame(1)
	, m_TEXTURE(nullptr)
	, m_PORTRAITTYPE(PORTRAIT_TYPE::PORTRAITE_IDLE)
	, m_UNITTYPE(UNIT_TYPE::ADVISOR)
	, m_SCALE{0, 0 }
{
}

Portrait::Portrait(wstring _Name
				 , UNIT_TYPE _UNIT
				 , PORTRAIT_TYPE _PORTRAIT
				 , FloatPoint _SIZE)
	: Component(COMPONENT_TYPE::PORTRAIT)
	, m_Time(0.f)
	, m_Duration(3.f)
	, m_FPS_Time(0.f)
	, m_Index(0)
	, m_MaxFrame(1)
	, m_TEXTURE(nullptr)
	, m_PORTRAITTYPE(_PORTRAIT)
	, m_UNITTYPE(_UNIT)
	, m_SCALE{ _SIZE.x, _SIZE.y}
{
	SetName(_Name);

	m_TEXTURE = AssetMGR::GetInstance()->LoadTexture(m_Name
		, L"Texture\\Portrait\\" + (wstring)UNIT_TYPE_TO_STRING(m_UNITTYPE) + L"\\" + (wstring)PORTRAIT_TYPE_TO_STRING(m_PORTRAITTYPE) + L".bmp");

	/*m_TEXTURE = AssetMGR::GetInstance()->LoadTexture(m_Name
		, L"Texture\\Portrait\\" + (wstring)(UNIT_TYPE_TO_STRING(_UNIT)) + L"\\" + (wstring)PORTRAIT_TYPE_TO_STRING(m_PORTRAITTYPE) + L".bmp");*/

	Init();
}

// ���� ������ ���� ���������
Portrait::Portrait(const Portrait& _OTHER)
	: Component(_OTHER)
	, m_Name(_OTHER.m_Name)
	, m_Time(_OTHER.m_Time)
	, m_Duration(_OTHER.m_Duration)
	, m_FPS_Time(_OTHER.m_FPS_Time)
	, m_Index(_OTHER.m_Index)
	, m_MaxFrame(_OTHER.m_MaxFrame)
	, m_PORTRAITTYPE(_OTHER.m_PORTRAITTYPE)
	, m_UNITTYPE(_OTHER.m_UNITTYPE)
	, m_SCALE(_OTHER.m_SCALE)
{
	// Texture ���� (���ο� �ؽ�ó�� �ε��Ͽ� �������� ��ü�� ������ ��)
	if (_OTHER.m_TEXTURE != nullptr)
	{
		// ���� ����
		m_TEXTURE = _OTHER.m_TEXTURE;
	}
	else
	{
		m_TEXTURE = nullptr;
	}
}

// ���� ������ ���� ���Կ����� �����ε� -0-
Portrait& Portrait::operator=(const Portrait& _OTHER)
{
	// ����ڵ� (�ڱ���� ����)
	assert(this != &_OTHER);

	// �⺻ Ÿ�� ��� ����
	m_Name = _OTHER.m_Name;
	m_Time = _OTHER.m_Time;
	m_Duration = _OTHER.m_Duration;
	m_FPS_Time = _OTHER.m_FPS_Time;
	m_Index = _OTHER.m_Index;
	m_MaxFrame = _OTHER.m_MaxFrame;
	m_PORTRAITTYPE = _OTHER.m_PORTRAITTYPE;
	m_UNITTYPE = _OTHER.m_UNITTYPE;
	m_SCALE = _OTHER.m_SCALE;

	// ���� �ؽ�ó �޸� ���� (�ʿ��� ���)
	if (m_TEXTURE != nullptr)
	{
		delete m_TEXTURE;
		m_TEXTURE = nullptr;
	}

	// Texture ���� (���ο� �ؽ�ó�� �ε��Ͽ� �������� ��ü�� ������ ��)
	if (_OTHER.m_TEXTURE != nullptr)
	{
		m_TEXTURE = new Texture(*_OTHER.m_TEXTURE);  // ���� ����
	}
	else {
		m_TEXTURE = nullptr;
	}

	return *this;
}

Portrait::~Portrait()
{
	m_TEXTURE = nullptr;
}

void Portrait::Init()
{
	// �ִ� ������ �ڵ� ���
	m_MaxFrame = (int)(m_TEXTURE->GetHeight() / (int)m_SCALE.y);

	// ������ ����
	if (1 != m_MaxFrame)
	{
		m_MaxFrame -= 1;
	}

	// �����Ӵ� �ɸ��� �ð�
	m_FPS_Time = m_Duration / m_MaxFrame;
}

void Portrait::FinalTick()
{
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
	Render();
}

void Portrait::Render()
{
	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
	FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();

	// �г� �� ��ġ�� ��ƾߵ�..
	FloatPoint tPOS = { vResolution.x * 0.70 - 5, vResolution.y * 0.9 + 5 };

		// �̻��� ��������� ������ ����.. �ذ��� �ϴ� �ȵǴϱ� �ٸ� ������� ��������..
		//FloatPoint tSCALE = GetOwner()->GetScale();
		// �ӽ��ڵ�

		BitBlt(tDC
		, (int)tPOS.x - (int)(m_SCALE.x * 0.5)
		, (int)tPOS.y - (int)(m_SCALE.y * 0.5)
		, (int)m_TEXTURE->GetWidth()
		, (int)m_SCALE.y
		, m_TEXTURE->GetDC()
		, 0, (m_SCALE.y * m_Index)
		, SRCCOPY);
}
