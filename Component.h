#pragma once
#include "Foundation.h"

class Object;

class Component :
    public Foundation
{
    // Foundation Member
/*
private:
	static UINT g_NextID;

private:
	wstring		m_Name;
	const UINT	m_ID;
    */

private:
    Object* m_OWNER;
    const COMPONENT_TYPE    m_TYPE;

public:
    COMPONENT_TYPE GetType()
    {
        return m_TYPE;
    }
    
    Object* GetOwner()
    {
        return m_OWNER;
    }

    void SetOwner(Object* _pOBEJECT)
    {
        m_OWNER = _pOBEJECT;
    }

public:
    virtual void FinalTick() = 0;

public:
    Component(COMPONENT_TYPE _TYPE);
    ~Component();

    friend class Object;
};