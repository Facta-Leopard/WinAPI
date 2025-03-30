#pragma once
#include "Component.h"

class RigidBody :
    public Component
{
private:
    FloatPoint      m_FORCE;        // 방향, 힘의 크기
    bool            m_Self;         // 힘을 준 주체가 자기자신인지 확인

    FloatPoint      m_VELOCITY;     // 방향, 속력
    float           m_Mass;         // F = M x A
    float           m_InitialSpeed; // 초기 이동속력
    float           m_MaxSpeed;     // 최대 속력 제한
    float           m_Friction;     // 마찰력 크기
    FloatPoint      m_JUMPVELOCITY; // 점프 속도   

    bool            m_bPrevMove;    // 이전에 이동중인지 아닌지
    bool            m_bMove;        // 이동중인지 아닌지

    FloatPoint      m_VELOCITYX;    // 좌,우 방향 속도
    FloatPoint      m_VELOCITYY;    // 위,아래 방향 속도
    float           m_MaxGravitySpeed;  // 중력에 의한 최대속도 제한
    FloatPoint      m_GRAVITYACCEL; // 중력 가속도
    bool            m_bGround;      // 땅위에 서있는지

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