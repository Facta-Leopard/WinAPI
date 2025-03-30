#pragma once
#include "PreCompile.h"
#include "R_UI.h"

class R_ButtonUI :
    public R_UI
{
    // UI Member
/*
private:
UI*          m_ParentUI;    // 자신을 소유한 부모UI 를 가리키는 포인터, nullptr 인 경우 본인이 최상위 부모 UI 라는 뜻
vector<UI*>  m_vecChildUI;  // 소유하고 있는 자식 UI 들 포인터
FloatPoint   m_FinalPos;    // 최종 계산된 위치

bool         m_MouseHover;  // UI 위에 마우스가 올라왔는지 체크
bool         m_LBtnDown;    // UI 위에서 마우스 왼쪽 버튼이 눌렸는지 체크
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