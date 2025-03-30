#include "PreCompile.h"
#include "GameEngine.h"

#include "CameraMGR.h"

// Ű �� �迭
UINT KeyValue[KEY::KEY_END] = 
{
    // ���ĺ� Ű (A ~ Z)
    'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  // Q ~ P
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',        // A ~ L
    'Z', 'X', 'C', 'V', 'B', 'N', 'M',                  // Z ~ M

    // ���� Ű (0 ~ 9)
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',    // ���� 0 ~ 9

    // Ư�� ���� Ű (�Ϲ������� Ű���� ���� ��ȣ��)
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

    // ��� Ű (F1 ~ F12)
    VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12,  // F1 ~ F12

    // ���� Ű
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

    // ����Ű (Up, Down, Left, Right)
    VK_UP,        // ���� ����Ű (Up Arrow)
    VK_DOWN,      // �Ʒ��� ����Ű (Down Arrow)
    VK_LEFT,      // ���� ����Ű (Left Arrow)
    VK_RIGHT,     // ������ ����Ű (Right Arrow)

    // �����е� Ű (Numpad 0 ~ Numpad 9)
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

    // �����е� ������ Ű
    VK_ADD,       // Numpad +
    VK_SUBTRACT,  // Numpad -
    VK_MULTIPLY,  // Numpad *
    VK_DIVIDE,    // Numpad /
    VK_DECIMAL,   // Numpad . (Decimal point)

    // ���콺 ��ư (����, ������, ���)
    VK_LBUTTON,   // ���� ���콺 ��ư (Left Mouse Button)
    VK_RBUTTON,   // ������ ���콺 ��ư (Right Mouse Button)

    //VK_MBUTTON,   // ��� ���콺 ��ư (Middle Mouse Button)

    // ��Ÿ Ű��
    VK_LSHIFT,    // ���� Shift Ű
    VK_RSHIFT,    // ������ Shift Ű
    VK_LCONTROL,  // ���� Control Ű
    VK_RCONTROL,  // ������ Control Ű
    VK_LMENU,     // ���� Alt Ű (Left Alt)
    VK_RMENU,     // ������ Alt Ű (Right Alt)
};


