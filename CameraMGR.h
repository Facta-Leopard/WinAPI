#pragma once
#include "PreCompile.h"

class Texture;

class CameraMGR
{
	SINGLE(CameraMGR);

private:
	FloatPoint				m_LOOKINGAT;	// 카메라가 바라보고 있는 곳
	FloatPoint				m_DIFFERENCE;		// 카메라가 보는 지점과 해상도 중앙의 위치 차이값
	FloatPoint				m_OFFSET;	// 카메라가 바라보는 위치에서 추가적인 Offset

	Object* m_Target;	// 카메라 타겟 오브젝트

	bool				m_ScreenMoveable;

	float				m_Duration;    // 진동 유지시간
	float				m_Amplitude;   // 진촉
	float				m_Frequency;   // 초당 진동횟수
	float				m_Time;		   // 누적시간
	float				m_Dir;		   // 진동 방향
	bool				m_bOscillation;// 진동 On / Off

	Texture* m_CAMERATEXTURE;
	Texture* m_CAMERATEXTURE1;

	list<CameraEffect>	m_CamEffectList;

public:
	void Init();
	void Tick();
	void Render();

	// 화면 고정 및 이동관련

	bool GetScreenMoveable()
	{
		return m_ScreenMoveable;
	}

	void SetOnScreenMoveable()
	{
		m_ScreenMoveable = true;
	}

	void SetOffScreenMoveable()
	{
		m_ScreenMoveable = false;
	}

	// 스테이지에서 안되서 카메라로 옮김
	void MiniMapRender();

private:
	void Oscillation();

public:
	FloatPoint GetCameraView(FloatPoint _RealPos)
	{
		return _RealPos - m_DIFFERENCE;
	}

	FloatPoint GetInGameView(FloatPoint _RenderPos)
	{
		return _RenderPos + m_DIFFERENCE;
	}

	FloatPoint GetLookAt()
	{
		return m_LOOKINGAT + m_OFFSET;
	}

	void  SetLookAt(float _DifferenceX, float _DifferenceY)
	{
		m_LOOKINGAT.x += _DifferenceX * DELTATIME;
		m_LOOKINGAT.y += _DifferenceY * DELTATIME;
	}

	void SetLookAtCentre()
	{
		m_LOOKINGAT.x = RESOLUTION.x * 0.5;
		m_LOOKINGAT.y = RESOLUTION.y * 0.5;
	}

	void SetTarget(Object* _Target)
	{
		m_Target = _Target;
	}

	void Oscillation(float _Duration, float _Amplitude, float _Frequency)
	{
		m_Duration = _Duration;
		m_Amplitude = _Amplitude;
		m_Frequency = _Frequency;
		m_Time = 0.f;
		m_bOscillation = true;
		m_Dir = 1.f;
	}

	void PostProcessEffect(POST_PROCESS _TYPE, float _Duration)
	{
		m_CamEffectList.push_back(CameraEffect{ _TYPE , 0.f, _Duration });
	}
};