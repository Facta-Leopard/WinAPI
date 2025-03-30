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

// 복사 대입을 위한 복사생성자
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
	// Texture 복사 (새로운 텍스처를 로드하여 독립적인 객체를 만들어야 함)
	if (_OTHER.m_TEXTURE != nullptr)
	{
		// 얉은 복사
		m_TEXTURE = _OTHER.m_TEXTURE;
	}
	else
	{
		m_TEXTURE = nullptr;
	}
}

// 복사 대입을 위한 대입연산자 오버로딩 -0-
Portrait& Portrait::operator=(const Portrait& _OTHER)
{
	// 방어코드 (자기대입 방지)
	assert(this != &_OTHER);

	// 기본 타입 멤버 복사
	m_Name = _OTHER.m_Name;
	m_Time = _OTHER.m_Time;
	m_Duration = _OTHER.m_Duration;
	m_FPS_Time = _OTHER.m_FPS_Time;
	m_Index = _OTHER.m_Index;
	m_MaxFrame = _OTHER.m_MaxFrame;
	m_PORTRAITTYPE = _OTHER.m_PORTRAITTYPE;
	m_UNITTYPE = _OTHER.m_UNITTYPE;
	m_SCALE = _OTHER.m_SCALE;

	// 기존 텍스처 메모리 해제 (필요한 경우)
	if (m_TEXTURE != nullptr)
	{
		delete m_TEXTURE;
		m_TEXTURE = nullptr;
	}

	// Texture 복사 (새로운 텍스처를 로드하여 독립적인 객체를 만들어야 함)
	if (_OTHER.m_TEXTURE != nullptr)
	{
		m_TEXTURE = new Texture(*_OTHER.m_TEXTURE);  // 깊은 복사
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
	// 최대 프레임 자동 계산
	m_MaxFrame = (int)(m_TEXTURE->GetHeight() / (int)m_SCALE.y);

	// 프레임 보정
	if (1 != m_MaxFrame)
	{
		m_MaxFrame -= 1;
	}

	// 프레임당 걸리는 시간
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

	// 패널 위 위치를 잡아야됨..
	FloatPoint tPOS = { vResolution.x * 0.70 - 5, vResolution.y * 0.9 + 5 };

		// 이상한 복사생성자 에러가 난다.. 해결이 일단 안되니까 다른 방법으로 구현하자..
		//FloatPoint tSCALE = GetOwner()->GetScale();
		// 임시코드

		BitBlt(tDC
		, (int)tPOS.x - (int)(m_SCALE.x * 0.5)
		, (int)tPOS.y - (int)(m_SCALE.y * 0.5)
		, (int)m_TEXTURE->GetWidth()
		, (int)m_SCALE.y
		, m_TEXTURE->GetDC()
		, 0, (m_SCALE.y * m_Index)
		, SRCCOPY);
}
