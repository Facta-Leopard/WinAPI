#pragma once
#include "PreCompile.h"
#include "R_UI.h"

class R_ButtonUI :
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
    PARAM_0             m_Func;

    // Delegate
    Foundation*         m_Inst;
    DELEGATE_0          m_MemFunc;

public:
    void AddCallBack(PARAM_0 _Func) { m_Func = _Func; }
    void AddDelegate(Foundation* _Inst, DELEGATE_0 _memFunc) { m_Inst = _Inst; m_MemFunc = _memFunc; }

public:
    virtual void Tick_UI() override;
    virtual void Render_UI() override;

    // Mouse Click
    virtual void MouseLBtnClikced() override;

public:
    R_ButtonUI();
    ~R_ButtonUI();
};