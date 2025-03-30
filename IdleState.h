#pragma once
#include "State.h"

class IdleState :
    public State
{
private:
    Object* m_TARGETOBJECT;

public:
    virtual void Enter() override;
    virtual void FinalTick() override;
    virtual void DeInit() override;

public:
    IdleState();
    ~IdleState();
};