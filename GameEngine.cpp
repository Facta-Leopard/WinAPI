#include "PreCompile.h"
#include "GameEngine.h"

#include "StageMGR.h"
#include "DBGRenderMGR.h"
#include "ColliderMGR.h"
#include "UIMGR.h"
#include "CameraMGR.h"
#include "PortraitMGR.h"

GameEngine::GameEngine()
    : m_HandleInstance(nullptr)
    , m_Handle(nullptr)
    , m_Resolution{}
    , m_HANDLEDC(nullptr)
    , m_BackBuffer(nullptr)
    , m_PEN{}
    , m_Brush{}
{
}

GameEngine::~GameEngine()
{
    // DC ����
    ReleaseDC(m_Handle, m_HANDLEDC);

    // Pen �� Brush ����
    for (UINT i = 0; i < (UINT)PEN_COLOR::EOL; ++i)
    {
        DeleteObject(m_PEN[i]);
    }

    for (UINT i = 0; i < (UINT)BRUSH_COLOR::EOL; ++i)
    {
        if (BRUSH_COLOR::HOLLOW == (BRUSH_COLOR)i)
            continue;

        DeleteObject(m_Brush[i]);
    }
}

int GameEngine::Init(HINSTANCE _HandleInstance, POINT _Resolution)
{
    m_HandleInstance = _HandleInstance;
    m_Resolution = _Resolution;

    // HWND ������ ID Ÿ��
    // Ŀ�� ������Ʈ ( OS �������� �����Ǵ� ��ü )
    m_Handle = CreateWindowW(L"Key", L"MyGame"
                            , (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX)
                            , CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_HandleInstance, nullptr);

    if (!m_Handle)
        return E_FAIL;

    ShowWindow(m_Handle, true);
    UpdateWindow(m_Handle);

    // ������ ũ�⸦ �ػ󵵿� �°� ����
    ChangeWindowSize(m_Resolution);

    // DC ����   
    m_HANDLEDC = GetDC(m_Handle);

    // GDIObject ����
    CreateGDIObject();

    // Manager ���� �� �ʱ�ȭ
    PathMGR::Init();
    SoundMGR::GetInstance()->Init();
    TimeMGR::GetInstance()->Init();
    KeyMGR::GetInstance()->Init();
    AssetMGR::GetInstance()->Init();
    StageMGR::GetInstance()->Init();
    CameraMGR::GetInstance()->Init();
    PortraitMGR::GetInstance()->Init();


    // ������۸��� ���� �߰����� ����
    CreateSecondBuffer();


    return S_OK;
}

void GameEngine::CreateGDIObject()
{
    // Pen
    m_PEN[(UINT)PEN_COLOR::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    m_PEN[(UINT)PEN_COLOR::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    m_PEN[(UINT)PEN_COLOR::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    m_PEN[(UINT)PEN_COLOR::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
    m_PEN[(UINT)PEN_COLOR::GRAY] = CreatePen(PS_SOLID, 1, RGB(120, 120, 120));


    // Brush
    m_Brush[(UINT)BRUSH_COLOR::RED] = CreateSolidBrush(RGB(255, 0, 0));
    m_Brush[(UINT)BRUSH_COLOR::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
    m_Brush[(UINT)BRUSH_COLOR::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
    m_Brush[(UINT)BRUSH_COLOR::GRAY] = CreateSolidBrush(RGB(90, 90, 90));
    m_Brush[(UINT)BRUSH_COLOR::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
}

void GameEngine::Tick()
{
    // Manager Tick
    TimeMGR::GetInstance()->Tick(); // DELTATIME ���
    KeyMGR::GetInstance()->Tick();  // �� Ű�� ����
    CameraMGR::GetInstance()->Tick();

    DBGRenderMGR::GetInstance()->Tick();

    // �������� ����
    StageMGR::GetInstance()->Tick();

    // �浹 �˻� ����
    ColliderMGR::GetInstance()->Tick();

    // UI �Ŵ��� üũ
    UIMGR::GetInstance()->Tick();


    // ������
    // ȭ�� Ŭ����
    {
        SELECT_BRUSH(BRUSH_COLOR::GRAY);
        Rectangle(m_BackBuffer->GetDC(), -1, -1, (int)m_Resolution.x + 1, (int)m_Resolution.y + 1);
    }

    // �������� ������
    StageMGR::GetInstance()->Render();

    // Camera ������
    CameraMGR::GetInstance()->Render();

    // ����� ���� ������
    DBGRenderMGR::GetInstance()->Render();

    // SecondBitmap �ִ� ����� MainWindowBitmap ���� �����ؿ´�.
    BitBlt(m_HANDLEDC, 0, 0, (int)m_Resolution.x, (int)m_Resolution.y
        , m_BackBuffer->GetDC(), 0, 0, SRCCOPY);

    // TaskMGR ����
    TaskMGR::GetInstance()->Tick();
}

void GameEngine::ChangeWindowSize(POINT _Resolution)
{
    m_Resolution = _Resolution;

    RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };

    // ���������찡 Menu �� �ִ��� Ȯ��
    HMENU hMenu = GetMenu(m_Handle);

    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!hMenu);

    //if (StageMGR::GetInstance()->GetCurrentStage())
    //{
    //    GetWindowRect(GameEngine::GetInstance()->GetMainWndHwnd(), &rt);

    //    // ��.. �̷� �ϴ� �ڲ� ���� �ö󰡳�..
    //    //AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, !!hMenu);

    //    //// ¥�����ϱ� �׳� �޴�ũ�� ��ü�� ���ص� �ȵ�..
    //    //int menuHeight = GetSystemMetrics(SM_CYMENU);

    //    //SetWindowPos(m_Handle, nullptr, rt.left, rt.top, m_Resolution.x, m_Resolution.y, 0);
    //    SetWindowPos(m_Handle, nullptr, rt.left, rt.top, 640, 480, 0);
    //}
    //else
    RECT tRT = {};
    GetWindowRect(GameEngine::GetInstance()->GetMainWndHwnd(), &tRT);
    SetWindowPos(m_Handle, nullptr, tRT.left, tRT.top, rt.right - rt.left, rt.bottom - rt.top, 0);
    

}

void GameEngine::CreateSecondBuffer()
{
    m_BackBuffer = AssetMGR::GetInstance()->CreateTexture(L"BackBuffer", (int)m_Resolution.x, (int)m_Resolution.y);
}