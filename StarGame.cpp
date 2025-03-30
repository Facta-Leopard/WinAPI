#include "PreCompile.h"
#include "InGameStage.h"
#include "Player_Unit.h"

#include "CameraMGR.h"

// 전역 변수:

// 현재 인스턴스
HINSTANCE hInst;

// 현재 해상도
extern FloatPoint RESOLUTIONSCALE(640, 480);
extern POINT RESOLUTION = { (int)RESOLUTIONSCALE.x, (int)RESOLUTIONSCALE.y };


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(HINSTANCE hInstance,
                      HINSTANCE hPrevInstance,
                      LPWSTR    lpCmdLine,
                      int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    hInst = hInstance; // 프로세스 시작 주소

    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DOPPLESTARICON));
 /*   wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);*/
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    // 메뉴 보이게 하고 안 보이게 하고
    // SetMenu()를 이용해서 조절하자..
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINAPI);
    wcex.lpszClassName = L"Key";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    RegisterClassExW(&wcex);

    // Engine 초기화
    if (FAILED(GameEngine::GetInstance()->Init(hInst, RESOLUTION)))
        return FALSE;

    // 단축키 테이블 
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI));

    // 메시지 변수
    MSG msg = {};

    while (true)
    {
        // 메세지큐에 메세지가 있는지 확인
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

    // 메세지 처리
    if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// 메세지큐에 메세지가 없다.
        else
        {
            // 게임 실행
            GameEngine::GetInstance()->Tick();
        }
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
            // 글자관련 - 켜기
        case IDM_Text_On:
        {
            Stage* tStage = dynamic_cast<InGameStage*>(StageMGR::GetInstance()->GetCurrentStage());

            if (tStage)
            {
                vector<Object*> tVECTOR = tStage->GetObjects(LAYER_TYPE::PLAYER1);

                for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
                {
                    dynamic_cast<Player_Unit*>(*iter)->SetOnText();
                }

                vector<Object*> tVECTOR2 = tStage->GetObjects(LAYER_TYPE::PLAYER2);

                for (vector<Object*>::iterator iter = tVECTOR2.begin(); iter != tVECTOR2.end(); iter++)
                {
                    dynamic_cast<Player_Unit*>(*iter)->SetOnText();
                }
            }
        }
            break;

            // 글자관련 - 끄기
        case IDM_Text_Off:
        {
            Stage* tStage = dynamic_cast<InGameStage*>(StageMGR::GetInstance()->GetCurrentStage());

            if (tStage)
            {
                vector<Object*> tVECTOR = tStage->GetObjects(LAYER_TYPE::PLAYER1);

                for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
                {
                    dynamic_cast<Player_Unit*>(*iter)->SetOffText();
                }

                vector<Object*> tVECTOR2 = tStage->GetObjects(LAYER_TYPE::PLAYER2);

                for (vector<Object*>::iterator iter = tVECTOR2.begin(); iter != tVECTOR2.end(); iter++)
                {
                    dynamic_cast<Player_Unit*>(*iter)->SetOffText();
                }
            }
        }
            break;

        case IDM_DEBUG_ON:
        {
            InGameStage* tStage = dynamic_cast<InGameStage*>(StageMGR::GetInstance()->GetCurrentStage());
            if (tStage)
            {
                tStage->SetOnDebugging();
            }
        }
            break;

        case IDM_DEBUG_OFF:
        {
            InGameStage* tStage = dynamic_cast<InGameStage*>(StageMGR::GetInstance()->GetCurrentStage());
            if (tStage)
            {
                tStage->SetOffDebugging();
            }
        }
            break;

            // 화면관련 - 고정하기
        case IDM_Screen_Fix:
            CameraMGR::GetInstance()->SetOffScreenMoveable();
            break;

            // 화면관련 - 고정풀기
        case IDM_Screen_Release:
            CameraMGR::GetInstance()->SetOnScreenMoveable();
            break;

            // 실행관련 - 타이틀화면
        case IDM_To_MainStage:
            StageMGR::GetInstance()->ChangeStage(STAGE_TYPE::TITLE);
            TimeMGR::GetInstance()->SetOffTimeStop();
            //GameEngine::GetInstance()->ChangeWindowSize(RESOLUTION);
            //InvalidateRect(GameEngine::GetInstance()->GetMainWndHwnd(), NULL, true);
            break;

            // 실행관련 - 종료하기
        case IDM_Exit_Game:
            PostMessage(GameEngine::GetInstance()->GetMainWndHwnd(), WM_CLOSE, 0, 0);
            break;
        // 
        //case IDM_ABOUT:
        //    // Modal
        //    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, &About);
        //    break;
        //case IDM_DeInit:
        //    DestroyWindow(hWnd);
        //    break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_MOUSEMOVE:
    {
        int a = 0;
    }
    break;
    case WM_SIZE:

        break;

    case WM_SIZING:

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}