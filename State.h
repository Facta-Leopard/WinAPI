#pragma once
#include "Foundation.h"
#include "FSM.h"

class Object;

class State :
    public Foundation
{
private:
    class FSM* m_OWNER;

public:
    FSM* GetFSM()
    {
        return m_OWNER;
    }
    
    Object* GetOwnerObject()
    {
        return m_OWNER->GetOwner();
    }

public:
    virtual void Enter() = 0;
    virtual void FinalTick() = 0;
    virtual void DeInit() = 0;

public:
    State();
    ~State();

    friend class FSM;
};