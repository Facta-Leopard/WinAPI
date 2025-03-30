#pragma once
#include "PreCompile.h"

class DBGRenderMGR
{
	SINGLE(DBGRenderMGR);
private:
	list<DbgRenderInfo>		m_DbgInfo;
	bool					m_Show;

public:
	void Tick();

	void AddDbgInfo(const DbgRenderInfo& _info)
	{
		if (false == m_Show)
			return;

		m_DbgInfo.push_back(_info);
	}

	void ShowDebugRender(bool _Show) { m_Show = _Show; }

public:
	void Render();
};