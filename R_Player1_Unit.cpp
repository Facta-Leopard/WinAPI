#include "PreCompile.h"
//#include "Player_Unit.h"
//
//#include "Stage.h"
//#include "Collider.h"
//
//#include "StageMGR.h"
//
//Player1Unit::Player1Unit()
//	: m_Target(nullptr)
//	, m_DetectRange(700.f)
//{
//	GetCollider()->SetScale(FloatPoint(50.f, 50.f));
//}
//
//Player1Unit::~Player1Unit()
//{
//}
//
//void Player1Unit::Tick()
//{
//	// Ÿ���� ��ȿ�ϸ�
//	if (IsValid(m_Target))
//	{
//		//TraceTarget_0();
//		//TraceTarget_1();
//		TraceTarget_2();
//	}
//
//	// Ÿ���� ��ȿ���� ������
//	else
//	{
//		// ���� ����� ã�´�.
//		FindTarget();
//	}
//
//	DrawDebugCircle(PEN_COLOR::BLUE, GetCameraViewPosition(), FloatPoint(m_DetectRange * 2.f, m_DetectRange * 2.f), 0.f);
//
//	Player1Building::Tick();
//}
//
//void Player1Unit::FindTarget()
//{
//	m_Target = nullptr;
//
//	Stage* pCURRENTSTAGE = StageMGR::GetInstance()->GetCurrentStage();
//	const vector<Object*>& vecMon = pCURRENTSTAGE->GetObjects(LAYER_TYPE::PLAYER2);
//
//	// �̻��� ���ΰ� ���� ����� ����� Ÿ������ �����Ѵ�.
//	FloatPoint vPos = GetPosition(); // �̻��� ������ ��ġ
//	float MinDistance = m_DetectRange;
//
//	for (size_t i = 0; i < vecMon.size(); ++i)
//	{
//		if (vecMon[i]->IsDead())
//			continue;
//
//		FloatPoint vMonPos = vecMon[i]->GetPosition(); // ������ ��ġ
//		float Dist = (vPos - vMonPos).Length();
//
//		// �ּҰŸ��� ���ŵ� ���
//		if (Dist < MinDistance)
//		{
//			MinDistance = Dist;
//			m_Target = vecMon[i];
//		}
//	}
//}
//
//void Player1Unit::TraceTarget_0()
//{
//	// Ÿ���� ���ؼ� �̵������� �����Ѵ�.
//	FloatPoint vDir = (m_Target->GetPosition() - GetPosition());
//	vDir.Normalize(); // �������� ���� ��������
//	vDir *= GetVelocity().Length();
//	SetVelocity(vDir);
//}
//
//void Player1Unit::TraceTarget_1()
//{
//	// Ÿ���� ���ؼ� ���� �ش�.
//	// 1. Ÿ���� ���� ������ �˾Ƴ���.
//	FloatPoint vDir = m_Target->GetPosition() - GetPosition();
//	vDir.Normalize();
//	AddForce(vDir * 500.f);
//}
//
//void Player1Unit::TraceTarget_2()
//{
//	// Ÿ���� ���� ������ ���ֺ����� ȸ���� ��Ų��.
//	FloatPoint V = GetVelocity();
//	V.Normalize();
//
//	// Ÿ���� ���� ������ ���Ѵ�.
//	FloatPoint vDir = m_Target->GetPosition() - GetPosition();
//	vDir.Normalize();
//
//	// ���� ����� Ÿ���� ���� ���� ������ ������ ���Ѵ�
//	float Dot = V.DotProduct(vDir);
//	float fTheta = acosf(Dot);
//
//	// ������ 60�й����� ����
//	float Degree = fabs((fTheta * 180.f) / PI);
//
//	// ���� �����, �������� ���� ������ ������ ���� �ӵ��� ������ �����Ų��.
//	float Scale = Degree / 90.f;
//	if (1.f < Scale)
//		Scale = 1.f;
//	Scale = 1.f - Scale;
//	Scale = 0.3f + Scale * 0.7f;
//	SetVelocityScale(Scale);
//
//	// �� ������ ������ 0 �� �ƴϸ� ȸ���� �Ѵ�.
//	if (!(0.f <= Degree && Degree <= 2.f))
//	{
//		float RotateDir = 0.f;
//		if (GetClockWise(V, vDir))
//			RotateDir = 1.f;
//		else
//			RotateDir = -1.f;
//
//		FloatPoint vRotate = Rotate(V, RotateDir * PI * DELTATIME * 0.5f);
//		vRotate *= GetVelocity().Length();
//		SetVelocity(vRotate);
//	}
//
//	// ����
//	// - �� ���⺤�� ������ ������ ��� ( �ӵ��� ���ϴ� ����, Ÿ���� ���� ����, �� ���ͻ����� ���� )
//	// - ���翵, �� ���͸� �ٸ� ���ͷ� ������Ų ����
//	// - ������� ����� ���� ��
//
//	// ����
//	// - 3���� ���������� ������ ���� �� --> ����ź�� ȸ���� ����(�ð� or �ݽð�)
//	// - ����纯�� ����, Intersects ������ �ﰢ���� ��� �˻�
//}
//
//void Player1Unit::BeginOverlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER)
//{
//	if (_OTHEROBJECT->GetName() == L"Player2")
//	{
//		DeleteObject(this);
//		//DeleteObject(_OTHEROBJECT);
//	}
//}