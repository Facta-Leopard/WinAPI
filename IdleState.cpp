#include "PreCompile.h"
#include "IdleState.h"
#include "Object.h"
#include "Player2.h"

#include "StageMGR.h"

IdleState::IdleState()
	: m_TARGETOBJECT(nullptr)
{
}

IdleState::~IdleState()
{
}

void IdleState::Enter()
{
//	// ������(����) �� R_AnimationPlayer �� �̿��ؼ� Ư�� �ø���(�ִϸ��̼�) �� �����Ų��.
//	R_AnimationPlayer* pR_AnimationPlayer = GetOwnerObject()->GetComponent<R_AnimationPlayer>();
//	if (pR_AnimationPlayer)
//	{
//		//pR_AnimationPlayer->Play();
//	}
}

void IdleState::FinalTick()
{
	// Level �ȿ� �ִ� �÷��̾ ã�´�.
	if (nullptr == m_TARGETOBJECT)
	{
		m_TARGETOBJECT = StageMGR::GetInstance()->FindObjectByName(LAYER_TYPE::PLAYER1, L"Player1");
	}

	// ������ ������ �����´�.
	Player2* pUnit = dynamic_cast<Player2*>(GetOwnerObject());

	assert(pUnit);

	const UnitInfomation& info = pUnit->GeUnitInfomation();

	// �÷��̾ ������ �������� ���� �ִ��� Ȯ���Ѵ�.
	if (m_TARGETOBJECT)
	{
		FloatPoint vTargetPos = m_TARGETOBJECT->GetPosition();
		FloatPoint vPos = pUnit->GetPosition();
		float fDist = (vTargetPos - vPos).Length();

		// ���� �ȿ� ������ �ڽ��� ���¸� TraceState
		if (fDist < info.DetectRange)
		{
			GetFSM()->ChangeState(L"Trace");
		}
	}

	// �������� �ð�ȭ
	DrawDebugCircle(PEN_COLOR::BLUE, pUnit->GetPosition(), FloatPoint(info.DetectRange * 2.f, info.DetectRange * 2.f), 0.f);
}

void IdleState::DeInit()
{
}