#include "PreCompile.h"
#include "TimeMGR.h"

TimeMGR::TimeMGR()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_Fps(0)
	, m_DELTATIME(0.f)
	, m_Time(0.f)
	, m_TimeStop(false)

	, m_Timer1Started(0.f)
	, m_Timer1Passed(0.f)
	, m_TimerStandard(0.f)
	, m_Timer1Check(false)
{
}

TimeMGR::~TimeMGR()
{

}

void TimeMGR::Init()
{
	// 1초에 1000 카운팅 -> 초당 카운팅 양이 너무 적음
	//GetTickCount64();

	// 프레임과 프레임 사이의 시간
	QueryPerformanceFrequency(&m_Frequency); // 초당 카운팅 값 (천만)
	QueryPerformanceCounter(&m_PrevCount);
}

void TimeMGR::Tick()
{
	// 현재시점 Count 값
	QueryPerformanceCounter(&m_CurCount);

	m_DELTATIME = (float)(m_CurCount.QuadPart - m_PrevCount.QuadPart) / (float)m_Frequency.QuadPart;

	if (m_TimeStop)
	{
		m_DELTATIME = 0;
	}

	m_PrevCount = m_CurCount;

	++m_Fps;
	m_Time += m_DELTATIME;

	if (1.f <= m_Time)
	{
		wchar_t buff[255] = {};
		swprintf_s(buff, 255, L"FPS : %d, DELTATIME : %f", m_Fps, m_DELTATIME);
		SetWindowText(GameEngine::GetInstance()->GetMainWndHwnd(), buff);

		m_Fps = 0;
		m_Time -= 1.f;
	}

	if (m_Timer1Check)
	{
		StartTimerCheck(m_TimerStandard);
	}
}

void TimeMGR::SetTimerStandard(float _Duration)
{
	m_Timer1Check = true;
	m_TimerStandard = _Duration;
}

void TimeMGR::StartTimerCheck(float _Duration)
{
	if (!m_Timer1Started)
	{
		m_Timer1Passed = m_Timer1Started;
	}
	m_Timer1Started += GetTickCount64();
	
	if (m_TimerStandard < m_Timer1Started)
	{
		m_Timer1Started = 0;
		m_Timer1Passed = m_Timer1Started;
		m_Timer1Check = false;
	}
}
