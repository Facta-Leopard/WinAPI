#include "PreCompile.h"
//#include "R_AnimationPlayer.h"
//#include "GameEngine.h"
//
//R_AnimationPlayer::R_AnimationPlayer()
//	: Component(COMPONENT_TYPE::R_AnimationPlayer)
//	, m_CURRENTANIMATION(nullptr)
//	, m_SpriteIdx(0)
//	, m_FPS(0.f)
//	, m_Time(0.f)
//	, m_Repeat(false)
//	, m_Finish(false)
//{
//}
//
//R_AnimationPlayer::~R_AnimationPlayer()
//{
//}
//
//void R_AnimationPlayer::FinalTick()
//{
//	// 현재 재생중인 ANIMATION 이 없으면 끝
//	if (nullptr == m_CURRENTANIMATION)
//	{
//		return;
//	}
//
//	if (m_Finish)
//	{
//		// 반복 재생하기로 했으면 다시 0 번 스프라이트로 인덱스를 변경한다.
//		if (m_Repeat)
//			Reset();
//
//		// 한번 재생이 끝났고(m_Finish), 반복 재생모드가 아니라면
//		// 마지막 프레임을 유지하도록 한다.
//		else
//			return;
//	}
//
//	// FPS 에 따른 시간체크
//	m_Time += DELTATIME;
//	if (1.f / m_FPS <= m_Time)
//	{
//		m_Time -= 1.f / m_FPS;
//		++m_SpriteIdx;
//
//		// 마지막 Sprite 에 도달했다면
//		if (m_CURRENTANIMATION->GetMaxSpriteCount() <= m_SpriteIdx)
//		{
//			// Finish 상태 On
//			m_Finish = true;
//			--m_SpriteIdx;
//		}
//	}
//}
//
//void R_AnimationPlayer::Render()
//{
//	if (nullptr == m_CURRENTANIMATION)
//		return;
//
//	Sprite* Sprite = m_CURRENTANIMATION->GetSprite(m_SpriteIdx);
//
//	// Sprite 를 화면에 그린다.
//	HDC hBackDC = GameEngine::GetInstance()->GetMemoryDC();
//	FloatPoint vPOS = GetOwner()->GetCameraViewPosition();
//
//	FloatPoint LeftTop = FloatPoint(vPOS.x - (Sprite->GetSlice().x / 2) + Sprite->GetOffset().x,
//		vPOS.y - (Sprite->GetSlice().y / 2) + Sprite->GetOffset().y);
//
//	TransparentBlt(hBackDC
//		, vPOS.x - (Sprite->GetSlice().x / 2) + Sprite->GetOffset().x
//		, vPOS.y - (Sprite->GetSlice().y / 2) + Sprite->GetOffset().y
//		, Sprite->GetSlice().x
//		, Sprite->GetSlice().y
//		, Sprite->GetAtlas()->GetDC()
//		, Sprite->GetLeftTop().x
//		, Sprite->GetLeftTop().y
//		, Sprite->GetSlice().x
//		, Sprite->GetSlice().y
//		, RGB(0, 0, 0));
//}