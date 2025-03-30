#include "PreCompile.h"
#include "PortraitMGR.h"
#include"MovingMotion.h"

void TransferStage(LAYER_TYPE _LAYERTYPE)
{
	switch (_LAYERTYPE)
	{
	case LAYER_TYPE::BACKGROUND:
		break;
	case LAYER_TYPE::TILE:
		break;
	case LAYER_TYPE::PLAYER1:
		break;
	case LAYER_TYPE::PLAYER2:
		break;
	case LAYER_TYPE::CRITTER:
		break;
	case LAYER_TYPE::MENU_MAIN:
		StageMGR::GetInstance()->ChangeStage(STAGE_TYPE::MAIN);
		break;
	case LAYER_TYPE::MENU_SUBMAIN:
		StageMGR::GetInstance()->ChangeStage(STAGE_TYPE::SUBMAIN);
		break;
	case LAYER_TYPE::MENU_BRIEDFING:
		StageMGR::GetInstance()->ChangeStage(STAGE_TYPE::BRIEFING);
		break;
	case LAYER_TYPE::MENU_INGAME:
		StageMGR::GetInstance()->ChangeStage(STAGE_TYPE::INGAME);
		break;
	case LAYER_TYPE::MENU_EXIT:
		PostMessage(GameEngine::GetInstance()->GetMainWndHwnd(), WM_CLOSE, 0, 0);
		break;
	case LAYER_TYPE::FOW:
		break;
	case LAYER_TYPE::UI_BASE:
		break;
	case LAYER_TYPE::UI_ADD:
		break;
	case LAYER_TYPE::UI_POSTBASE:
		break;
	case LAYER_TYPE::UI_POSTADD:
		break;
	case LAYER_TYPE::EOL:
		break;
	default:
		break;
	}
};

// ���� ������ ����
//void PlayMovingMotion(UNIT_TYPE _UNITTYPE, MOVINGMOTION_TYPE _MOVINGMOTIONTYPE, POINT _POSITION)
//{
//	MovingMotion pMovingMotion = PortraitMGR::GetInstance()->m_VECTOR_MOVINGMOTION[(int)_UNITTYPE];
//
//	Texture* pTEXTURE = pMovingMotion.GetTexture();
//	float tDuration = pMovingMotion.GetDuration();
//	float tFPSTime = pMovingMotion.GetFPSTime();
//	int tIndex = pMovingMotion.GetIndex();
//	int tMaxFrame = pMovingMotion.GetMaxFrame();
//
//	HDC tDC = GameEngine::GetInstance()->GetMemoryDC();
//
//	if (1 == tMaxFrame)
//	{
//		tIndex = 0;
//	}
//	else
//	{
//		if (tMaxFrame <= tIndex)
//		{
//			tIndex = 0;
//		}
//
//		if (tFPSTime < tDuration / tMaxFrame)
//		{
//			tIndex++;
//		}
//	}
//
//	// �ӽ÷� �׽�Ʈ�ϱ� ���� MARINE�� ũ��(64*64)�� ũ�� 64�� UNIT_RENDER_SIZE �����
//	// ���� ũ�Ⱑ �ٸ� ���ҽ� ���ֻ��� ������ �����ؾ���
//	TransparentBlt(tDC
//		, _POSITION.x - UNIT_RENDER_SIZE * 0.5
//		, _POSITION.y - UNIT_RENDER_SIZE * 0.5
//		, UNIT_RENDER_SIZE
//		, UNIT_RENDER_SIZE
//		, pTEXTURE->GetDC()
//		, 0, UNIT_RENDER_SIZE * tIndex
//		, pTEXTURE->GetWidth()
//		, UNIT_RENDER_SIZE
//		, RGB(255, 255, 255));
//}


// ���� ����
void PlaySoundSelected(UNIT_TYPE _UNITTYPE)
{
	UNIT_TYPE tSound = _UNITTYPE;
	switch (tSound)
	{
	case UNIT_TYPE::RAYNOR:
		break;
	case UNIT_TYPE::SCV:
		break;
	case UNIT_TYPE::MARINE:
		break;
	case UNIT_TYPE::MEDIC:
		break;
	case UNIT_TYPE::TANK:
		break;
	case UNIT_TYPE::MENU:
		break;
	default:
		break;
	}
};