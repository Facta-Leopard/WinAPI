#pragma once
#include "PreCompile.h"

class TimeMGR
{
	SINGLE(TimeMGR);

private:
	LARGE_INTEGER	m_Frequency;
	LARGE_INTEGER	m_PrevCount;
	LARGE_INTEGER	m_CurCount;

	UINT			m_Fps;
	float			m_DELTATIME;	// Delta Time : 프레임 간격 시간, 1 프레임 동작하는데 걸리는 시간
	float			m_Time; // 프로그램을 킨 이후로 지난 누적시간

	bool			m_TimeStop;


	// 재생시 타이머 대용으로 사용할 변수들
	float			m_Timer1Started;
	float			m_Timer1Passed;
	float			m_TimerStandard;
	bool			m_Timer1Check;

public:
	void Init();
	void Tick();

public:
	float GetDELTATIME()
	{
		return m_DELTATIME;
	}

	void SetOnTimeStop()
	{
		m_TimeStop = true;
	}

	void SetOffTimeStop()
	{
		m_TimeStop = false;
	}

	float GetTimerCheck()
	{
		return m_Timer1Check;
	}

	void SetTimerStandard(float _Duration);

	void StartTimerCheck(float _Duration);
};