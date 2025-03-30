#pragma once
#include "R_UI.h"

class R_PanelUI :
    public R_UI
{
    // UI Member
    /*
    private:
    UI*          m_ParentUI;    // �ڽ��� ������ �θ�UI �� ����Ű�� ������, nullptr �� ��� ������ �ֻ��� �θ� UI ��� ��
    vector<UI*>  m_vecChildUI;  // �����ϰ� �ִ� �ڽ� UI �� ������
    FloatPoint   m_FinalPos;    // ���� ���� ��ġ

    bool         m_MouseHover;  // UI ���� ���콺�� �ö�Դ��� üũ
    bool         m_LBtnDown;    // UI ������ ���콺 ���� ��ư�� ���ȴ��� üũ
    */

private:
    FloatPoint    m_DownPos; // �ڽ��� ���콺 ���� Ŭ�� �Ǿ��� �� ��ǥ ���

public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

    virtual void MouseLBtnDown() override;
    virtual void MouseLBtnClikced() override;

public:
    R_PanelUI();
    ~R_PanelUI();
};