#pragma once

#include "StarUnit.h"
#include "Texture.h"

class Player1_Building :
    public StarUnit
{
    Player1_Building(wstring _wString, UNIT_TYPE m_UNITTYPE, float _duration = 8.f);
    ~Player1_Building();

    // Foundation Member

/* private:
    static UINT g_NextID;

private:
    wstring		m_Name;
    const UINT	m_ID;
*/

// Object Member

/* private:
    FloatPoint           m_POSITION;
    FloatPoint           m_PREVIOUSPOSTION;
    FloatPoint           m_SCALE;
    vector<Component*>   m_COMPONENT;
    LAYER_TYPE           m_LAYERTYPE;
    bool                 m_Dead;         // ���� ����
*/

protected:

    bool                m_ClickSoundable;

    // ����, ������ Ŭ�� ���� ����� ��ӹ��� Ŭ�������� ��������
    bool                m_IsMouseover;
    bool                m_WasMouseover;
    bool                m_IsLeftButtonClick;
    bool                m_WasLeftButtonClick;


    // StarUnit Ŭ������ �ֿ�κ�
    //Texture* m_TEXTURE;

    //// �������Լ��� ���� ��� ���� �߱�
    //std::function<void(LAYER_TYPE)> m_Trigger_PointerFunction;

    //// �������Լ��� ���� ��� ���� �߱�(����)
    //std::function<void(UNIT_TYPE)> m_Sound_PointerFunction;

public:
    virtual void Init() override;
    virtual void Tick() override;
    virtual void Render() override;

    virtual void MouseoverCheck() override;
    virtual void MouseClickCheck() override;

    // �������Լ��� ���� ��� ����
    // Ʈ���ſ� ������ �Լ�
    virtual void SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction);

    // ���� ����� ������ �Լ�
    virtual void SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction);
};