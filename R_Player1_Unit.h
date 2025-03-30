#pragma once
#include "R_Player1Building.h"

class Player1Unit :
    public Player1Building
{
public:
    Player1Unit();
    ~Player1Unit();

private:
    Object* m_Target;       // ���� ���
    float   m_DetectRange;  // ���� ����

public:
    void SetDetectRange(float _Range) { m_DetectRange = _Range; }

public:
    virtual void Tick() override;
    virtual void BeginOverlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER) override;

private:
    void FindTarget();
    void TraceTarget_0();
    void TraceTarget_1();
    void TraceTarget_2();
};