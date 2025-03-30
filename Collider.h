#pragma once
#include "PreCompile.h"
#include "Component.h"

class Collider :
    public Component
{
public:
    Collider();
    ~Collider();

private:
    FloatPoint        m_OFFSET;   // 상대 좌표
    FloatPoint        m_SCALE;    // 크기
    FloatPoint        m_FINALPOS; // 충돌체의 실제 위치

    bool        m_Active;   // 활성화
    int         m_OverlapCount; // 충돌 중인 물체의 숫자

public:
    void SetScale(FloatPoint _SCALE)
    {
        m_SCALE = _SCALE;
    }

    FloatPoint GetScale()
    {
        return m_SCALE;
    }

    void SetOffset(FloatPoint _OFFSET)
    {
        m_OFFSET = _OFFSET;
    }
    
    FloatPoint GetOffset()
    {
        return m_OFFSET;
    }

    FloatPoint GetFinalPos()
    {
        return m_FINALPOS;
    }

public:
    void BeginOverlap(Collider* _OTHER);   // 다른 충돌체와 최초 충돌 시
    void Overlap(Collider* _OTHER);        // 다른 충돌체와 BeginOverlap 이후에도 계속 겹쳐있을 경우
    void EndOverlap(Collider* _OTHER);     // 다른 충돌체와 겹쳐있다가 최초로 떨어지는 순간

public:
    virtual void FinalTick() override;
};