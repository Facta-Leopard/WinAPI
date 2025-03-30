#pragma once
#include "PreCompile.h"
#include "StageMGR.h"

// StarUnit헤더파일에서 구현을 조정해봄
// 멤버 함수포인터끼리 사용이 가능하도록 설정


void TransferStage(LAYER_TYPE _LAYERTYPE);

//void PlayMovingMotion(UNIT_TYPE _UNITTYPE, MOVINGMOTION_TYPE _MOVINGMOTIONTYPE, POINT _POSITION);

void PlaySoundSelected(UNIT_TYPE _LAYERTYPE);
