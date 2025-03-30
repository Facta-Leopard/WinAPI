#pragma once

enum KEY
{
	// ���ĺ� Ű (A ~ Z)
	Q, W, E, R, T, Y, U, I, O, P,	// Q ~ P
	A, S, D, F, G, H, J, K, L,      // A ~ L
	Z, X, C, V, B, N, M,            // Z ~ M

	// ���� Ű (0 ~ 9)
	NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,

	// Ư�� ���� Ű��
	OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_PLUS, OEM_COMMA, OEM_PERIOD, OEM_MINUS,

	// ��� Ű (F1 ~ F12)
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

	// ���� Ű��
	ENTER, ESC, TAB, SPACE, BACK, SHIFT, CONTROL, ALT, CAPSLOCK, NUMLOCK, SCROLLLOCK,

	// ����Ű (Up, Down, Left, Right)
	UP, DOWN, LEFT, RIGHT,

	// �����е� Ű��
	NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,

	// �����е� ������ Ű��
	NUMPAD_ADD, NUMPAD_SUBTRACT, NUMPAD_MULTIPLY, NUMPAD_DIVIDE, NUMPAD_DECIMAL,

	// ���콺 ��ư��
	LBTN, RBTN,

	// ��Ÿ Ű��
	LSHIFT, RSHIFT, LCONTROL, RCONTROL, LMENU, RMENU,

	KEY_END,  // �������� ���� ��Ÿ���� Ű
};

enum KEY_STATE
{
	NONE,
	TAP,
	PRESSED,
	RELEASED,
};

enum CURSOR_TYPE
{
	STARCRAFT_CURSOR,
	STARCRAFT_WORKING,
	STARCRAFT_CURSOR_RED,
	STARCRAFT_ALTERNATE,
	STARCRAFT_EW,
	STARCRAFT_NS,
	STARCRAFT_NESW,
	STARCRAFT_NWSE,

	CURSOR_EOL
};

enum BROOD_TYPE
{
	TERRAN,
	ZERG,
	PROTOSS,
	XELNAGA,
	NOTHING,
};


// �̸������ؼ� �ٲٴ� �Լ��� ���� ���� ������..(��������)
// ����Ÿ�� �߰��ϸ� ��ũ�ε� �߰��� ��
enum class UNIT_TYPE
{
	// Terran Unit
	// Terran �� õ�ڸ� �� 1
	// Hero & Heroine
	// ���� ������ ���ڸ� �� 0
	ETC = 0,


	// Common
	// Ŀ�Ǵ��� ������ ��õ�� �� 0
	ADVISOR = 1,

	// ���̿��� ������ ���ڸ� �� 1
	MARINE =2,


	HYDRALISK = 3,

	MEDIC,

	// �Ⱙ ������ ���ڸ� �� 2
	// �Ⱙ �����̸鼭 ���������� ���ڸ��� 1
	VULTURE,
	TANK,

	// �Ⱙ �����̸鼭 ���������� ���ڸ��� 2
	WRAITH,
	DROPSHIP,


	// ���̿��� �̸鼭 �Ⱙ�� ������ ���ڸ� �� 3
	SCV,

	// Zerg Unit
	// Zerg �� õ�ڸ� �� 2
	// Hero&Hiroine

	// Common

	// Protoss Unit
	// Protoss �� õ�ڸ� �� 3
	// Hero&Hiroine

	// Common


	// Etc

	RAYNOR,

	MENU,
};

enum STATE_TYPE
{
	IDLE_,
	MOVE_,
	ATTACK_,
	DIE_,

	STATE_EOL,
};

enum DIRECTION_TYPE
{
	DOWN_,
	DOWNLEFT_,
	LEFT_,
	UPLEFT_,
	UP_,
	UPRIGHT_,
	RIGHT_,
	DOWNRIGHT_,

	DIRECTION_EOL_,
};

