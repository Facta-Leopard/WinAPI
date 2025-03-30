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
	// 현재 스테이지안에 있는 UI 들을 가져온다.
	Stage* pCURRENTSTAGE = StageMGR::GetInstance()->GetCurrentStage();

	// 스테이지에 추가된 최상위 부모 UI 들
	vector<Object*>& VECTORUI = pCURRENTSTAGE->m_VECTOROBJECTS[(UINT)LAYER_TYPE::UI_BASE];

	// 마우스 왼쪽버튼이 눌린 상황 체크
	KEY_STATE LBtnState = KeyMGR::GetInstance()->GetKeyState(KEY::LBTN);

	// reverse itertor 를 이용해서 vector 를 역순으로 순회한다.
	vector<Object*>::reverse_iterator riter = VECTORUI.rbegin();
	for (; riter != VECTORUI.rend(); ++riter)
	{
		// UI 레이어에 있는 오브젝트가 진짜 UI 객체인지 확인 및 다운캐스팅
		R_UI* pParentUI = dynamic_cast<R_UI*>((*riter));
		assert(pParentUI);

		// 최상위 부모 UI 포함, 본인의 자식들 중 가장 우선순위가 높은 UI 를 찾아서 반환한다.
		R_UI* pPriorityUI = GetPriorityUI(pParentUI);
		if (nullptr == pPriorityUI)
		{
			ReleaseCheck(pParentUI);
			continue;
		}

		// UI 가 눌렸는지 확인
		if (LBtnState == KEY_STATE::TAP)
		{
			pPriorityUI->m_LBtnDown = true;
			pPriorityUI->MouseLBtnDown();

			// vector 에서 제거 후 가장 뒤로 보내준다.
			VECTORUI.erase((++riter).base());
			VECTORUI.push_back(pParentUI);
			break;
		}

		// UI 가 클릭됐는지 체크
		if (LBtnState == KEY_STATE::RELEASED)
		{
			if (pPriorityUI->m_LBtnDown)
				pPriorityUI->MouseLBtnClikced();
			else
				pPriorityUI->MouseReleased();

			// LBtn 키가 해제되었기 때문에, 눌린 상태를 해제한다.			
			ReleaseCheck(pParentUI);
		}
	}
}

R_UI* UIMGR::GetPriorityUI(R_UI* _ParentUI)
{
	R_UI* pPriorityUI = nullptr;

	// Queue 역할을 할 List
	static list<R_UI*> queue;
	queue.clear();

	// 최상위 부모 UI 입력
	queue.push_back(_ParentUI);

	// Queue 가 비어있지 않다면 반복문 실행
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
	// Queue 역할을 할 List
	static list<R_UI*> queue;
	queue.clear();

	// 최상위 부모 UI 입력
	queue.push_back(_UI);

	// Queue 가 비어있지 않다면 반복문 실행
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