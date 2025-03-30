#pragma once
#include "PreCompile.h"

#include "R_UI.h"

// ��� UI �� �߿��� � UI �� Focuse �������� �˻�
// Focuse ���� UI �� �̺�Ʈ ó���� �� �� �ֵ��� ��� UI �� ���� �� �˻��ϴ� ����
class UIMGR
{
	SINGLE(UIMGR);

private:
	R_UI* m_FocusedUI;	// ��Ŀ�� �Ǿ��ִ� UI
	R_UI* m_PriorityUI;	// ��Ŀ�� �Ǿ��ִ� UI ������ �ٽ� ���� �켱������ ���� UI

public:
	void Tick();

private:
	void ReleaseCheck(R_UI* _UI);

private:
	R_UI* GetPriorityUI(R_UI* _ParentUI);

};