#include "PreCompile.h"
#include "GameEngine.h"

#include "CameraMGR.h"

// 키 값 배열
UINT KeyValue[KEY::KEY_END] = 
{
    // 알파벳 키 (A ~ Z)
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  // Q ~ P
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',        // A ~ L
    'Z', 'X', 'C', 'V', 'B', 'N', 'M',                  // Z ~ M

    // 숫자 키 (0 ~ 9)
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',    // 숫자 0 ~ 9

    // 특수 문자 키 (일반적으로 키보드 상의 기호들)
    VK_OEM_1,    // ; : (semi-colon)
    VK_OEM_2,    // / ? (forward slash)
    VK_OEM_3,    // ` ~ (grave accent)
    VK_OEM_4,    // [ { (left bracket)
    VK_OEM_5,    // \ | (backslash)
    VK_OEM_6,    // ] } (right bracket)
    VK_OEM_7,    // ' " (single quote)

	VK_OEM_PLUS,   // + (plus key)
	VK_OEM_COMMA, // , < (comma)
    VK_OEM_PERIOD, // . > (period)
    VK_OEM_MINUS, // - _ (minus)

    // 기능 키 (F1 ~ F12)
    VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,  // F1 ~ F12

    // 제어 키
    VK_RETURN,    // Enter
    VK_ESCAPE,    // Escape
    VK_TAB,       // Tab
    VK_SPACE,     // Space
    VK_BACK,      // Backspace
    VK_SHIFT,     // Shift
    VK_CONTROL,   // Control
    VK_MENU,      // Alt

    VK_CAPITAL,   // Caps Lock
    VK_NUMLOCK,   // Num Lock
    VK_SCROLL,    // Scroll Lock

    // 방향키 (Up, Down, Left, Right)
    VK_UP,        // 위쪽 방향키 (Up Arrow)
    VK_DOWN,      // 아래쪽 방향키 (Down Arrow)
    VK_LEFT,      // 왼쪽 방향키 (Left Arrow)
    VK_RIGHT,     // 오른쪽 방향키 (Right Arrow)

    // 숫자패드 키 (Numpad 0 ~ Numpad 9)
    VK_NUMPAD0,   // Numpad 0
    VK_NUMPAD1,   // Numpad 1
    VK_NUMPAD2,   // Numpad 2
    VK_NUMPAD3,   // Numpad 3
    VK_NUMPAD4,   // Numpad 4
    VK_NUMPAD5,   // Numpad 5
    VK_NUMPAD6,   // Numpad 6
    VK_NUMPAD7,   // Numpad 7
    VK_NUMPAD8,   // Numpad 8
    VK_NUMPAD9,   // Numpad 9

    // 숫자패드 연산자 키
    VK_ADD,       // Numpad +
    VK_SUBTRACT,  // Numpad -
    VK_MULTIPLY,  // Numpad *
    VK_DIVIDE,    // Numpad /
    VK_DECIMAL,   // Numpad . (Decimal point)

    // 마우스 버튼 (왼쪽, 오른쪽, 가운데)
    VK_LBUTTON,   // 왼쪽 마우스 버튼 (Left Mouse Button)
    VK_RBUTTON,   // 오른쪽 마우스 버튼 (Right Mouse Button)

    //VK_MBUTTON,   // 가운데 마우스 버튼 (Middle Mouse Button)

    // 기타 키들
    VK_LSHIFT,    // 왼쪽 Shift 키
    VK_RSHIFT,    // 오른쪽 Shift 키
    VK_LCONTROL,  // 왼쪽 Control 키
    VK_RCONTROL,  // 오른쪽 Control 키
    VK_LMENU,     // 왼쪽 Alt 키 (Left Alt)
    VK_RMENU,     // 오른쪽 Alt 키 (Right Alt)
};


