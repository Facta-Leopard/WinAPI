#include "PreCompile.h"
#include "DBGRenderMGR.h"

#include "GameEngine.h"
#include "Class.h"

DBGRenderMGR::DBGRenderMGR()
	: m_Show(true)
{

}

DBGRenderMGR::~DBGRenderMGR()
{

}

void DBGRenderMGR::Tick()
{
	if (KEY_TAP(KEY::NUM9))
	{
		m_Show ? m_Show = false : m_Show = true;
	}
}

void DBGRenderMGR::Render()
{
	list<DbgRenderInfo>::iterator iter = m_DbgInfo.begin();

	HDC dc = GameEngine::GetInstance()->GetMemoryDC();

	for (; iter != m_DbgInfo.end(); )
	{
		if (m_Show)
		{
			SELECT_PEN((*iter).Color);
			SELECT_BRUSH(BRUSH_COLOR::HOLLOW);

			switch ((*iter).Type)
			{
			case DEBUG_SHAPE::RECT:

				Rectangle(dc, (int)(*iter).Position0.x - (int)(*iter).Scale.x * 0.5
					, (int)(*iter).Position0.y - (int)(*iter).Scale.y * 0.5
					, (int)(*iter).Position0.x + (int)(*iter).Scale.x * 0.5
					, (int)(*iter).Position0.y + (int)(*iter).Scale.y * 0.5);

				break;
			case DEBUG_SHAPE::CIRCLE:

				Ellipse(dc, (int)(*iter).Position0.x - (int)(*iter).Scale.x * 0.5
					, (int)(*iter).Position0.y - (int)(*iter).Scale.y * 0.5
					, (int)(*iter).Position0.x + (int)(*iter).Scale.x * 0.5
					, (int)(*iter).Position0.y + (int)(*iter).Scale.y * 0.5);

				break;
			case DEBUG_SHAPE::LINE:

				MoveToEx(dc, (int)(*iter).Position0.x, (int)(*iter).Position0.y, nullptr);
				LineTo(dc, (int)(*iter).Position1.x, (int)(*iter).Position1.y);

				break;
			}
		}

		(*iter).Time += DELTATIME;
		if ((*iter).Duration <= (*iter).Time)
		{
			iter = m_DbgInfo.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}