#pragma once

#include "StarUnit.h"
#include "Texture.h"

#include <functional>

class MenuUI :
    public StarUnit
{
public:
    MenuUI(wstring _wString, float _duration = 5.f);
    ~MenuUI();

protected:
    bool                m_ClickSoundable;
    bool                m_MouseoverSoundable;

    // ����, ������ Ŭ�� ���� ����� ��ӹ��� Ŭ�������� ��������
    bool                m_IsMouseover;
    bool                m_WasMouseover;
    bool                m_IsLeftButtonClick;
    bool                m_WasLeftButtonClick;

    Texture*            m_TEXTURE;

    float               m_Index;
    int                 m_MaxFrame;

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
    virtual void PlaySound();

    virtual void MouseoverCheck() override;
    virtual void MouseClickCheck() override;


    virtual void SetOnText();
    virtual void SetOffText();


    // �������Լ��� ���� ��� ����
    // �׽�Ʈ��
    virtual void SetTriggerPointerFunction(std::function<void(LAYER_TYPE)> PointFunction);

    // 
    virtual void SetSoundPointerFunction(std::function<void(UNIT_TYPE)> PointFunction);
};