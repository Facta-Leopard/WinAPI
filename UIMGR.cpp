#include "PreCompile.h"
#include "UIMGR.h"

#include "R_UI.h"

#include "Stage.h"
#include "StageMGR.h"

UIMGR::UIMGR()
	: m_FocusedUI(nullptr)
	, m_PriorityUI(nullptr)
{

}

UIMGR::~UIMGR()
{

}

void UIMGR::Tick()
{
	// ���� ���������ȿ� �ִ� UI ���� �����´�.
	Stage* pCURRENTSTAGE = StageMGR::GetInstance()->GetCurrentStage();

	// ���������� �߰��� �ֻ��� �θ� UI ��
	vector<Object*>& VECTORUI = pCURRENTSTAGE->m_VECTOROBJECTS[(UINT)LAYER_TYPE::UI_BASE];

	// ���콺 ���ʹ�ư�� ���� ��Ȳ üũ
	KEY_STATE LBtnState = KeyMGR::GetInstance()->GetKeyState(KEY::LBTN);

	// reverse itertor �� �̿��ؼ� vector �� �������� ��ȸ�Ѵ�.
	vector<Object*>::reverse_iterator riter = VECTORUI.rbegin();
	for (; riter != VECTORUI.rend(); ++riter)
	{
		// UI ���̾ �ִ� ������Ʈ�� ��¥ UI ��ü���� Ȯ�� �� �ٿ�ĳ����
		R_UI* pParentUI = dynamic_cast<R_UI*>((*riter));
		assert(pParentUI);

		// �ֻ��� �θ� UI ����, ������ �ڽĵ� �� ���� �켱������ ���� UI �� ã�Ƽ� ��ȯ�Ѵ�.
		R_UI* pPriorityUI = GetPriorityUI(pParentUI);
		if (nullptr == pPriorityUI)
		{
			ReleaseCheck(pParentUI);
			continue;
		}

		// UI �� ���ȴ��� Ȯ��
		if (LBtnState == KEY_STATE::TAP)
		{
			pPriorityUI->m_LBtnDown = true;
			pPriorityUI->MouseLBtnDown();

			// vector ���� ���� �� ���� �ڷ� �����ش�.
			VECTORUI.erase((++riter).base());
			VECTORUI.push_back(pParentUI);
			break;
		}

		// UI �� Ŭ���ƴ��� üũ
		if (LBtnState == KEY_STATE::RELEASED)
		{
			if (pPriorityUI->m_LBtnDown)
				pPriorityUI->MouseLBtnClikced();
			else
				pPriorityUI->MouseReleased();

			// LBtn Ű�� �����Ǿ��� ������, ���� ���¸� �����Ѵ�.			
			ReleaseCheck(pParentUI);
		}
	}
}

R_UI* UIMGR::GetPriorityUI(R_UI* _ParentUI)
{
	R_UI* pPriorityUI = nullptr;

	// Queue ������ �� List
	static list<R_UI*> queue;
	queue.clear();

	// �ֻ��� �θ� UI �Է�
	queue.push_back(_ParentUI);

	// Queue �� ������� �ʴٸ� �ݺ��� ����
	while (!queue.empty())
	{
		R_UI* pR_UI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pR_UI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pR_UI->m_vecChildUI[i]);
		}

		if (pR_UI->IsMouseHover())
			pPriorityUI = pR_UI;
	}

	return pPriorityUI;
}


void UIMGR::ReleaseCheck(R_UI* _UI)
{
	// Queue ������ �� List
	static list<R_UI*> queue;
	queue.clear();

	// �ֻ��� �θ� UI �Է�
	queue.push_back(_UI);

	// Queue �� ������� �ʴٸ� �ݺ��� ����
	while (!queue.empty())
	{
		R_UI* pR_UI = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pR_UI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pR_UI->m_vecChildUI[i]);
		}

		if (KEY_RELEASED(KEY::LBTN))
			pR_UI->m_LBtnDown = false;
	}
}