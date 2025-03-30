#pragma once
#include "Object.h"

class R_Obstruction :
    public Object
{
private:
    class Collider* m_COLLIDER;

public:
    virtual void Tick() override;
    virtual void BeginOverlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER);
    virtual void Overlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER);
    virtual void EndOverlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER);


public:
    R_Obstruction();
    ~R_Obstruction();
};