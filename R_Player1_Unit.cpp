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
//	// 타겟이 유효하면
//	if (IsValid(m_Target))
//	{
//		//TraceTarget_0();
//		//TraceTarget_1();
//		TraceTarget_2();
//	}
//
//	// 타겟이 유효하지 않으면
//	else
//	{
//		// 다음 대상을 찾는다.
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
//	// 미사일 본인과 가장 가까운 대상을 타겟으로 지정한다.
//	FloatPoint vPos = GetPosition(); // 미사일 본인의 위치
//	float MinDistance = m_DetectRange;
//
//	for (size_t i = 0; i < vecMon.size(); ++i)
//	{
//		if (vecMon[i]->IsDead())
//			continue;
//
//		FloatPoint vMonPos = vecMon[i]->GetPosition(); // 몬스터의 위치
//		float Dist = (vPos - vMonPos).Length();
//
//		// 최소거리가 갱신된 경우
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
//	// 타겟을 향해서 이동방향을 설정한다.
//	FloatPoint vDir = (m_Target->GetPosition() - GetPosition());
//	vDir.Normalize(); // 목적지를 향한 방향정보
//	vDir *= GetVelocity().Length();
//	SetVelocity(vDir);
//}
//
//void Player1Unit::TraceTarget_1()
//{
//	// 타겟을 향해서 힘을 준다.
//	// 1. 타겟을 향한 방향을 알아낸다.
//	FloatPoint vDir = m_Target->GetPosition() - GetPosition();
//	vDir.Normalize();
//	AddForce(vDir * 500.f);
//}
//
//void Player1Unit::TraceTarget_2()
//{
//	// 타겟을 향한 방향을 마주보도록 회전을 시킨다.
//	FloatPoint V = GetVelocity();
//	V.Normalize();
//
//	// 타겟을 향한 방향을 구한다.
//	FloatPoint vDir = m_Target->GetPosition() - GetPosition();
//	vDir.Normalize();
//
//	// 진행 방향과 타겟을 향한 방향 사이의 각도를 구한다
//	float Dot = V.DotProduct(vDir);
//	float fTheta = acosf(Dot);
//
//	// 라디안을 60분법으로 변경
//	float Degree = fabs((fTheta * 180.f) / PI);
//
//	// 진행 방향과, 목적지를 향한 방향의 각도에 따라서 속도에 배율을 적용시킨다.
//	float Scale = Degree / 90.f;
//	if (1.f < Scale)
//		Scale = 1.f;
//	Scale = 1.f - Scale;
//	Scale = 0.3f + Scale * 0.7f;
//	SetVelocityScale(Scale);
//
//	// 두 벡터의 각도가 0 이 아니면 회전을 한다.
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
//	// 내적
//	// - 두 방향벡터 사이의 각도를 계산 ( 속도가 향하는 방향, 타겟을 향한 방향, 두 벡터사이의 각도 )
//	// - 정사영, 한 벡터를 다른 벡터로 투영시킨 길이
//	// - 직교행렬 역행렬 구할 때
//
//	// 외적
//	// - 3차원 직교벡터의 방향을 구할 때 --> 유도탄이 회전할 방향(시계 or 반시계)
//	// - 평행사변의 넓이, Intersects 직선이 삼각형을 통과 검사
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