#include "PreCompile.h"
#include "MovingMotion.h"

#include "PortraitMGR.h"

MovingMotion::MovingMotion()
	: Component(COMPONENT_TYPE::MOVINGMOTION)
	, m_Time(0.f)
	, m_Duration(2.f)
	, m_FPS_Time(0.f)
	, m_Index(0)
	, m_MaxFrame(0)
	, m_TEXTURE(nullptr)
	, m_MOVINGMOTIONTYPE()
	, m_UNITTYPE()
{
	if (m_TEXTURE)
	{
		Init();
	}
}

MovingMotion::MovingMotion(wstring _Name
	, UNIT_TYPE _UNIT
	, MOVINGMOTION_TYPE _MOVINGMOTION
	, FloatPoint _SIZE)
	: Component(COMPONENT_TYPE::MOVINGMOTION)
	, m_Time(0.f)
	, m_Duration(2.f)
	, m_FPS_Time(0.f)
	, m_Index(0)
	, m_MaxFrame(1)
	, m_TEXTURE(nullptr)
	, m_MOVINGMOTIONTYPE(_MOVINGMOTION)
	, m_UNITTYPE(_UNIT)
{
	SetName(_Name);
	SetScale(_SIZE);

	wstring tName = std::to_wstring(GetID());

	m_TEXTURE = AssetMGR::GetInstance()->LoadTexture(tName, L"Texture\\Unit\\" + (wstring)(UNIT_TYPE_TO_STRING(_UNIT)) + L"\\" + (wstring)MOVINGMOTION_TYPE_TO_STRING(_MOVINGMOTION) + L".bmp");
	Init();
}

// ���� ������ ���� ���������
MovingMotion::MovingMotion(const MovingMotion& _OTHER)
	: Component(_OTHER)
	, m_Name(_OTHER.m_Name)
	, m_Time(_OTHER.m_Time)
	, m_Duration(_OTHER.m_Duration)
	, m_FPS_Time(_OTHER.m_FPS_Time)
	, m_Index(_OTHER.m_Index)
	, m_MaxFrame(_OTHER.m_MaxFrame)
	, m_MOVINGMOTIONTYPE(_OTHER.m_MOVINGMOTIONTYPE)
	, m_UNITTYPE(_OTHER.m_UNITTYPE)
	, m_SCALE(_OTHER.m_SCALE)
{
	if ((MOVINGMOTION_TYPE)16 <= m_MOVINGMOTIONTYPE && m_MOVINGMOTIONTYPE <= (MOVINGMOTION_TYPE)23)
	{
		m_Duration = 1.f;
	}
	// Texture ���� (���ο� �ؽ�ó�� �ε��Ͽ� �������� ��ü�� ������ ��)
	// ����ڵ�(������ ��� �� �� ������.. Ȥ�ó�..)
	if (_OTHER.m_TEXTURE != nullptr)
	{
		// ���� ����
		m_TEXTURE = _OTHER.m_TEXTURE;

		// ���� ������ �ʿ䰡 ������? ������ Ȥ�� ���� �׽�Ʈ ���̹Ƿ� �ּ����� ����
		// ���� ���縦 �ϱ� ���� new ���
		// m_TEXTURE = new Texture(*other.m_TEXTURE);
	}
	else
	{
		m_TEXTURE = nullptr;
	}
}

// ���� ������ ���� ���Կ����� �����ε� -0-
MovingMotion& MovingMotion::operator=(const MovingMotion& _OTHER)
{
	// ����ڵ�(�ڱ���� ����)
	assert(this != &_OTHER);
	
		// �⺻ Ÿ�� ��� ����
		m_Name = _OTHER.m_Name;
		m_Time = _OTHER.m_Time;
		m_Duration = _OTHER.m_Duration;
		m_FPS_Time = _OTHER.m_FPS_Time;
		m_Index = _OTHER.m_Index;
		m_MaxFrame = _OTHER.m_MaxFrame;
		m_MOVINGMOTIONTYPE = _OTHER.m_MOVINGMOTIONTYPE;
		m_UNITTYPE = _OTHER.m_UNITTYPE;
		m_SCALE = _OTHER.m_SCALE;

		// m_TEXTURE ���� (������ ���� ��, ���� ���簡 �ʿ��� ��� ó��)
		if (_OTHER.m_TEXTURE != nullptr)
		{
			// ���� ����
			//m_TEXTURE = _OTHER.m_TEXTURE;
			// �Ǵ� ���� ���� �ʿ� ��:
			 m_TEXTURE = new Texture(*_OTHER.m_TEXTURE);
		}
		else {
			m_TEXTURE = nullptr;
		}
	
	// �ڱ� �ڽ��� ��ȯ
	return *this;
}

MovingMotion::~MovingMotion()
{
}

void MovingMotion::Init()
{
	// �̻��� ��������� ������ ����.. �ذ��� �ϴ� �ȵǴϱ� �ٸ� ������� ��������..
	//FloatPoint tSCALE = GetOwner()->GetScale();
	// �ӽ��ڵ�
	FloatPoint tSCALE = { 64, 64 };

	// �ִ� ������ �ڵ� ���
	m_MaxFrame = (int)(m_TEXTURE->GetHeight() / 64);

	// ������ ����
	if (12 < m_MaxFrame)
	{
		m_Duration *= 1.8;
	}
	else if (8 < m_MaxFrame)
	{
		m_Duration *= 1.2f;
	}
	else if (4 < m_MaxFrame)
	{
		m_Duration *= 0.4;
	}
	else if (3 < m_MaxFrame)
	{
		m_Duration * 0.2;
	}
	

	if (1 == m_MaxFrame)
	{
		m_MaxFrame = 1;
	}
	else
	{
		m_MaxFrame -= 1;
	}

	// �����Ӵ� �ɸ��� �ð�
	m_FPS_Time = m_Duration / m_MaxFrame;
}

void MovingMotion::FinalTick()
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

void MovingMotion::Render()
{
	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();

	FloatPoint tPOS = { 0, 0 };
	tPOS = GetOwner()->GetIngameViewPosition();

	FloatPoint tSCALE = {0, 0};
	tSCALE = GetOwner()->GetScale();

	TransparentBlt(tDC
		, tPOS.x - (int)(tSCALE.x * 0.5)
		, tPOS.y - (int)(tSCALE.y * 0.5)
		, (int)tSCALE.x
		, (int)tSCALE.y
		, m_TEXTURE->GetDC()
		, 0, ((int)tSCALE.y * m_Index)
		, (int)tSCALE.x
		, (int)tSCALE.y
		, RGB(255, 255, 255));
}
