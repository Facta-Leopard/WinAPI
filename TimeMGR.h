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
	float			m_DELTATIME;	// Delta Time : ������ ���� �ð�, 1 ������ �����ϴµ� �ɸ��� �ð�
	float			m_Time; // ���α׷��� Ų ���ķ� ���� �����ð�

	bool			m_TimeStop;


	// ����� Ÿ�̸� ������� ����� ������
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