enum class MOVINGMOTION_TYPE
{
	// IDLE ���� (���)
	IDLE_DOWN = 0,        // row 01-03, column 01-34
	IDLE_DOWNLEFT = 1,    // row 01-03, column 02-05
	IDLE_LEFT = 2,        // row 01-03, column 06-09
	IDLE_UPLEFT = 3,      // row 01-03, column 12-14
	IDLE_UP = 4,          // row 01-03, column 15-20
	IDLE_UPRIGHT = 5,     // row 01-03, column 20-22
	IDLE_RIGHT = 6,       // row 01-03, column 24-29
	IDLE_DOWNRIGHT = 7,   // row 01-03, column 30-33

	// MOVE ���� (�̵�)
	MOVE_DOWN = 8,        // row 05-13, column 01-34
	MOVE_DOWNLEFT = 9,    // row 05-13, column 02-05
	MOVE_LEFT = 10,       // row 05-13, column 06-09
	MOVE_UPLEFT = 11,     // row 05-13, column 12-14
	MOVE_UP = 12,         // row 05-13, column 15-20
	MOVE_UPRIGHT = 13,    // row 05-13, column 20-22
	MOVE_RIGHT = 14,      // row 05-13, column 24-29
	MOVE_DOWNRIGHT = 15,  // row 05-13, column 30-33

	// ATTACK ���� (����)
	ATTACK_DOWN = 16,     // row 03-04, column 01-34
	ATTACK_DOWNLEFT = 17, // row 03-04, column 02-05
	ATTACK_LEFT = 18,     // row 03-04, column 06-09
	ATTACK_UPLEFT = 19,   // row 03-04, column 12-14
	ATTACK_UP = 20,       // row 03-04, column 15-20
	ATTACK_UPRIGHT = 21,  // row 03-04, column 20-22
	ATTACK_RIGHT = 22,    // row 03-04, column 24-29
	ATTACK_DOWNRIGHT = 23,// row 03-04, column 30-33

	// ���� �ε��̳� ��Ƽ ������ �����Ǹ� �߰��� ���µ�
	// IDLE_PORTRAIT = 24,   // ��� ���� (��Ʈ����Ʈ)
	// TALKING_PORTRAIT = 25, // ��ȭ ���� ���� (��Ʈ����Ʈ)
};

enum class PORTRAIT_TYPE
{
	PORTRAITE_IDLE = 0,
	PORTRAITE_TALK = 1,
};

enum POST_PROCESS
{
	FADE_IN,
	FADE_OUT,
	HEART,
};

enum class PEN_COLOR
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	GRAY,
	
	EOL
};

enum class BRUSH_COLOR
{
	RED,
	GREEN,
	BLUE,
	GRAY,
	HOLLOW,
	
	EOL
};

enum class STAGE_TYPE
{
	TITLE,
	MAIN,
	SUBMAIN,
	BRIEFING,
	INGAME,
	VICTORY,
	DEFEAT,

	EOL
};

enum class TASK_TYPE
{
	// Param0 : Object Address, Param1 : Layer Index
	CREATE_OBJECT,

	// Param0 : Object Address
	DELETE_OBJECT,

	// Param0 : Current Stage
	CURRENT_STAGE,

	// Param0 : Next Stage
	CHANGE_STAGE,
};

enum class LAYER_TYPE
{
	BACKGROUND,
	TILE,

	PLAYER1,
	PLAYER2,

	CRITTER,
	
	MENU_PREMOUSEOVER,
	MENU_MAIN,
	MENU_SUBMAIN,
	MENU_BRIEDFING,
	MENU_INGAME,
	MENU_EXIT,
	MENU_MOUSEOVER,

	// FOW = Fog of War
	FOW = 27,
	UI_BASE = 28,
	UI_ADD = 29,
	UI_POSTBASE = 30,
	UI_POSTADD = 31,
	EOL = 32
};

enum class COMPONENT_TYPE
{
	COLLIDER,
	RIGIDBODY,
	MOVINGMOTION,
	PORTRAIT,

	FSM,
	MAPTILE
};

enum class ASSET_TYPE
{
	TEXTURE,	// �̹���
	SPRITE,		// Ư�� �ؽ����� Ư�� ����
	ANIMATION,	// Sprite �� ����ü
	SOUND,		// �Ҹ�	
};

enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	LINE,
};