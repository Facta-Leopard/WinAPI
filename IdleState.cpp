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
//	// 소유자(몬스터) 의 R_AnimationPlayer 를 이용해서 특정 플립북(애니메이션) 을 재생시킨다.
//	R_AnimationPlayer* pR_AnimationPlayer = GetOwnerObject()->GetComponent<R_AnimationPlayer>();
//	if (pR_AnimationPlayer)
//	{
//		//pR_AnimationPlayer->Play();
//	}
}

void IdleState::FinalTick()
{
	// Level 안에 있는 플레이어를 찾는다.
	if (nullptr == m_TARGETOBJECT)
	{
		m_TARGETOBJECT = StageMGR::GetInstance()->FindObjectByName(LAYER_TYPE::PLAYER1, L"Player1");
	}

	// 몬스터의 스탯을 가져온다.
	Player2* pUnit = dynamic_cast<Player2*>(GetOwnerObject());

	assert(pUnit);

	const UnitInfomation& info = pUnit->GeUnitInfomation();

	// 플레이어가 몬스터의 인지범위 내에 있는지 확인한다.
	if (m_TARGETOBJECT)
	{
		FloatPoint vTargetPos = m_TARGETOBJECT->GetPosition();
		FloatPoint vPos = pUnit->GetPosition();
		float fDist = (vTargetPos - vPos).Length();

		// 범위 안에 있으면 자신의 상태를 TraceState
		if (fDist < info.DetectRange)
		{
			GetFSM()->ChangeState(L"Trace");
		}
	}

	// 인지범위 시각화
	DrawDebugCircle(PEN_COLOR::BLUE, pUnit->GetPosition(), FloatPoint(info.DetectRange * 2.f, info.DetectRange * 2.f), 0.f);
}

void IdleState::DeInit()
{
}