#pragma once

#include "Macro.h"
#include "Enum.h"
#include "Texture.h"

extern POINT RESOLUTION;

class GameEngine
{
	SINGLE(GameEngine);

private:
	HINSTANCE	m_HandleInstance;		// 프로세스 주소
	HWND		m_Handle;			// 메인 윈도우 핸들
	POINT		m_Resolution;	// 메인 윈도우 해상도

	HDC			m_HANDLEDC;			// Main DC(Device Context) 그리기 관련 관리자, 그리기 도구 집합체

	HPEN		m_PEN[(UINT)PEN_COLOR::EOL];
	HBRUSH		m_Brush[(UINT)BRUSH_COLOR::EOL];

	Texture*	m_BackBuffer;	// 백버퍼 용도 텍스쳐


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
