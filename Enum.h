#pragma once

enum KEY
{
	// 알파벳 키 (A ~ Z)
	Q, W, E, R, T, Y, U, I, O, P,	// Q ~ P
	A, S, D, F, G, H, J, K, L,      // A ~ L
	Z, X, C, V, B, N, M,            // Z ~ M

	// 숫자 키 (0 ~ 9)
	NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9,

	// 특수 문자 키들
	OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_PLUS, OEM_COMMA, OEM_PERIOD, OEM_MINUS,

	// 기능 키 (F1 ~ F12)
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

	// 제어 키들
	ENTER, ESC, TAB, SPACE, BACK, SHIFT, CONTROL, ALT, CAPSLOCK, NUMLOCK, SCROLLLOCK,

	// 방향키 (Up, Down, Left, Right)
	UP, DOWN, LEFT, RIGHT,

	// 숫자패드 키들
	NUMPAD0, NUMPAD1, NUMPAD2, NUMPAD3, NUMPAD4, NUMPAD5, NUMPAD6, NUMPAD7, NUMPAD8, NUMPAD9,

	// 숫자패드 연산자 키들
	NUMPAD_ADD, NUMPAD_SUBTRACT, NUMPAD_MULTIPLY, NUMPAD_DIVIDE, NUMPAD_DECIMAL,

	// 마우스 버튼들
	LBTN, RBTN,

	// 기타 키들
	LSHIFT, RSHIFT, LCONTROL, RCONTROL, LMENU, RMENU,

	KEY_END,  // 열거형의 끝을 나타내는 키
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


// 이름관련해서 바꾸는 함수를 만들어서 쓰면 좋을듯..(실행하자)
// 유닛타입 추가하면 매크로도 추가할 것
enum class UNIT_TYPE
{
	// Terran Unit
	// Terran 은 천자리 수 1
	// Hero & Heroine
	// 영웅 유닛은 백자리 수 0
	ETC = 0,


	// Common
	// 커맨더는 무조건 백천일 수 0
	ADVISOR = 1,

	// 바이오닉 유닛은 백자리 수 1
	MARINE =2,


	HYDRALISK = 3,

	MEDIC,

	// 기갑 유닛은 백자리 수 2
	// 기갑 유닛이면서 지상유닛은 십자리수 1
	VULTURE,
	TANK,

	// 기갑 유닛이면서 비행유닛은 십자리수 2
	WRAITH,
	DROPSHIP,


	// 바이오닉 이면서 기갑인 유닛은 백자리 수 3
	SCV,

	// Zerg Unit
	// Zerg 은 천자리 수 2
	// Hero&Hiroine

	// Common

	// Protoss Unit
	// Protoss 은 천자리 수 3
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
	// IDLE 상태 (대기)
	IDLE_DOWN = 0,        // row 01-03, column 01-34
	IDLE_DOWNLEFT = 1,    // row 01-03, column 02-05
	IDLE_LEFT = 2,        // row 01-03, column 06-09
	IDLE_UPLEFT = 3,      // row 01-03, column 12-14
	IDLE_UP = 4,          // row 01-03, column 15-20
	IDLE_UPRIGHT = 5,     // row 01-03, column 20-22
	IDLE_RIGHT = 6,       // row 01-03, column 24-29
	IDLE_DOWNRIGHT = 7,   // row 01-03, column 30-33

	// MOVE 상태 (이동)
	MOVE_DOWN = 8,        // row 05-13, column 01-34
	MOVE_DOWNLEFT = 9,    // row 05-13, column 02-05
	MOVE_LEFT = 10,       // row 05-13, column 06-09
	MOVE_UPLEFT = 11,     // row 05-13, column 12-14
	MOVE_UP = 12,         // row 05-13, column 15-20
	MOVE_UPRIGHT = 13,    // row 05-13, column 20-22
	MOVE_RIGHT = 14,      // row 05-13, column 24-29
	MOVE_DOWNRIGHT = 15,  // row 05-13, column 30-33

	// ATTACK 상태 (공격)
	ATTACK_DOWN = 16,     // row 03-04, column 01-34
	ATTACK_DOWNLEFT = 17, // row 03-04, column 02-05
	ATTACK_LEFT = 18,     // row 03-04, column 06-09
	ATTACK_UPLEFT = 19,   // row 03-04, column 12-14
	ATTACK_UP = 20,       // row 03-04, column 15-20
	ATTACK_UPRIGHT = 21,  // row 03-04, column 20-22
	ATTACK_RIGHT = 22,    // row 03-04, column 24-29
	ATTACK_DOWNRIGHT = 23,// row 03-04, column 30-33

	// 향후 로딩이나 멀티 쓰레딩 구현되면 추가될 상태들
	// IDLE_PORTRAIT = 24,   // 대기 상태 (포트레이트)
	// TALKING_PORTRAIT = 25, // 대화 중인 상태 (포트레이트)
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
	TEXTURE,	// 이미지
	SPRITE,		// 특정 텍스쳐의 특정 부위
	ANIMATION,	// Sprite 의 집합체
	SOUND,		// 소리	
};

enum class DEBUG_SHAPE
{
	RECT,
	CIRCLE,
	LINE,
};