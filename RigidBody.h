#pragma once
#include "Component.h"

class RigidBody :
    public Component
{
private:
    FloatPoint      m_FORCE;        // ����, ���� ũ��
    bool            m_Self;         // ���� �� ��ü�� �ڱ��ڽ����� Ȯ��

    FloatPoint      m_VELOCITY;     // ����, �ӷ�
    float           m_Mass;         // F = M x A
    float           m_InitialSpeed; // �ʱ� �̵��ӷ�
    float           m_MaxSpeed;     // �ִ� �ӷ� ����
    float           m_Friction;     // ������ ũ��
    FloatPoint      m_JUMPVELOCITY; // ���� �ӵ�   

    bool            m_bPrevMove;    // ������ �̵������� �ƴ���
    bool            m_bMove;        // �̵������� �ƴ���

    FloatPoint      m_VELOCITYX;    // ��,�� ���� �ӵ�
    FloatPoint      m_VELOCITYY;    // ��,�Ʒ� ���� �ӵ�
    float           m_MaxGravitySpeed;  // �߷¿� ���� �ִ�ӵ� ����
    FloatPoint      m_GRAVITYACCEL; // �߷� ���ӵ�
    bool            m_bGround;      // ������ ���ִ���

    int             m_JumpStack;
    int             m_MaxJumpStack;

public:
    FloatPoint GetForce()
    {
        return m_FORCE;
    }
    void AddForce(FloatPoint _Force, bool _Self = false)
    {
        m_FORCE += _Force; m_Self = _Self;
    }

    float GetMass()
    {
        return m_Mass;
    }
    
    void SetMass(float _Mass)
    {
        m_Mass = _Mass;
    }

    float GetMaxSpeed()
    {
        return m_MaxSpeed;
    }
    
    void SetMaxSpeed(float _Speed)
    {
        m_MaxSpeed = _Speed;
    }

    float GetFriction()
    {
        return m_Friction;
    }
    
    void SetFriction(float _Friction)
    {
        m_Friction = _Friction;
    }

    float GetInitialSpeed()
    {
        return m_InitialSpeed;
    }
    
    void SetInitialSpeed(float _Init)
    {
        m_InitialSpeed = _Init;
    }

    void SetVelocity(FloatPoint _Velocity)
    {
        m_VELOCITY = _Velocity;
    }
    
    void AddVelocity(FloatPoint _Velocity)
    {
        m_VELOCITY += _Velocity;
    }

    void SetGravityAccel(FloatPoint _GravityAccel)
    {
        m_GRAVITYACCEL = _GravityAccel;
    }
    
    FloatPoint GetGravityAccel()
    {
        return m_GRAVITYACCEL;
    }

    bool IsGround() { return m_bGround; }
    void SetGround(bool _Ground) {
        m_bGround = _Ground;

        if (m_bGround)
        {
            m_JumpStack = m_MaxJumpStack;
        }
    }

    void SetJumpVelocity(FloatPoint _Veloticy)
    {
        m_JUMPVELOCITY = _Veloticy;
    }

    void Jump();

public:
    virtual void FinalTick() override;

private:
    void FinalTick_TopView();
    void FinalTick_BeltScroll();

    void CheckState();

    void CalcInitSpeed_TopView();
    void CalcInitSpeed_BeltScroll();

    void CalcFriction_TopView();
    void CalcFriction_BeltScroll();

    void CalcMaxSpeed_TopView();
    void CalcMaxSpeed_BeltScroll();

public:
    RigidBody();
    ~RigidBody();
};