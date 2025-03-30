#pragma once
#include "PreCompile.h"
#include "Foundation.h"

class Component;
class Collider;

class Object :
    public Foundation
{
public:
    Object();
    virtual ~Object();

    friend class Stage;
    friend class TaskMGR;

// Foundation Member
/* private:
    static UINT g_NextID;

private:
    wstring		m_Name;
    const UINT	m_ID; */

protected:
    FloatPoint           m_POSITION;
    FloatPoint           m_PREVIOUSPOSTION;
    FloatPoint           m_SCALE;
    //vector<Component*>   m_COMPONENT;
    LAYER_TYPE           m_LAYERTYPE;
    bool                 m_Dead;         // 삭제 예정

public:
    virtual void Init();               // 스테이지 시작할 때
    virtual void Tick() = 0;            // 오브젝트가 할 일
    virtual void FinalTick();     // 오브젝트가 소유한 Component 가 할 일
    virtual void Render();              // 오브젝트를 그리기

    virtual void BeginOverlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER)
    {
    }
    
    virtual void Overlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER)
    {
    }
    
    virtual void EndOverlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER)
    {
    }

public:
    void SetPosition(FloatPoint _POS)
    {
        m_POSITION = _POS;
    }

    virtual void SetPosition(float _x, float _y)
    {
        m_POSITION = FloatPoint(_x, _y);
    }
    
    void SetScale(FloatPoint _SCALE)
    {
        m_SCALE = _SCALE; }
    
    void SetScale(float _x, float _y)
    {
        m_SCALE = FloatPoint(_x, _y);
    }

    FloatPoint GetPosition()
    {
       return m_POSITION;
    }
    
    FloatPoint GetCameraViewPosition();

    FloatPoint GetIngameViewPosition();
    
    FloatPoint GetScale()
    {
        return m_SCALE;
    }
    
    LAYER_TYPE GetLayerType()
    {
        return m_LAYERTYPE;
    }

    bool IsDead() { return m_Dead; }

    //Component* AddComponent(Component* _Component);

    //Component* GetComponent(const wstring& _Name);
    //Component* GetComponent(COMPONENT_TYPE _TYPE);

    //template<typename T>
    //T* GetComponent();
};

//template<typename T>
//T* Object::GetComponent()
//{
//    for (size_t i = 0; i < m_COMPONENT.size(); ++i)
//    {
//        if (dynamic_cast<T*>(m_COMPONENT[i]))
//        {
//            return (T*)m_COMPONENT[i];
//        }
//    }
//
//    return nullptr;
//}
