#pragma once
#include "PreCompile.h"

union COLLISION_ID
{
	struct
	{
		UINT Left;
		UINT Right;
	};

	ULONGLONG ID;
};


class Collider;

class ColliderMGR
{
	SINGLE(ColliderMGR);

private:
	UINT					m_Matrix[(UINT)LAYER_TYPE::EOL];
	map<ULONGLONG, bool>	m_ColInfo;

public:
	void CollisionCheck(LAYER_TYPE _Left, LAYER_TYPE _Right);
	void CollisionCheckClear() { memset(m_Matrix, 0, sizeof(UINT) * (UINT)LAYER_TYPE::EOL); m_ColInfo.clear(); }

private:
	void CollisionBtwLayer(LAYER_TYPE _Left, LAYER_TYPE _Right);
	void CollisionBtwCollider(Collider* _LeftCol, Collider* _RightCol);
	bool IsCollision(Collider* _LeftCol, Collider* _RightCol);


public:
	void Tick();
};