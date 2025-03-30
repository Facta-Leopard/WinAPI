#pragma once

// StingleTon
#define SINGLE(Type)	public:\
							static Type* GetInstance()\
							{\
								static Type singleTon;\
								return &singleTon;\
							}\
							private:\
								Type();\
								Type(const Type& _Origin) = delete;\
								void operator =(const Type& _Origin) = delete;\
								~Type();

#define DELTATIME TimeMGR::GetInstance()->GetDELTATIME()
#define CONTENTS_PATH PathMGR::GetInstance()->GetContentPath()

#define KEY_CHECK(key, STATE) (KeyMGR::GetInstance()->GetKeyState(key) == STATE)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_PRESSED(key) KEY_CHECK(key, KEY_STATE::PRESSED)
#define KEY_RELEASED(key) KEY_CHECK(key, KEY_STATE::RELEASED)

#define SELECT_PEN(Pen) SelectGDI SelectPen(GameEngine::GetInstance()->GetMemoryDC(), GameEngine::GetInstance()->GetPen(Pen));
#define SELECT_BRUSH(Brush) SelectGDI SelectBrush(GameEngine::GetInstance()->GetMemoryDC(), GameEngine::GetInstance()->GetBrush(Brush));

// 카메라 좌표전환 매크로
#define CAMERAVIEW_POS(Position) CameraMGR::GetInstance()->GetCameraView(Position);
#define INGAME_POS(Position) CameraMGR::GetInstance()->GetInGameView(Position);

#define DELETE(p) if(p != nullptr) {delete p; p = nullptr;}

#define PI 3.14159265358979323846

#define TILE_SIZE 32

#define UNIT_RENDER_SIZE 64


// 설마 매크로 문이 문제인가?
// //함수형을 추가해서 테스트 예정
// enum 값을 문자열로 바꾸기 위한 매크로
// 근데 왜 enum class가 되면 문제가 되지?
// 유닛타입 추가하면 여기도 추가할 것
#define UNIT_TYPE_TO_STRING(x) \
    ((x) == UNIT_TYPE::ETC ? L"Etc" : \
    (x) == UNIT_TYPE::ADVISOR ? L"Advisor" : \
    (x) == UNIT_TYPE::MARINE ? L"Marine" : \
    (x) == UNIT_TYPE::HYDRALISK ? L"Hydralisk" : \
    (x) == UNIT_TYPE::MEDIC ? L"MEDIC" : \
    (x) == UNIT_TYPE::VULTURE ? L"VULTURE" : \
    (x) == UNIT_TYPE::TANK ? L"TANK" : \
    (x) == UNIT_TYPE::WRAITH ? L"WRAITH" : \
    (x) == UNIT_TYPE::DROPSHIP ? L"DROPSHIP" : \
    (x) == UNIT_TYPE::SCV ? L"SCV" : \
    (x) == UNIT_TYPE::RAYNOR ? L"RAYNOR" : L"")

#define UNIT_TYPE_TO_INT(x) \
    ((x) == UNIT_TYPE::ETC ? 0 : \
    (x) == UNIT_TYPE::ADVISOR ? 1 : \
    (x) == UNIT_TYPE::MARINE ? 2 : \
    (x) == UNIT_TYPE::HYDRALISK ? 3 : \
    (x) == UNIT_TYPE::MEDIC ? 4 : \
    (x) == UNIT_TYPE::VULTURE ? 5 : \
    (x) == UNIT_TYPE::TANK ? 6 : \
    (x) == UNIT_TYPE::WRAITH ? 7 : \
    (x) == UNIT_TYPE::DROPSHIP ? 8 : \
    (x) == UNIT_TYPE::SCV ? 9 : \
    (x) == UNIT_TYPE::RAYNOR ? 10 : 0)

