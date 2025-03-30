#include "PreCompile.h"
#include "FSM.h"
#include "Player2.h"
#include "Collider.h"
#include "IdleState.h"
#include "TraceState.h"

//Player2::Player2()
//	: m_Dir(1)
//	, m_Speed(300.f)
//	, m_Dist(100.f)
//	, m_COLLIDER(nullptr)
//	, m_FSM(nullptr)
//{
//	m_Tex = AssetMGR::GetInstance()->LoadTexture(L"Character", L"Texture\\TX_GlowScene_2.PNG");
//
//	// Collider 컴포넌트 추가
//	m_COLLIDER = (Collider*)AddComponent(new Collider);
//	m_COLLIDER->SetScale(FloatPoint(100.f, 100.f));
//
//	// 몬스터 스탯
//	m_INFORMATION.MaxHP = 100.f;
//	m_INFORMATION.CurHP = 100.f;
//	m_INFORMATION.AttRange = 100.f;
//	m_INFORMATION.DetectRange = 200.f;
//	m_INFORMATION.Speed = 100.f;
//
//	// FSM 컴포넌트 추가
//	m_FSM = (FSM*)AddComponent(new FSM);
//
//	// FSM 에 상태 추가
//	m_FSM->AddState(L"Idle", new IdleState);
//	m_FSM->AddState(L"Trace", new TraceState);
//}
//
//Player2::~Player2()
//{
//}
//
//void Player2::Init()
//{
//	m_FSM->ChangeState(L"Idle");
//
//	// 스테이지이 시작할때 초기 위치값 기록
//	m_InitPos = GetPosition();
//}
//
//void Player2::Tick()
//{
//	return;
//
//	FloatPoint vPos = GetPosition();
//
//	vPos.x += DELTATIME * m_Speed * m_Dir;
//
//	float fDistance = fabs(m_InitPos.x - vPos.x);
//
//	if (m_Dist < fDistance)
//	{
//		vPos.x = m_InitPos.x + m_Dir * m_Dist;
//		m_Dir *= -1;
//	}
//
//	SetPosition(vPos);
//}
//
//void Player2::Render()
//{
//	HDC dc = GameEngine::GetInstance()->GetMemoryDC();
//
//	FloatPoint vPos = GetCameraViewPosition();
//	FloatPoint vScale = GetScale();
//
//	//BitBlt(dc
//	//	, vPos.x - m_Tex->GetWidth() * 0.5
//	//	, vPos.y - m_Tex->GetHeight() / 2
//	//	, m_Tex->GetWidth()
//	//	, m_Tex->GetHeight()
//	//	, m_Tex->GetDC()
//	//	, 0, 0
//	//	, SRCCOPY);
//
//	BLENDFUNCTION blend = {};
//
//	blend.BlendOp = AC_SRC_OVER;
//	blend.BlendFlags = 0;
//	blend.SourceConstantAlpha = 127;
//	blend.AlphaFormat = AC_SRC_ALPHA;
//
//	AlphaBlend(dc
//		, vPos.x - m_Tex->GetWidth() * 0.5
//		, vPos.y - m_Tex->GetHeight() * 0.5
//		, m_Tex->GetWidth()
//		, m_Tex->GetHeight()
//		, m_Tex->GetDC()
//		, 0, 0
//		, m_Tex->GetWidth()
//		, m_Tex->GetHeight()
//		, blend);
//
//	/*Ellipse(dc, vPos.x - vScale.x * 0.5, vPos.y - vScale.y / 2
//		, vPos.x + vScale.x * 0.5, vPos.y + vScale.y * 0.5 );*/
//}
//
//
//
//void Player2::BeginOverlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER)
//{
//	if (_OTHEROBJECT->GetName() == L"Player1")
//	{
//		// 플레이어랑 부딪히면 다음 스테이지로 넘어간다.
//		ChangeStage(STAGE_TYPE::TITLE);
//	}
//}