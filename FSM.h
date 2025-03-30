#pragma once
#include "Component.h"

class State;

// 유한 상태 기계
// Finite State Machine
class FSM :
    public Component
{
/*
private:
    static UINT g_NextID;

private:
    wstring		m_Name;
    const UINT	m_ID;
*/

/*
private:
    Object* m_OWNER;
    const COMPONENT_TYPE    m_TYPE;
*/

private:
    map<wstring, State*>   m_MAPSTATE;
    State* m_CURRENTSTATE;
    State* m_PREVSTATE;

public:
    void AddState(const wstring& _Key, State* _STATE);
    State* FindState(const wstring& _Key);
    void ChangeState(const wstring& _NextState);


public:
    virtual void FinalTick() override;

public:
    FSM();
    ~FSM();
};