KeyMGR::KeyMGR()
	: m_CURSORSTATE(STARCRAFT_CURSOR)
	, m_DragAndDropBox{ {0, 0},{0, 0} }
{
	// 커서 파일 로드
	wstring tPath = CONTENTS_PATH;

	tPath += L"Cursor\\StarcraftCursor.ani";
	m_HANDLECURSOR.push_back(LoadCursorFromFile(tPath.c_str()));
	tPath = CONTENTS_PATH;

	tPath += L"Cursor\\StarcraftWorking.ani";
	m_HANDLECURSOR.push_back(LoadCursorFromFile(tPath.c_str()));
	tPath = CONTENTS_PATH;

	tPath += L"Cursor\\StarcraftCursor_Red.ani";
	m_HANDLECURSOR.push_back(LoadCursorFromFile(tPath.c_str()));
	tPath = CONTENTS_PATH;

	tPath += L"Cursor\\StarcraftAlternate.ani";
	m_HANDLECURSOR.push_back(LoadCursorFromFile(tPath.c_str()));
	tPath = CONTENTS_PATH;

	tPath += L"Cursor\\StarcraftEW.ani";
	m_HANDLECURSOR.push_back(LoadCursorFromFile(tPath.c_str()));
	tPath = CONTENTS_PATH;

	tPath += L"Cursor\\StarcraftNS.ani";
	m_HANDLECURSOR.push_back(LoadCursorFromFile(tPath.c_str()));
	tPath = CONTENTS_PATH;

	tPath += L"Cursor\\StarcraftNESW.ani";
	m_HANDLECURSOR.push_back(LoadCursorFromFile(tPath.c_str()));
	tPath = CONTENTS_PATH;

	tPath += L"Cursor\\StarcraftNWSE.ani";
	m_HANDLECURSOR.push_back(LoadCursorFromFile(tPath.c_str()));
	tPath = CONTENTS_PATH;
}

KeyMGR::~KeyMGR()
{
	// 이터레이터를 사용하여 벡터의 커서 핸들을 삭제
	for (vector<HCURSOR>::iterator it = m_HANDLECURSOR.begin(); it != m_HANDLECURSOR.end(); ++it)
	{
		if (*it != nullptr)
		{
			DeleteObject(*it);  // 커서 핸들 삭제
			*it = nullptr;      // 포인터 초기화
		}
	}
}

void KeyMGR::Init()
{
	for (size_t i = 0; i < KEY_END; ++i)
	{
		m_vecKeyInfo.push_back(KeyInfo{ KEY_STATE::NONE, false });
	}
	SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_CURSOR]);
}

void KeyMGR::Tick()
{
	// 게임 윈도우가 포커싱 중일 때
	if (GetFocus() == GameEngine::GetInstance()->GetMainWndHwnd())
	{
		for (size_t i = 0; i < m_vecKeyInfo.size(); ++i)
		{
			// 현재 해당 키가 눌려있다.
			if (GetAsyncKeyState(KeyValue[i]) & 0x8001)
			{
				// 이전에도 눌려있었다.
				if (m_vecKeyInfo[i].bPrevPressed)
				{
					m_vecKeyInfo[i].STATE = KEY_STATE::PRESSED;
				}

				// 이전에 눌려있지 않았다.
				else
				{
					m_vecKeyInfo[i].STATE = KEY_STATE::TAP;
				}

				m_vecKeyInfo[i].bPrevPressed = true;
			}

			// 현재 해당키가 안눌려있다.
			else
			{
				// 이전에는 눌려있었다.
				if (m_vecKeyInfo[i].bPrevPressed)
				{
					m_vecKeyInfo[i].STATE = KEY_STATE::RELEASED;
				}

				else
				{
					m_vecKeyInfo[i].STATE = KEY_STATE::NONE;
				}

				m_vecKeyInfo[i].bPrevPressed = false;
			}
		}

		// 마우스 좌표 갱신
		POINT ptPos = {};

		// 마우스 절대 좌표 받기
		GetCursorPos(&ptPos);

		// DC의 절대좌표를 WINDOW창 기반의 상대좌표로 바꾸기
		// 랜더링 좌표아님을 유의
		ScreenToClient(GameEngine::GetInstance()->GetMainWndHwnd(), &ptPos);

		m_MOUSEPOS = ptPos;

		// 마우스 커서 갱신
		SetMouseCursor(m_CURSORSTATE);

		// 드래그박스 체크
		if (KEY_NONE(RBTN) && KEY_NONE(LBTN))
		{
			m_DragAndDropBox.m_CLICK.x = 0;
			m_DragAndDropBox.m_CLICK.y = 0;
			m_DragAndDropBox.m_RELEASE.x = 0;
			m_DragAndDropBox.m_RELEASE.y = 0;
		}
	}
	// 게임 윈도우가 비활성화 되어 있을 때
	else
	{
		for (size_t i = 0; i < m_vecKeyInfo.size(); ++i)
		{
			if (KEY_STATE::TAP == m_vecKeyInfo[i].STATE
				|| KEY_STATE::PRESSED == m_vecKeyInfo[i].STATE)
			{
				m_vecKeyInfo[i].STATE = KEY_STATE::RELEASED;
			}

			else if (KEY_STATE::RELEASED == m_vecKeyInfo[i].STATE)
			{
				m_vecKeyInfo[i].STATE = KEY_STATE::NONE;
			}

			m_vecKeyInfo[i].bPrevPressed = false;
		}
		// 이 코드가 뭔가 문제가 있나?
		//// 마우스 좌표 갱신
		//*((int*)&m_MOUSEPOS.x) = 0xffffffff;
		//*((int*)&m_MOUSEPOS.y) = 0xffffffff;
	}
}

