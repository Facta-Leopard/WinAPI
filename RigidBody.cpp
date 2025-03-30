#include "PreCompile.h"
#include "RigidBody.h"
#include "Function.h"

RigidBody::RigidBody()
	: Component(COMPONENT_TYPE::RIGIDBODY)
	, m_Mass(1.f)
	, m_InitialSpeed(0.f)
	, m_MaxSpeed(1000.f)
	, m_bGround(false)
	, m_Friction(100.f)
	, m_bPrevMove(false)
	, m_bMove(false)
	, m_GRAVITYACCEL(FloatPoint(0.f, 980.f))
	, m_JumpStack(1)
	, m_MaxJumpStack(3)
{
}

RigidBody::~RigidBody()
{
}

// Foundation Member
/*
private:
	static UINT g_NextID;

private:
	wstring		m_Name;
	const UINT	m_ID;
	*/

// Component Member
//private:
//	Object* m_OWNER;
//	const COMPONENT_TYPE    m_TYPE;

//private:
//	FloatPoint      m_FORCE;        // 방향, 힘의 크기
//	bool            m_Self;         // 힘을 준 주체가 자기자신인지 확인
//
//	FloatPoint      m_VELOCITY;     // 방향, 속력
//	float           m_Mass;         // F = M x A
//	float           m_InitialSpeed; // 초기 이동속력
//	float           m_MaxSpeed;     // 최대 속력 제한
//	float           m_Friction;     // 마찰력 크기
//	FloatPoint      m_JUMPVELOCITY; // 점프 속도   
//
//	bool            m_bPrevMove;    // 이전에 이동중인지 아닌지
//	bool            m_bMove;        // 이동중인지 아닌지
//
//	FloatPoint      m_VELOCITYX;    // 좌,우 방향 속도
//	FloatPoint      m_VELOCITYY;    // 위,아래 방향 속도
//	float           m_MaxGravitySpeed;  // 중력에 의한 최대속도 제한
//	FloatPoint      m_GRAVITYACCEL; // 중력 가속도
//	bool            m_bGround;      // 땅위에 서있는지
//
//	int             m_JumpStack;
//	int             m_MaxJumpStack;
//
//	RIGIDBODY_MODE  m_Mode;         // 동작 모드

void RigidBody::FinalTick()
{
		FinalTick_TopView();

	// Velocity Debug Render
	DrawDebugLine(PEN_COLOR::BLUE, GetOwner()->GetCameraViewPosition(), GetOwner()->GetCameraViewPosition() + m_VELOCITY * 0.3f, 0.f);
}

void RigidBody::FinalTick_TopView()
{
	Object* pObject = GetOwner();

	// F / M == A
	FloatPoint vAccel = m_FORCE / m_Mass;

	// 가속도에 따른 속도의 변화
	m_VELOCITY += vAccel * DELTATIME;

	// 상태 체크
	CheckState();

	// 초기속도 계산
	CalcInitSpeed_TopView();

	// 마찰력에 따른 속도 감소
	CalcFriction_TopView();

	// 최대속력 제한
	CalcMaxSpeed_TopView();

	// 속도에 따른 이동
	FloatPoint vPos = pObject->GetPosition();
	vPos += m_VELOCITY * DELTATIME;
	pObject->SetPosition(vPos);

	// 힘 초기화
	m_FORCE = FloatPoint(0.f, 0.f);
}

void RigidBody::FinalTick_BeltScroll()
{
	Object* pObject = GetOwner();

	// F / M == A
	FloatPoint vAccel = m_FORCE / m_Mass;

	// 가속도에 따른 속도의 변화
	m_VELOCITYX += FloatPoint(vAccel.x * DELTATIME, 0.f);
	m_VELOCITYY += FloatPoint(0.f, vAccel.y * DELTATIME);

	if (m_VELOCITY.Length() != 0.f)
		int a = 0;

	// 상태 체크
	CheckState();

	// 초기속도 계산
	CalcInitSpeed_BeltScroll();

	// 마찰력에 따른 속도 감소
	CalcFriction_BeltScroll();

	// 최대속력 제한
	CalcMaxSpeed_BeltScroll();

	// 중력 가속도 계산	
	if (false == m_bGround) // 공중에 있을 경우
		m_VELOCITYY += m_GRAVITYACCEL * DELTATIME;
	else if (0.f < m_VELOCITYY.y)
	{
		m_VELOCITYY.y = 0.f;
	}

	// 분해된 속도를 합쳐서 최종 속도를 계산한다.
	m_VELOCITY = m_VELOCITYX + m_VELOCITYY;

	// 속도에 따른 이동
	FloatPoint vPos = pObject->GetPosition();
	vPos += m_VELOCITY * DELTATIME;
	pObject->SetPosition(vPos);

	// 초기화
	m_FORCE = FloatPoint(0.f, 0.f);
	m_Self = false;
}

void RigidBody::CheckState()
{
	// 현재 상태를 이전상태로 저장
	m_bPrevMove = m_bMove;

	if (m_VELOCITY.Length() == 0.f && m_FORCE.Length() == 0.f)
		m_bMove = false;
	else
		m_bMove = true;
}

void RigidBody::CalcInitSpeed_TopView()
{
	if (m_bPrevMove == false && m_bMove == true && m_Self)
	{
		FloatPoint vDir = m_VELOCITY;
		vDir.Normalize();
		m_VELOCITY += vDir * m_InitialSpeed;
	}
}

void RigidBody::CalcInitSpeed_BeltScroll()
{
	if (m_bPrevMove == false && m_bMove == true && m_Self)
	{
		FloatPoint vDir = m_VELOCITYX;
		vDir.Normalize();
		m_VELOCITYX += vDir * m_InitialSpeed;
	}
}

void RigidBody::CalcFriction_TopView()
{
	float Speed = m_VELOCITY.Length();

	if (0.f != Speed)
	{
		Speed -= m_Friction * m_Mass * DELTATIME;
		if (Speed < 0.f)
			Speed = 0.f;

		m_VELOCITY.Normalize();
		m_VELOCITY *= Speed;
	}
}

void RigidBody::CalcFriction_BeltScroll()
{
	float Speed = m_VELOCITYX.Length();

	if (0.f != Speed)
	{
		Speed -= m_Friction * m_Mass * DELTATIME;
		if (Speed < 0.f)
			Speed = 0.f;

		m_VELOCITYX.Normalize();
		m_VELOCITYX *= Speed;
	}
}

void RigidBody::CalcMaxSpeed_TopView()
{
	float Speed = m_VELOCITY.Length();

	if (m_MaxSpeed < Speed)
	{
		Speed = m_MaxSpeed;
		m_VELOCITY.Normalize();
		m_VELOCITY *= Speed;
	}
}

void RigidBody::CalcMaxSpeed_BeltScroll()
{
	float Speed = m_VELOCITYX.Length();

	if (m_MaxSpeed < Speed)
	{
		Speed = m_MaxSpeed;
		m_VELOCITYX.Normalize();
		m_VELOCITYX *= Speed;
	}
}

// 모작에 필요없는 기능이라 주석처리
//void RigidBody::Jump()
//{
//	if (m_JumpStack <= 0)
//		return;
//
//	m_VELOCITYY = m_JUMPVELOCITY;
//	m_bGround = false;
//
//	--m_JumpStack;
//}