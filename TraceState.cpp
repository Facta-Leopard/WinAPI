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
	// Level ���� ������� �÷��̾ ã�´�.
	if (nullptr == m_TargetObject)
	{
		m_TargetObject = StageMGR::GetInstance()->FindObjectByName(LAYER_TYPE::PLAYER1, L"Player1");
	}
}

void TraceState::FinalTick()
{
	// ������ ���������� �����´�.	
	Player2* pPlayer2 = dynamic_cast<Player2*>(GetOwnerObject());
	assert(pPlayer2);
	const UnitInfomation& info = pPlayer2->GeUnitInfomation();

	// ������ �̵��ӿ� �°� �÷��̾ ���ؼ� �̵��Ѵ�.
	// �̵� ���� ���
	FloatPoint vMoveDir = m_TargetObject->GetPosition() - pPlayer2->GetPosition();
	vMoveDir.Normalize();

	// �ش� ��������, �ӷ¿� �°� �������Ӹ��� �̵�
	FloatPoint vPos = pPlayer2->GetPosition() + vMoveDir * info.Speed * DELTATIME;
	pPlayer2->SetPosition(vPos);

	// �÷��̾ ���ݹ��� ������ ������ Attack ���·� �����Ѵ�.

	// ���࿡ �����߿� �ǰ��� ���ϸ�, �ǰݻ��·� ��ȯ��.


	// �������� �ð�ȭ
	DrawDebugCircle(PEN_COLOR::BLUE, pPlayer2->GetPosition(), FloatPoint(info.DetectRange * 2.f, info.DetectRange * 2.f), 0.f);
}

void TraceState::DeInit()
{
}