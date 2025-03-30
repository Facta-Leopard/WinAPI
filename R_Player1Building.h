#pragma once
#include "Object.h"
#include "MovingMotion.h"

#include "RigidBody.h"

class R_Player1Building :
    public Object
{
public:
    R_Player1Building(wstring _Name);
    ~R_Player1Building();

    // Foundation Member
/* private:
    static UINT g_NextID;

private:
    wstring		m_Name;
    const UINT	m_ID; */

    // Object Member
//private:
//    FloatPoint           m_POSITION;
//    FloatPoint           m_PREVIOUSPOSTION;
//    FloatPoint           m_SCALE;
//    vector<Component*>   m_COMPONENT;
//    LAYER_TYPE           m_LAYERTYPE;
//    bool                 m_Dead;         // 삭제 예정

protected:
    RigidBody*              m_RIGIDBODY;
    Collider*               m_COLLISION;

public:
    FloatPoint              m_VELOCITY;
    float                   m_VelocityScale;

    float                   m_IsHitPoint;

    Collider*               m_COLLIDER;
    float                   m_Mass;     // 질량

    FloatPoint              m_Force;    // 크기
    float                   m_Direction;// 방향

    vector<MovingMotion>   m_VECTOR_MOVINGMOTION;

    bool                    m_OrderMove;
    bool                    m_OrderAttack;

public:
    void AddForce(FloatPoint _Force) { m_Force += _Force; }

public:
    virtual void Tick() override;
    virtual void Render() override;
};