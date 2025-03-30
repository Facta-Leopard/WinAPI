#pragma once
#include "PreCompile.h"

class Texture;

class CameraMGR
{
	SINGLE(CameraMGR);

private:
	FloatPoint				m_LOOKINGAT;	// ī�޶� �ٶ󺸰� �ִ� ��
	FloatPoint				m_DIFFERENCE;		// ī�޶� ���� ������ �ػ� �߾��� ��ġ ���̰�
	FloatPoint				m_OFFSET;	// ī�޶� �ٶ󺸴� ��ġ���� �߰����� Offset

	Object* m_Target;	// ī�޶� Ÿ�� ������Ʈ

	bool				m_ScreenMoveable;

	float				m_Duration;    // ���� �����ð�
	float				m_Amplitude;   // ����
	float				m_Frequency;   // �ʴ� ����Ƚ��
	float				m_Time;		   // �����ð�
	float				m_Dir;		   // ���� ����
	bool				m_bOscillation;// ���� On / Off

	Texture* m_CAMERATEXTURE;
	Texture* m_CAMERATEXTURE1;

	list<CameraEffect>	m_CamEffectList;

public:
	void Init();
	void Tick();
	void Render();

	// ȭ�� ���� �� �̵�����

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

	// ������������ �ȵǼ� ī�޶�� �ű�
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