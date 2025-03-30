#pragma once
#include "PreCompile.h"

#include "R_UI.h"

// 모든 UI 들 중에서 어떤 UI 가 Focuse 상태인지 검사
// Focuse 중인 UI 만 이벤트 처리가 될 수 있도록 모든 UI 를 관리 및 검사하는 역할
class UIMGR
{
	SINGLE(UIMGR);

private:
	R_UI* m_FocusedUI;	// 포커싱 되어있는 UI
	R_UI* m_PriorityUI;	// 포커싱 되어있는 UI 내에서 다시 가장 우선순위가 높은 UI

public:
	void Tick();

private:
	void ReleaseCheck(R_UI* _UI);

private:
	R_UI* GetPriorityUI(R_UI* _ParentUI);

};