void KeyMGR::SetCursorType(CURSOR_TYPE _CURSORTYPE)
{
	m_CURSORSTATE = _CURSORTYPE;
}

// 커서 설정
void KeyMGR::SetMouseCursor(CURSOR_TYPE _CURSOR_TYPE)
{
	switch (_CURSOR_TYPE)
	{
	case STARCRAFT_CURSOR:

		// 인게임 스테이지에서만 방향커서 바뀌도록
		if (StageMGR::GetInstance()->m_CURRENTSTAGE == StageMGR::GetInstance()->m_ARRAYSTAGE[(UINT)STAGE_TYPE::INGAME])
		{
			// 단, 화면이동이 가능한 경우
			if (CameraMGR::GetInstance()->GetScreenMoveable())
			{
			FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();

			// 실제 좌표 기준으로 함
			// 마우스위치가 왼쪽으로 30포인트 쏠려있을 때
			if (m_MOUSEPOS.x <= 30)
			{
				// 마우스위치가 북서방향으로 30포인트 쏠려있을 때
				if (m_MOUSEPOS.y <= 30)
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NWSE]);

					// 화면 보는 것 조정도 같이
					CameraMGR::GetInstance()->SetLookAt(500.f, 500.f);
				}

				// 마우스위치가 남서방향으로 30포인트 쏠려있을 때
				else if (m_MOUSEPOS.y >= vResolution.y - 30)
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NESW]);

					// 화면 보는 것 조정도 같이
					CameraMGR::GetInstance()->SetLookAt(500.f, -500.f);
				}
				else
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_EW]);

					// 화면 보는 것 조정도 같이
					CameraMGR::GetInstance()->SetLookAt(500.f, 0.f);
				}
			}
			// 마우스위치가 오른쪽으로 30포인트 쏠려있을 때
			else if (m_MOUSEPOS.x >= vResolution.x - 30)
			{
				// 마우스위치가 북동방향으로 30포인트 쏠려있을 때
				if (m_MOUSEPOS.y <= 30)
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NESW]);

					// 화면 보는 것 조정도 같이
					CameraMGR::GetInstance()->SetLookAt(-500.f, 500.f);
				}

				// 마우스위치가 남동방향으로 30포인트 쏠려있을 때
				else if (m_MOUSEPOS.y >= vResolution.y - 30)
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NWSE]);

					// 화면 보는 것 조정도 같이
					CameraMGR::GetInstance()->SetLookAt(-500.f, -500.f);
				}
				else
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_EW]);

					// 화면 보는 것 조정도 같이
					CameraMGR::GetInstance()->SetLookAt(-500.f, 0.f);
				}
			}
			// 북쪽으로 방향으로 20포인트 쏠려있을 때
			else if (m_MOUSEPOS.y <= 20)
			{
				SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NS]);

				// 화면 보는 것 조정도 같이
				CameraMGR::GetInstance()->SetLookAt(0.f, 500.f);
			}
			// 남쪽으로 방향으로 20포인트 쏠려있을 때
			else if (m_MOUSEPOS.y >= vResolution.y - 20)
			{
				SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NS]);

				// 화면 보는 것 조정도 같이
				CameraMGR::GetInstance()->SetLookAt(0.f, -500.f);
			}
			else
			{
				SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_CURSOR]);
			}
		}
		else
		{
			SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_CURSOR]);
		}

		}
		break;
	case STARCRAFT_WORKING:
		SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_WORKING]);
		break;

	case STARCRAFT_CURSOR_RED:
		SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_CURSOR_RED]);
		break;


	case STARCRAFT_ALTERNATE:
		SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_ALTERNATE]);
		break;


	default:
		break;
	}
}

void KeyMGR::SetDragAndDropBox(DragAndDrop _BOX)
{
	m_DragAndDropBox = _BOX;
}

bool KeyMGR::IsMouseOffScreen()
{
	FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();

	if (vResolution.x <= m_MOUSEPOS.x || vResolution.y <= m_MOUSEPOS.y
		|| m_MOUSEPOS.x < 0 || m_MOUSEPOS.y < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}