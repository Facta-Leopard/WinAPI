#pragma once
#include "PreCompile.h"

class KeyMGR
{
	SINGLE(KeyMGR);

public:
	void Init();
	void Tick();

private:
	vector<KeyInfo>		m_vecKeyInfo;
	FloatPoint			m_MOUSEPOS;
	vector<HCURSOR>		m_HANDLECURSOR;

	// 마우스 커서 변경 적용
	CURSOR_TYPE			m_CURSORSTATE;

	// 드래그앤드랍 박스 좌표설정용
	DragAndDrop			m_DragAndDropBox;

public:
	KEY_STATE GetKeyState(KEY _key)
	{
		return m_vecKeyInfo[_key].STATE;
	}
	
	FloatPoint GetMousePos()
	{
		return m_MOUSEPOS;
	}

	void SetCursorType(CURSOR_TYPE _CURSORTYPE);

	void SetMouseCursor(CURSOR_TYPE _CURSOR_TYPE);

	DragAndDrop GetDragAndDropBox()
	{
		return m_DragAndDropBox;
	};

	void SetDragAndDropBox(DragAndDrop _BOX);

	bool IsMouseOffScreen();


};