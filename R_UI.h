#pragma once
#include "Object.h"

typedef void (*PARAM_0)(void);
typedef void (*PARAM_1)(DWORD_PTR);


typedef void(Foundation::* DELEGATE_0)(void);
typedef void(Foundation::* DELEGATE_1)(DWORD_PTR);
typedef void(Foundation::* DELEGATE_2)(DWORD_PTR, DWORD_PTR);


class R_UI :
    public Object
{

    friend class UIMGR;

public:
    R_UI();
    ~R_UI();

private:
    R_UI*          m_ParentUI;    // �ڽ��� ������ �θ�UI �� ����Ű�� ������, nullptr �� ��� ������ �ֻ��� �θ� UI ��� ��
    vector<R_UI*>  m_vecChildUI;  // �����ϰ� �ִ� �ڽ� UI �� ������
    FloatPoint   m_FINALPOS;    // ���� ���� ��ġ

    bool         m_MouseHover;  // UI ���� ���콺�� �ö�Դ��� üũ
    bool         m_LBtnDown;    // UI ������ ���콺 ���� ��ư�� ���ȴ��� üũ

public:
    bool IsMouseHover()
    {
        return m_MouseHover;
    }

    bool IsLBtnDown()
    {
        return m_LBtnDown;
    }

    FloatPoint GetFinalPos()
    {
        return m_FINALPOS;
    }

    void AddChildUI(R_UI* _ChildUI)
    {
        m_vecChildUI.push_back(_ChildUI);
        _ChildUI->m_ParentUI = this;
    }

public:
    virtual void Tick() override;
    virtual void Tick_UI() = 0;

    virtual void Render() override;
    virtual void Render_UI();

protected:
    virtual void MouseoverCheck();

    // ���콺 ���� ��ư�� ������ ��
    virtual void MouseLBtnDown() {}

    // �ش� UI �� ���Ȱ�, �ٽ� UI ������ ��ư�� ������ �� Ŭ������ �����Ѵ�.
    virtual void MouseLBtnClikced() {}

    // �ش� UI �� ������ �ʾ�����, UI ������ ��ư�� ������ ��, Drag Drop �� �� Ȱ��
    virtual void MouseReleased() {}
};