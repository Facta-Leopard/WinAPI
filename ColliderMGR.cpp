#include "PreCompile.h"
#include "ColliderMGR.h"

#include "StageMGR.h"
#include "Stage.h"
#include "Object.h"
#include "Collider.h"

ColliderMGR::ColliderMGR()
	: m_Matrix{}
{
}

ColliderMGR::~ColliderMGR()
{

}

void ColliderMGR::CollisionCheck(LAYER_TYPE _Left, LAYER_TYPE _Right)
{
	// �Է����� ���� ���̾� ��ȣ�߿��� �� �������� Matrix �� ������, �� ū���� ���� ����Ѵ�.
	UINT Row = (UINT)_Left;
	UINT Col = (UINT)_Right;

	if (Col < Row)
	{
		Row = (UINT)_Right;
		Col = (UINT)_Left;
	}

	// �̹� üũ�� �Ǿ�������
	if (m_Matrix[Row] & (1 << Col))
	{
		// ��Ʈ�� ����.
		m_Matrix[Row] &= ~(1 << Col);
	}

	// üũ�� �ȵǾ�������
	else
	{
		// üũ�Ѵ�.
		m_Matrix[Row] |= (1 << Col);
	}
}

void ColliderMGR::Tick()
{
	for (UINT Row = 0; Row < (UINT)LAYER_TYPE::EOL; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)LAYER_TYPE::EOL; ++Col)
		{
			if (!(m_Matrix[Row] & (1 << Col)))
				continue;

			CollisionBtwLayer((LAYER_TYPE)Row, (LAYER_TYPE)Col);
		}
	}
}


void ColliderMGR::CollisionBtwLayer(LAYER_TYPE _Left, LAYER_TYPE _Right)
{
	const vector<Collider*>& vecLeft = StageMGR::GetInstance()->GetCurrentStage()->GetColliders(_Left);
	const vector<Collider*>& vecRight = StageMGR::GetInstance()->GetCurrentStage()->GetColliders(_Right);

	// ���� �ٸ� ���̾�� �浹 �˻�
	if (_Left != _Right)
	{
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = 0; j < vecRight.size(); ++j)
			{
				CollisionBtwCollider(vecLeft[i], vecRight[j]);
			}
		}
	}

	// ���� ���̾�� �浹 �˻�
	else
	{
		// �ߺ� �˻� or �ڱ��ڽŰ��� �˻縦 ���ϱ� ���ؼ� j �� i + 1 ���� �����Ѵ�.
		for (size_t i = 0; i < vecLeft.size(); ++i)
		{
			for (size_t j = i + 1; j < vecRight.size(); ++j)
			{
				CollisionBtwCollider(vecLeft[i], vecRight[j]);
			}
		}
	}
}

void ColliderMGR::CollisionBtwCollider(Collider* _LeftCol, Collider* _RightCol)
{
	COLLISION_ID ColID = {};
	ColID.Left = _LeftCol->GetID();
	ColID.Right = _RightCol->GetID();

	map<ULONGLONG, bool>::iterator iter = m_ColInfo.find(ColID.ID);

	// �� �浹ü ������ ��ϵ� ���� ����.
	if (iter == m_ColInfo.end())
	{
		// ����� ��Ų��.
		m_ColInfo.insert(make_pair(ColID.ID, false));
		iter = m_ColInfo.find(ColID.ID);
	}

	// �� �浹ü �� 1���� ���� ���� ������Ʈ���
	bool IsDead = _LeftCol->GetOwner()->IsDead() || _RightCol->GetOwner()->IsDead();

	// ���� �����ִ�.
	if (!IsDead && IsCollision(_LeftCol, _RightCol))
	{
		// �������� �����־���.
		if (iter->second)
		{
			_LeftCol->Overlap(_RightCol);
			_RightCol->Overlap(_LeftCol);
		}

		// �������� �������� �ʾҴ�.
		else
		{
			_LeftCol->BeginOverlap(_RightCol);
			_RightCol->BeginOverlap(_LeftCol);
			iter->second = true; // �浹���� ����
		}
	}

	// ���� ������ �ִ�.
	else
	{
		// �������� �����־���.
		if (iter->second)
		{
			_LeftCol->EndOverlap(_RightCol);
			_RightCol->EndOverlap(_LeftCol);
			iter->second = false;
		}
	}
}

bool ColliderMGR::IsCollision(Collider* _LeftCol, Collider* _RightCol)
{
	FloatPoint LeftPos = _LeftCol->GetFinalPos();
	FloatPoint RightPos = _RightCol->GetFinalPos();

	FloatPoint LeftScale = _LeftCol->GetScale();
	FloatPoint RightScale = _RightCol->GetScale();
	FloatPoint vDiff = LeftPos - RightPos;

	if (fabs(vDiff.x) < (LeftScale.x + RightScale.x) * 0.5
		&& fabs(vDiff.y) < (LeftScale.y + RightScale.y) * 0.5)
	{
		return true;
	}

	return false;
}