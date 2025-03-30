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
//	// ���� ������� ANIMATION �� ������ ��
//	if (nullptr == m_CURRENTANIMATION)
//	{
//		return;
//	}
//
//	if (m_Finish)
//	{
//		// �ݺ� ����ϱ�� ������ �ٽ� 0 �� ��������Ʈ�� �ε����� �����Ѵ�.
//		if (m_Repeat)
//			Reset();
//
//		// �ѹ� ����� ������(m_Finish), �ݺ� �����尡 �ƴ϶��
//		// ������ �������� �����ϵ��� �Ѵ�.
//		else
//			return;
//	}
//
//	// FPS �� ���� �ð�üũ
//	m_Time += DELTATIME;
//	if (1.f / m_FPS <= m_Time)
//	{
//		m_Time -= 1.f / m_FPS;
//		++m_SpriteIdx;
//
//		// ������ Sprite �� �����ߴٸ�
//		if (m_CURRENTANIMATION->GetMaxSpriteCount() <= m_SpriteIdx)
//		{
//			// Finish ���� On
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
//	// Sprite �� ȭ�鿡 �׸���.
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