#define INT_TO_UNIT_TYPE(x) \
    ((x) == 0 ? UNIT_TYPE::ETC : \
    (x) == 1 ? UNIT_TYPE::ADVISOR : \
    (x) == 2 ? UNIT_TYPE::MARINE : \
    (x) == 3 ? UNIT_TYPE::HYDRALISK : \
    (x) == 4 ? UNIT_TYPE::MEDIC : \
    (x) == 5 ? UNIT_TYPE::VULTURE : \
    (x) == 6 ? UNIT_TYPE::TANK : \
    (x) == 7 ? UNIT_TYPE::WRAITH : \
    (x) == 8 ? UNIT_TYPE::DROPSHIP : \
    (x) == 9 ? UNIT_TYPE::SCV : \
    (x) == 10 ? UNIT_TYPE::RAYNOR : UNIT_TYPE::ETC)

// enum값을 문자열로 바꾸기 위한 매크로
#define MOVINGMOTION_TYPE_TO_STRING(x) \
    ((x) == MOVINGMOTION_TYPE::IDLE_DOWN ? L"IDLE_DOWN" : \
    (x) == MOVINGMOTION_TYPE::IDLE_DOWNLEFT ? L"IDLE_DOWNLEFT" : \
    (x) == MOVINGMOTION_TYPE::IDLE_LEFT ? L"IDLE_LEFT" : \
    (x) == MOVINGMOTION_TYPE::IDLE_UPLEFT ? L"IDLE_UPLEFT" : \
    (x) == MOVINGMOTION_TYPE::IDLE_UP ? L"IDLE_UP" : \
    (x) == MOVINGMOTION_TYPE::IDLE_UPRIGHT ? L"IDLE_UPRIGHT" : \
    (x) == MOVINGMOTION_TYPE::IDLE_RIGHT ? L"IDLE_RIGHT" : \
    (x) == MOVINGMOTION_TYPE::IDLE_DOWNRIGHT ? L"IDLE_DOWNRIGHT" : \
    (x) == MOVINGMOTION_TYPE::MOVE_DOWN ? L"MOVE_DOWN" : \
    (x) == MOVINGMOTION_TYPE::MOVE_DOWNLEFT ? L"MOVE_DOWNLEFT" : \
    (x) == MOVINGMOTION_TYPE::MOVE_LEFT ? L"MOVE_LEFT" : \
    (x) == MOVINGMOTION_TYPE::MOVE_UPLEFT ? L"MOVE_UPLEFT" : \
    (x) == MOVINGMOTION_TYPE::MOVE_UP ? L"MOVE_UP" : \
    (x) == MOVINGMOTION_TYPE::MOVE_UPRIGHT ? L"MOVE_UPRIGHT" : \
    (x) == MOVINGMOTION_TYPE::MOVE_RIGHT ? L"MOVE_RIGHT" : \
    (x) == MOVINGMOTION_TYPE::MOVE_DOWNRIGHT ? L"MOVE_DOWNRIGHT" : \
    (x) == MOVINGMOTION_TYPE::ATTACK_DOWN ? L"ATTACK_DOWN" : \
    (x) == MOVINGMOTION_TYPE::ATTACK_DOWNLEFT ? L"ATTACK_DOWNLEFT" : \
    (x) == MOVINGMOTION_TYPE::ATTACK_LEFT ? L"ATTACK_LEFT" : \
    (x) == MOVINGMOTION_TYPE::ATTACK_UPLEFT ? L"ATTACK_UPLEFT" : \
    (x) == MOVINGMOTION_TYPE::ATTACK_UP ? L"ATTACK_UP" : \
    (x) == MOVINGMOTION_TYPE::ATTACK_UPRIGHT ? L"ATTACK_UPRIGHT" : \
    (x) == MOVINGMOTION_TYPE::ATTACK_RIGHT ? L"ATTACK_RIGHT" : \
    L"IDLE_DOWN")

