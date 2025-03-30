#include "PreCompile.h"

// 적 마우스오버 여부 확인
//vector<Object*> tVECTOR = StageMGR::GetInstance()->GetCurrentStage()->GetObjects(LAYER_TYPE::PLAYER2);
//if (0 != tVECTOR.size())
//{
//	for (vector<Object*>::iterator iter = tVECTOR.begin(); iter != tVECTOR.end(); iter++)
//	{
//		FloatPoint tTARGETFLOATPOINT = (*iter)->GetPosition();
//
//		tTARGETFLOATPOINT.x -= GetPosition().x;
//		tTARGETFLOATPOINT.y -= GetPosition().y;
//
//		// 타겟과의 거리를 구함
//		int tDistance = (int)sqrt((tPloatPoint.x * tPloatPoint.x) + (tPloatPoint.y * tPloatPoint.y));
//
//		if (m_AttackRange < tDistance)
//		{
//			return this;
//		}
//		else
//		{
//			m_STATETYPE = STATE_TYPE::ATTACK_;
//			return m_TARGET;
//		}
//
//			break;
//	}
//}
//
//switch (m_STATETYPE)
//{
//case IDLE_:
//
//
//
//	else if (MOVINGMOTION_TYPE::MOVE_DOWNRIGHT == tMOVINGMOTION)
//	{
//
//	}
//
//	else if (MOVINGMOTION_TYPE::MOVE_DOWN == tMOVINGMOTION)
//	{
//
//	}
//
//	else if (MOVINGMOTION_TYPE::MOVE_LEFT == tMOVINGMOTION)
//	{
//
//	}
//
//	else if (MOVINGMOTION_TYPE::MOVE_UPLEFT == tMOVINGMOTION)
//	{
//
//	}
//
//	else if (MOVINGMOTION_TYPE::MOVE_DOWNLEFT == tMOVINGMOTION)
//	{
//
//	}
//
//	else if (MOVINGMOTION_TYPE::MOVE_UP == tMOVINGMOTION)
//	{
//
//	}
//
//	else if (MOVINGMOTION_TYPE::MOVE_UPRIGHT == tMOVINGMOTION)
//	{
//
//	}
//	break;
//
//case MOVE_:
//	if (isRight && !isUP && !isDown)
//	{
//
//	}
//	else if (isUP && isRight)
//	{
//
//	}
//	else if (isUP && !isRight && !isLeft)
//	{
//
//	}
//	else if (isUP && isLeft)
//	{
//
//	}
//	else if (isLeft && !isUP && isDown)
//	{
//
//	}
//	else if (isDown && isLeft)
//	{
//
//	}
//	else if (isDown && !isRight && !isLeft)
//	{
//
//	}
//	else if (isDown && isRight)
//	{
//
//	}
//	break;
//
//case ATTACK_:
//	if (MOVINGMOTION_TYPE::MOVE_RIGHT == tMOVINGMOTION)
//	{
//
//	}
//	else if (MOVINGMOTION_TYPE::MOVE_DOWNRIGHT == tMOVINGMOTION)
//	{
//
//	}
//	else if (MOVINGMOTION_TYPE::MOVE_DOWN == tMOVINGMOTION)
//	{
//
//	}
//	else if (MOVINGMOTION_TYPE::MOVE_LEFT == tMOVINGMOTION)
//	{
//
//	}
//	else if (MOVINGMOTION_TYPE::MOVE_UPLEFT == tMOVINGMOTION)
//	{
//
//	}
//	else if (MOVINGMOTION_TYPE::MOVE_DOWNLEFT == tMOVINGMOTION)
//	{
//
//	}
//	else if (MOVINGMOTION_TYPE::MOVE_UP == tMOVINGMOTION)
//	{
//
//	}
//	else if (MOVINGMOTION_TYPE::MOVE_UPRIGHT == tMOVINGMOTION)
//	{
//
//	}
//	break;
//
//
//
//
//
//
//
//if (2.0f < m_SoundDuration)
//{
//	m_Soundable = true;
//	m_SoundDuration = 0.f;
//}
//
//
//
//
//
//