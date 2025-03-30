#include "PreCompile.h"
#include "CameraMGR.h"

CameraMGR::CameraMGR()
	: m_Target(nullptr)

	, m_ScreenMoveable(false)

	, m_Duration(0.f)
	, m_Amplitude(0.f)
	, m_Frequency(0.f)
	, m_Time(0.f)
	, m_Dir(1.f)
	, m_bOscillation(false)
{
	FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();
	m_CAMERATEXTURE = AssetMGR::GetInstance()->CreateTexture(L"CameraTex", (UINT)vResolution.x, (UINT)vResolution.y);
	m_CAMERATEXTURE1 = AssetMGR::GetInstance()->CreateTexture(L"CameraTex1", (UINT)vResolution.x, (UINT)vResolution.y);

	// 매크로 정의
// #define SELECT_PEN(Pen) SelectGDI SelectPen(GameEngine::GetInstance()->GetMemoryDC(), GameEngine::GetInstance()->GetPen(Pen));
// #define SELECT_BRUSH(Brush) SelectGDI SelectBrush(GameEngine::GetInstance()->GetMemoryDC(), GameEngine::GetInstance()->GetBrush(Brush));


	// m_CAMERATEXTURE1 전체를 red 색으로 채운다.
	HBRUSH hPrev = (HBRUSH)SelectObject(m_CAMERATEXTURE1->GetDC(), GameEngine::GetInstance()->GetBrush(BRUSH_COLOR::RED));
	Rectangle(m_CAMERATEXTURE1->GetDC(), -1, -1, (int)vResolution.x + 1, (int)vResolution.y + 1);
	SelectObject(m_CAMERATEXTURE1->GetDC(), hPrev);
}

CameraMGR::~CameraMGR()
{
}

void CameraMGR::Init()
{
	FloatPoint Resolution = GameEngine::GetInstance()->GetResolution();
	m_LOOKINGAT = Resolution * 0.5;

	m_OFFSET = FloatPoint(0.f, 0.f);
}

void CameraMGR::Tick()
{
	FloatPoint Resolution = GameEngine::GetInstance()->GetResolution();
	m_DIFFERENCE = (m_LOOKINGAT + m_OFFSET) - (Resolution * 0.5);

	// 화면이동 제어관련
	if (m_ScreenMoveable)
	{
		if (KEY_PRESSED(KEY::UP))
			m_LOOKINGAT.y += DELTATIME * 500.f;
		if (KEY_PRESSED(KEY::DOWN))
			m_LOOKINGAT.y -= DELTATIME * 500.f;
		if (KEY_PRESSED(KEY::LEFT))
			m_LOOKINGAT.x += DELTATIME * 500.f;
		if (KEY_PRESSED(KEY::RIGHT))
			m_LOOKINGAT.x -= DELTATIME * 500.f;
	}

	if (m_Target)
	{
		m_LOOKINGAT = m_Target->GetPosition();
	}


	// 화면 벗어나기 방지
	if (5 >= m_LOOKINGAT.x)
	{
		m_LOOKINGAT.x = 5;
	}
	else if (RESOLUTION.x <= m_LOOKINGAT.x)
	{
		m_LOOKINGAT.x = RESOLUTION.x;
	}
	if (5 >= m_LOOKINGAT.y)
	{
		m_LOOKINGAT.y = 5;
	}
	else if (RESOLUTION.y <= m_LOOKINGAT.y)
	{
		m_LOOKINGAT.y = RESOLUTION.y;
	}

	// 카메라 진동 효과
	Oscillation();
}

void CameraMGR::Render()
{
	if (m_CamEffectList.empty())
		return;

	CameraEffect& effect = m_CamEffectList.front();

	// 진행률
	float NormalizedAge = Saturate(effect.Time / effect.Duration);
	int Alpha = 0;
	Texture* pTex = nullptr;

	// FADE_IN : 점점 밝아진다		255 -> 0
	// FADE_OUT : 점점 어두워진다		0 -> 255
	if (FADE_IN == effect.Effect)
	{
		Alpha = (int)(255.f * (1.f - NormalizedAge));
		pTex = m_CAMERATEXTURE;
	}
	else if (FADE_OUT == effect.Effect)
	{
		Alpha = (int)(255.f * NormalizedAge);
		pTex = m_CAMERATEXTURE;
	}
	else if (HEART == effect.Effect)
	{
		NormalizedAge *= 2.f;

		if (NormalizedAge <= 1.f)
		{
			Alpha = (int)(150.f * NormalizedAge);
		}
		else
		{
			NormalizedAge -= 1.f;
			Alpha = (int)(150.f * (1.f - NormalizedAge));
		}

		pTex = m_CAMERATEXTURE1;
	}

	// 후처리 효과시간이 만료되면 기능을 Off 한다.
	effect.Time += DELTATIME;
	if (effect.Duration <= effect.Time)
	{
		m_CamEffectList.pop_front();
	}

	HDC dc = GameEngine::GetInstance()->GetMemoryDC();
	BLENDFUNCTION blend = {};

	blend.BlendOp = AC_SRC_OVER;
	blend.BlendFlags = 0;
	blend.SourceConstantAlpha = Alpha; // 추가 알파블렌드
	blend.AlphaFormat = 0;

	AlphaBlend(dc
		, 0.f, 0.f
		, pTex->GetWidth()
		, pTex->GetHeight()
		, pTex->GetDC()
		, 0, 0
		, pTex->GetWidth()
		, pTex->GetHeight()
		, blend);
}

void CameraMGR::MiniMapRender()
{
	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();

	SELECT_PEN(PEN_COLOR::GREEN);
	SELECT_BRUSH(BRUSH_COLOR::HOLLOW);
	Rectangle(tDC
		, (int)(RESOLUTION.x * 0.05) + 5 - (int)(m_DIFFERENCE.x * 0.1)
		, (int)(RESOLUTION.y * 0.80) + 5 - (int)(m_DIFFERENCE.y * 0.1)
		, (int)(RESOLUTION.x * 0.15) + 5 - (int)(m_DIFFERENCE.x * 0.1)
		, (int)(RESOLUTION.y * 0.90) + 5 - (int)(m_DIFFERENCE.y * 0.1));
}

void CameraMGR::Oscillation()
{
	if (false == m_bOscillation)
		return;

	float Speed = m_Amplitude * 4.f * m_Frequency;
	m_OFFSET.y += Speed * m_Dir * DELTATIME;

	// 만약 진폭크기를 넘어서버리면, 방향을 전환한다.
	if (m_Amplitude < fabs(m_OFFSET.y))
	{
		// 진폭 최대치로 설정
		m_OFFSET.y = m_Amplitude * m_Dir;

		// 방향 전환
		m_Dir *= -1.f;

		// 초과량을 전환된 방향쪽으로 전진시킴
		m_OFFSET.y += m_Dir * (m_Amplitude - fabs(m_OFFSET.y));
	}

	m_Time += DELTATIME;
	if (m_Duration <= m_Time)
	{
		m_bOscillation = false;
		m_OFFSET = FloatPoint(0.f, 0.f);
	}
}