// Player_Unit 방향설정용
// 방향값 설정을 위한 분기문 매크로
#define MOVINGMOTION_TYPE_TO_DIRECTIONANGLE(x) \
    ((x) == MOVINGMOTION_TYPE::IDLE_DOWN ? 180 : \
    (x) == MOVINGMOTION_TYPE::IDLE_DOWNLEFT ? 135 : \
    (x) == MOVINGMOTION_TYPE::IDLE_LEFT ? 90 : \
    (x) == MOVINGMOTION_TYPE::IDLE_UPLEFT ? 45 : \
    (x) == MOVINGMOTION_TYPE::IDLE_UP ? 0 : \
    (x) == MOVINGMOTION_TYPE::IDLE_UPRIGHT ? 315 : \
    (x) == MOVINGMOTION_TYPE::IDLE_RIGHT ? 270 : \
    (x) == MOVINGMOTION_TYPE::IDLE_DOWNRIGHT ? 215 : \
    (x) == MOVINGMOTION_TYPE::MOVE_DOWN ? 180 : \
    (x) == MOVINGMOTION_TYPE::MOVE_DOWNLEFT ? 135 : \
    (x) == MOVINGMOTION_TYPE::MOVE_LEFT ? 90 : \
    (x) == MOVINGMOTION_TYPE::MOVE_UPLEFT ? 45 : \
    (x) == MOVINGMOTION_TYPE::MOVE_UP ? 0 : \
    (x) == MOVINGMOTION_TYPE::MOVE_UPRIGHT ? 315 : \
    (x) == MOVINGMOTION_TYPE::MOVE_RIGHT ? 270 : \
    (x) == MOVINGMOTION_TYPE::MOVE_DOWNRIGHT ? 215 : \
    (x) == MOVINGMOTION_TYPE::ATTACK_DOWN ? 180 : \
    (x) == MOVINGMOTION_TYPE::ATTACK_DOWNLEFT ? 135 : \
    (x) == MOVINGMOTION_TYPE::ATTACK_LEFT ? 90 : \
    (x) == MOVINGMOTION_TYPE::ATTACK_UPLEFT ? 45 : \
    (x) == MOVINGMOTION_TYPE::ATTACK_UP ? 0 : \
    (x) == MOVINGMOTION_TYPE::ATTACK_UPRIGHT ? 315 : \
    (x) == MOVINGMOTION_TYPE::ATTACK_RIGHT ? 270 : \
    180)

// enum값을 문자열로 바꾸기 위한 매크로
#define PORTRAIT_TYPE_TO_STRING(x) \
    ((x) == PORTRAIT_TYPE::PORTRAITE_IDLE ? L"PORTRAITE_IDLE" : \
    (x) == PORTRAIT_TYPE::PORTRAITE_TALK ? L"PORTRAITE_TALK" : \
    L"")


// #를 앞에 붙히면, 문자열처럼 변함.
// 처음 알았네 ㅋ
// 매크로 구문은 오버로드가 안됨..
// 또 삽질 엄청했네..
//#define PLAY_SOUND1(Asset1) Sound* pSound1 = AssetMGR::GetInstance()->LoadSound(L#Asset1, L"Sound\\" L#Asset1 L".wav");\
//if (nullptr != pSound1)\
//{\
//    pSound1->Play(false);\
//    pSound1->SetVolume(80.f);\
//}
//
//#define PLAY_SOUND2(Asset2, State) Sound* pSound2 = AssetMGR::GetInstance()->LoadSound(L#Asset2, L"Sound\\" L#Asset2 L"\\" #State L".wav");\
//if (nullptr != pSound2)\
//{\
//    pSound2->Play(false);\
//    pSound2->SetVolume(80.f);\
//}
//
//#define PLAY_SOUND3(Asset3) Sound* pSound3 = AssetMGR::GetInstance()->LoadSound(L#Asset3, L"Sound\\" L#Asset3 L".wav");\
//if (nullptr != pSound3)\
//{\
//    pSound3->Play(false);\
//    pSound3->SetVolume(80.f);\
//}
//
//#define PLAY_SOUND4(Asset4, State) Sound* pSound4 = AssetMGR::GetInstance()->LoadSound(L#Asset4, L"Sound\\" L#Asset4 L"\\" #State L".wav");\
//if (nullptr != pSound4)\
//{\
//    pSound4->Play(false);\
//    pSound4->SetVolume(80.f);\
//}