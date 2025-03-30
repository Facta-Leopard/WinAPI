#include "PreCompile.h"
#include "TraceState.h"

#include "Player2.h"

#include "StageMGR.h"

TraceState::TraceState()
	: m_TargetObject(nullptr)
{
}

TraceState::~TraceState()
{
}

void TraceState::Enter()
{
	// Level 에서 추적대상 플레이어를 찾는다.
	if (nullptr == m_TargetObject)
	{
		m_TargetObject = StageMGR::GetInstance()->FindObjectByName(LAYER_TYPE::PLAYER1, L"Player1");
	}
}

void TraceState::FinalTick()
{
	// 몬스터의 스탯정보를 가져온다.	
	Player2* pPlayer2 = dynamic_cast<Player2*>(GetOwnerObject());
	assert(pPlayer2);
	const UnitInfomation& info = pPlayer2->GeUnitInfomation();

	// 몬스터의 이동속에 맞게 플레이어를 향해서 이동한다.
	// 이동 방향 계산
	FloatPoint vMoveDir = m_TargetObject->GetPosition() - pPlayer2->GetPosition();
	vMoveDir.Normalize();

	// 해당 방향으로, 속력에 맞게 매프레임마다 이동
	FloatPoint vPos = pPlayer2->GetPosition() + vMoveDir * info.Speed * DELTATIME;
	pPlayer2->SetPosition(vPos);

	// 플레이어가 공격범위 안으로 들어오면 Attack 상태로 변경한다.

	// 만약에 추적중에 피격을 당하면, 피격상태로 전환다.


	// 인지범위 시각화
	DrawDebugCircle(PEN_COLOR::BLUE, pPlayer2->GetPosition(), FloatPoint(info.DetectRange * 2.f, info.DetectRange * 2.f), 0.f);
}

void TraceState::DeInit()
{
}