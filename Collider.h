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
    FloatPoint        m_OFFSET;   // ��� ��ǥ
    FloatPoint        m_SCALE;    // ũ��
    FloatPoint        m_FINALPOS; // �浹ü�� ���� ��ġ

    bool        m_Active;   // Ȱ��ȭ
    int         m_OverlapCount; // �浹 ���� ��ü�� ����

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
    void BeginOverlap(Collider* _OTHER);   // �ٸ� �浹ü�� ���� �浹 ��
    void Overlap(Collider* _OTHER);        // �ٸ� �浹ü�� BeginOverlap ���Ŀ��� ��� �������� ���
    void EndOverlap(Collider* _OTHER);     // �ٸ� �浹ü�� �����ִٰ� ���ʷ� �������� ����

public:
    virtual void FinalTick() override;
};