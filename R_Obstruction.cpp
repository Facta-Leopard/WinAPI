#include "PreCompile.h"
#include "R_Obstruction.h"

#include "Collider.h"
#include "RigidBody.h"

#include "CameraMGR.h"

//R_Obstruction::R_Obstruction()
//	: m_COLLIDER(nullptr)
//{
//	m_COLLIDER = (Collider*)AddComponent(new Collider);
//	m_COLLIDER->SetScale(FloatPoint(700.f, 150.f));
//}
//
//R_Obstruction::~R_Obstruction()
//{
//}
//
//void R_Obstruction::Tick()
//{
//}
//
//void R_Obstruction::BeginOverlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER)
//{
//	if (_OTHEROBJECT->GetName() == L"Player1")
//	{
//		RigidBody* pBody = _OTHEROBJECT->GetComponent<RigidBody>();
//		pBody->SetGround(true);
//		CameraMGR::GetInstance()->Oscillation(0.15f, 5.f, 10.f);
//	}
//}
//
//void R_Obstruction::Overlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER)
//{
//}
//
//void R_Obstruction::EndOverlap(Collider* _COLLIDER, Object* _OTHEROBJECT, Collider* _OTHERCOLLIDER)
//{
//	if (_OTHEROBJECT->GetName() == L"Player1")
//	{
//		RigidBody* pBody = _OTHEROBJECT->GetComponent<RigidBody>();
//		pBody->SetGround(false);
//	}
//}