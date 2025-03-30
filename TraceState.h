#pragma once
#include "State.h"

class TraceState :
    public State
{
private:
    Object* m_TargetObject;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void DeInit() override;

public:
    TraceState();
    ~TraceState();
};