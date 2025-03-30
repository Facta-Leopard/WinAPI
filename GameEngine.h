#pragma once

#include "Macro.h"
#include "Enum.h"
#include "Texture.h"

extern POINT RESOLUTION;

class GameEngine
{
	SINGLE(GameEngine);

private:
	HINSTANCE	m_HandleInstance;		// ���μ��� �ּ�
	HWND		m_Handle;			// ���� ������ �ڵ�
	POINT		m_Resolution;	// ���� ������ �ػ�

	HDC			m_HANDLEDC;			// Main DC(Device Context) �׸��� ���� ������, �׸��� ���� ����ü

	HPEN		m_PEN[(UINT)PEN_COLOR::EOL];
	HBRUSH		m_Brush[(UINT)BRUSH_COLOR::EOL];

	Texture*	m_BackBuffer;	// ����� �뵵 �ؽ���


public:
	HINSTANCE GetHandleInstance()
	{
		return m_HandleInstance;
	}

	HWND GetMainWndHwnd()
	{
		return m_Handle;
	}
	
	POINT GetResolution()
	{
		return m_Resolution;
	}
	
	HPEN GetPen(PEN_COLOR _COLOR) const
	{
		return m_PEN[(UINT)_COLOR];
	}
	
	HBRUSH GetBrush(BRUSH_COLOR _COLOR) const
	{
		return m_Brush[(UINT)_COLOR];
	}
	
	HDC GetMainDC()
	{
		return m_HANDLEDC;
	}
	
	HDC GetMemoryDC()
	{
		return m_BackBuffer->GetDC();
	}

private:
	void CreateGDIObject();

	void CreateSecondBuffer();

public:
	int Init(HINSTANCE _HandleInstance, POINT _Resolution);

	void Tick();

	void ChangeWindowSize(POINT _Resolution);
};
