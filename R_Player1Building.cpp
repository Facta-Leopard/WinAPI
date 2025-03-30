#include "PreCompile.h"
#include "R_Player1Building.h"

#include "Collider.h"

#include "PortraitMGR.h"
#include "Player1_Building.h"

//R_Player1Building::R_Player1Building(wstring _Name)
//	: m_Mass(1.f)
//	, m_VelocityScale(1.f)
//	, m_VECTOR_MOVINGMOTION()
//	, m_ShieldPoint(0.f)
//	, m_IsHitPoint(100.f)
//	, m_Direction(0.f)
//	, m_RIGIDBODY(nullptr)
//	, m_OrderMove(false)
//	, m_OrderAttack(false)
//{
//	SetName(_Name);
//	m_COLLIDER = (Collider*)AddComponent(new Collider);
//	m_RIGIDBODY = (RigidBody*)AddComponent(new RigidBody);
//	m_COLLIDER->SetScale(FloatPoint(32.f, 32.f));
//
//	m_VELOCITY = FloatPoint(1.f, 1.f);
//	m_VELOCITY.Normalize();
//	m_VELOCITY *= 500.f;
//	vector<MovingMotion> tVector = PortraitMGR::GetInstance()->m_VECTOR_MOVINGMOTION;
//	for (vector<MovingMotion>::iterator i = tVector.begin(); i != tVector.end(); i++)
//	{
//		m_VECTOR_MOVINGMOTION.push_back(*i);
//	}
//}
//
//R_Player1Building::~R_Player1Building()
//{
//}
//
//void R_Player1Building::Tick()
//{
//	// ������ ���� Ȯ���Ѵ�.
//	// ������ �������ؼ� ���ܳ� ���ӵ��� ����Ѵ�.
//	// F = M * A
//	FloatPoint vAccel = m_Force / m_Mass;
//
//	// ���ӵ��� ���� �ӵ��� ��ȭ ����
//	m_VELOCITY += vAccel * DELTATIME;
//
//
//	// �ӵ��� ���� �̵�
//	FloatPoint vPos = GetPosition();
//	vPos += m_VELOCITY * m_VelocityScale * DELTATIME;
//	SetPosition(vPos);
//
//	DrawDebugLine(PEN_COLOR::BLUE, GetCameraViewPosition(), GetCameraViewPosition() + m_VELOCITY * 0.1f, 0.f);
//
//	// �������� �� ����
//	m_Force = FloatPoint(0.f, 0.f);
//
//	// �������� �� m_VECTOR_MOVINGMOTION ���� ����
//	CurrentDirectionTypeCheck(m_Direction);
//	MOVINGMOTION_TYPE i = CurrentMovingMotionTypecCheck(CurrentDirectionTypeCheck(m_Direction), m_OrderMove, m_OrderAttack);
//
//	m_VECTOR_MOVINGMOTION[i].FinalTick();
//}
//
//void R_Player1Building::Render()
//{
//	HDC dc = GameEngine::GetInstance()->GetMemoryDC();
//
//	FloatPoint vPos = GetCameraViewPosition();
//	FloatPoint vScale = GetScale();
//
//	Rectangle(dc, vPos.x - vScale.x * 0.5, vPos.y - vScale.y / 2
//		, vPos.x + vScale.x * 0.5, vPos.y + vScale.y * 0.5);
//}