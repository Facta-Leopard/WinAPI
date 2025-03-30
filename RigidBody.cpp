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
//	FloatPoint      m_FORCE;        // ����, ���� ũ��
//	bool            m_Self;         // ���� �� ��ü�� �ڱ��ڽ����� Ȯ��
//
//	FloatPoint      m_VELOCITY;     // ����, �ӷ�
//	float           m_Mass;         // F = M x A
//	float           m_InitialSpeed; // �ʱ� �̵��ӷ�
//	float           m_MaxSpeed;     // �ִ� �ӷ� ����
//	float           m_Friction;     // ������ ũ��
//	FloatPoint      m_JUMPVELOCITY; // ���� �ӵ�   
//
//	bool            m_bPrevMove;    // ������ �̵������� �ƴ���
//	bool            m_bMove;        // �̵������� �ƴ���
//
//	FloatPoint      m_VELOCITYX;    // ��,�� ���� �ӵ�
//	FloatPoint      m_VELOCITYY;    // ��,�Ʒ� ���� �ӵ�
//	float           m_MaxGravitySpeed;  // �߷¿� ���� �ִ�ӵ� ����
//	FloatPoint      m_GRAVITYACCEL; // �߷� ���ӵ�
//	bool            m_bGround;      // ������ ���ִ���
//
//	int             m_JumpStack;
//	int             m_MaxJumpStack;
//
//	RIGIDBODY_MODE  m_Mode;         // ���� ���

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

	// ���ӵ��� ���� �ӵ��� ��ȭ
	m_VELOCITY += vAccel * DELTATIME;

	// ���� üũ
	CheckState();

	// �ʱ�ӵ� ���
	CalcInitSpeed_TopView();

	// �����¿� ���� �ӵ� ����
	CalcFriction_TopView();

	// �ִ�ӷ� ����
	CalcMaxSpeed_TopView();

	// �ӵ��� ���� �̵�
	FloatPoint vPos = pObject->GetPosition();
	vPos += m_VELOCITY * DELTATIME;
	pObject->SetPosition(vPos);

	// �� �ʱ�ȭ
	m_FORCE = FloatPoint(0.f, 0.f);
}

void RigidBody::FinalTick_BeltScroll()
{
	Object* pObject = GetOwner();

	// F / M == A
	FloatPoint vAccel = m_FORCE / m_Mass;

	// ���ӵ��� ���� �ӵ��� ��ȭ
	m_VELOCITYX += FloatPoint(vAccel.x * DELTATIME, 0.f);
	m_VELOCITYY += FloatPoint(0.f, vAccel.y * DELTATIME);

	if (m_VELOCITY.Length() != 0.f)
		int a = 0;

	// ���� üũ
	CheckState();

	// �ʱ�ӵ� ���
	CalcInitSpeed_BeltScroll();

	// �����¿� ���� �ӵ� ����
	CalcFriction_BeltScroll();

	// �ִ�ӷ� ����
	CalcMaxSpeed_BeltScroll();

	// �߷� ���ӵ� ���	
	if (false == m_bGround) // ���߿� ���� ���
		m_VELOCITYY += m_GRAVITYACCEL * DELTATIME;
	else if (0.f < m_VELOCITYY.y)
	{
		m_VELOCITYY.y = 0.f;
	}

	// ���ص� �ӵ��� ���ļ� ���� �ӵ��� ����Ѵ�.
	m_VELOCITY = m_VELOCITYX + m_VELOCITYY;

	// �ӵ��� ���� �̵�
	FloatPoint vPos = pObject->GetPosition();
	vPos += m_VELOCITY * DELTATIME;
	pObject->SetPosition(vPos);

	// �ʱ�ȭ
	m_FORCE = FloatPoint(0.f, 0.f);
	m_Self = false;
}

void RigidBody::CheckState()
{
	// ���� ���¸� �������·� ����
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

// ���ۿ� �ʿ���� ����̶� �ּ�ó��
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