KeyMGR::KeyMGR()
	: m_CURSORSTATE(STARCRAFT_CURSOR)
	, m_DragAndDropBox{ {0, 0},{0, 0} }
{
	// Ŀ�� ���� �ε�
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
	// ���ͷ����͸� ����Ͽ� ������ Ŀ�� �ڵ��� ����
	for (vector<HCURSOR>::iterator it = m_HANDLECURSOR.begin(); it != m_HANDLECURSOR.end(); ++it)
	{
		if (*it != nullptr)
		{
			DeleteObject(*it);  // Ŀ�� �ڵ� ����
			*it = nullptr;      // ������ �ʱ�ȭ
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
	// ���� �����찡 ��Ŀ�� ���� ��
	if (GetFocus() == GameEngine::GetInstance()->GetMainWndHwnd())
	{
		for (size_t i = 0; i < m_vecKeyInfo.size(); ++i)
		{
			// ���� �ش� Ű�� �����ִ�.
			if (GetAsyncKeyState(KeyValue[i]) & 0x8001)
			{
				// �������� �����־���.
				if (m_vecKeyInfo[i].bPrevPressed)
				{
					m_vecKeyInfo[i].STATE = KEY_STATE::PRESSED;
				}

				// ������ �������� �ʾҴ�.
				else
				{
					m_vecKeyInfo[i].STATE = KEY_STATE::TAP;
				}

				m_vecKeyInfo[i].bPrevPressed = true;
			}

			// ���� �ش�Ű�� �ȴ����ִ�.
			else
			{
				// �������� �����־���.
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

		// ���콺 ��ǥ ����
		POINT ptPos = {};

		// ���콺 ���� ��ǥ �ޱ�
		GetCursorPos(&ptPos);

		// DC�� ������ǥ�� WINDOWâ ����� �����ǥ�� �ٲٱ�
		// ������ ��ǥ�ƴ��� ����
		ScreenToClient(GameEngine::GetInstance()->GetMainWndHwnd(), &ptPos);

		m_MOUSEPOS = ptPos;

		// ���콺 Ŀ�� ����
		SetMouseCursor(m_CURSORSTATE);

		// �巡�׹ڽ� üũ
		if (KEY_NONE(RBTN) && KEY_NONE(LBTN))
		{
			m_DragAndDropBox.m_CLICK.x = 0;
			m_DragAndDropBox.m_CLICK.y = 0;
			m_DragAndDropBox.m_RELEASE.x = 0;
			m_DragAndDropBox.m_RELEASE.y = 0;
		}
	}
	// ���� �����찡 ��Ȱ��ȭ �Ǿ� ���� ��
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
		// �� �ڵ尡 ���� ������ �ֳ�?
		//// ���콺 ��ǥ ����
		//*((int*)&m_MOUSEPOS.x) = 0xffffffff;
		//*((int*)&m_MOUSEPOS.y) = 0xffffffff;
	}
}

void KeyMGR::SetCursorType(CURSOR_TYPE _CURSORTYPE)
{
	m_CURSORSTATE = _CURSORTYPE;
}

// Ŀ�� ����
void KeyMGR::SetMouseCursor(CURSOR_TYPE _CURSOR_TYPE)
{
	switch (_CURSOR_TYPE)
	{
	case STARCRAFT_CURSOR:

		// �ΰ��� �������������� ����Ŀ�� �ٲ��
		if (StageMGR::GetInstance()->m_CURRENTSTAGE == StageMGR::GetInstance()->m_ARRAYSTAGE[(UINT)STAGE_TYPE::INGAME])
		{
			// ��, ȭ���̵��� ������ ���
			if (CameraMGR::GetInstance()->GetScreenMoveable())
			{
			FloatPoint vResolution = GameEngine::GetInstance()->GetResolution();

			// ���� ��ǥ �������� ��
			// ���콺��ġ�� �������� 30����Ʈ ������� ��
			if (m_MOUSEPOS.x <= 30)
			{
				// ���콺��ġ�� �ϼ��������� 30����Ʈ ������� ��
				if (m_MOUSEPOS.y <= 30)
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NWSE]);

					// ȭ�� ���� �� ������ ����
					CameraMGR::GetInstance()->SetLookAt(500.f, 500.f);
				}

				// ���콺��ġ�� ������������ 30����Ʈ ������� ��
				else if (m_MOUSEPOS.y >= vResolution.y - 30)
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NESW]);

					// ȭ�� ���� �� ������ ����
					CameraMGR::GetInstance()->SetLookAt(500.f, -500.f);
				}
				else
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_EW]);

					// ȭ�� ���� �� ������ ����
					CameraMGR::GetInstance()->SetLookAt(500.f, 0.f);
				}
			}
			// ���콺��ġ�� ���������� 30����Ʈ ������� ��
			else if (m_MOUSEPOS.x >= vResolution.x - 30)
			{
				// ���콺��ġ�� �ϵ��������� 30����Ʈ ������� ��
				if (m_MOUSEPOS.y <= 30)
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NESW]);

					// ȭ�� ���� �� ������ ����
					CameraMGR::GetInstance()->SetLookAt(-500.f, 500.f);
				}

				// ���콺��ġ�� ������������ 30����Ʈ ������� ��
				else if (m_MOUSEPOS.y >= vResolution.y - 30)
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NWSE]);

					// ȭ�� ���� �� ������ ����
					CameraMGR::GetInstance()->SetLookAt(-500.f, -500.f);
				}
				else
				{
					SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_EW]);

					// ȭ�� ���� �� ������ ����
					CameraMGR::GetInstance()->SetLookAt(-500.f, 0.f);
				}
			}
			// �������� �������� 20����Ʈ ������� ��
			else if (m_MOUSEPOS.y <= 20)
			{
				SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NS]);

				// ȭ�� ���� �� ������ ����
				CameraMGR::GetInstance()->SetLookAt(0.f, 500.f);
			}
			// �������� �������� 20����Ʈ ������� ��
			else if (m_MOUSEPOS.y >= vResolution.y - 20)
			{
				SetCursor(m_HANDLECURSOR[CURSOR_TYPE::STARCRAFT_NS]);

				// ȭ�� ���� �� ������ ����
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