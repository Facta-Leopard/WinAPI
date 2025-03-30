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

// 복사 대입을 위한 복사생성자
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
	// Texture 복사 (새로운 텍스처를 로드하여 독립적인 객체를 만들어야 함)
	// 방어코드(솔직히 없어도 될 것 같지만.. 혹시나..)
	if (_OTHER.m_TEXTURE != nullptr)
	{
		// 얉은 복사
		m_TEXTURE = _OTHER.m_TEXTURE;

		// 깊은 복사할 필요가 있을까? 싶지만 혹시 몰라서 테스트 중이므로 주석으로 만듦
		// 깊은 복사를 하기 위한 new 사용
		// m_TEXTURE = new Texture(*other.m_TEXTURE);
	}
	else
	{
		m_TEXTURE = nullptr;
	}
}

// 복사 대입을 위한 대입연산자 오버로딩 -0-
MovingMotion& MovingMotion::operator=(const MovingMotion& _OTHER)
{
	// 방어코드(자기대입 방지)
	assert(this != &_OTHER);
	
		// 기본 타입 멤버 복사
		m_Name = _OTHER.m_Name;
		m_Time = _OTHER.m_Time;
		m_Duration = _OTHER.m_Duration;
		m_FPS_Time = _OTHER.m_FPS_Time;
		m_Index = _OTHER.m_Index;
		m_MaxFrame = _OTHER.m_MaxFrame;
		m_MOVINGMOTIONTYPE = _OTHER.m_MOVINGMOTIONTYPE;
		m_UNITTYPE = _OTHER.m_UNITTYPE;
		m_SCALE = _OTHER.m_SCALE;

		// m_TEXTURE 복사 (포인터 복사 시, 깊은 복사가 필요할 경우 처리)
		if (_OTHER.m_TEXTURE != nullptr)
		{
			// 얕은 복사
			//m_TEXTURE = _OTHER.m_TEXTURE;
			// 또는 깊은 복사 필요 시:
			 m_TEXTURE = new Texture(*_OTHER.m_TEXTURE);
		}
		else {
			m_TEXTURE = nullptr;
		}
	
	// 자기 자신을 반환
	return *this;
}

MovingMotion::~MovingMotion()
{
}

void MovingMotion::Init()
{
	// 이상한 복사생성자 에러가 난다.. 해결이 일단 안되니까 다른 방법으로 구현하자..
	//FloatPoint tSCALE = GetOwner()->GetScale();
	// 임시코드
	FloatPoint tSCALE = { 64, 64 };

	// 최대 프레임 자동 계산
	m_MaxFrame = (int)(m_TEXTURE->GetHeight() / 64);

	// 프레임 보정
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

	// 프레임당 걸리는 시간
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
