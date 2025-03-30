#pragma once
#include "PreCompile.h"
#include "Collider.h"

#include "StageMGR.h"
#include "Stage.h"
#include "CameraMGR.h"

Collider::Collider()
	: Component(COMPONENT_TYPE::COLLIDER)
	, m_OverlapCount(0)
{
}

Collider::~Collider()
{
}

void Collider::FinalTick()
{
	m_FINALPOS = m_OFFSET + GetOwner()->GetPosition();

	// Collider 등록하기
	LAYER_TYPE LayerType = GetOwner()->GetLayerType();
	StageMGR::GetInstance()->GetCurrentStage()->RegisterCollider(this, LayerType);


	FloatPoint vRenderPos = CameraMGR::GetInstance()->GetCameraView(m_FINALPOS);
	if (m_OverlapCount)
		DrawDebugRect(PEN_COLOR::RED, vRenderPos, m_SCALE, 0.f);
	else
		DrawDebugRect(PEN_COLOR::GREEN, vRenderPos, m_SCALE, 0.f);
}


void Collider::BeginOverlap(Collider* _OTHER)
{
	++m_OverlapCount;

	GetOwner()->BeginOverlap(this, _OTHER->GetOwner(), _OTHER);
}

void Collider::Overlap(Collider* _OTHER)
{
	GetOwner()->Overlap(this, _OTHER->GetOwner(), _OTHER);
}

void Collider::EndOverlap(Collider* _OTHER)
{
	--m_OverlapCount;

	GetOwner()->EndOverlap(this, _OTHER->GetOwner(), _OTHER);
}
