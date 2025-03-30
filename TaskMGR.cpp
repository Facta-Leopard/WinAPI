#include "PreCompile.h"
#include "TaskMGR.h"

#include "StageMGR.h"
#include "Stage.h"
#include "Object.h"

TaskMGR::TaskMGR()
{
}

TaskMGR::~TaskMGR()
{
}

void TaskMGR::Tick()
{
	// Dead 오브젝트 처리
	for (size_t i = 0; i < m_GARBAGE.size(); ++i)
	{
		delete m_GARBAGE[i];
	}
	m_GARBAGE.clear();

	for (size_t i = 0; i < m_TASK.size(); ++i)
	{
		switch (m_TASK[i].Type)
		{
		case TASK_TYPE::CREATE_OBJECT:
		{
			Object* pObject = (Object*)m_TASK[i].Param0;
			LAYER_TYPE Type = (LAYER_TYPE)m_TASK[i].Param1;
			StageMGR::GetInstance()->GetCurrentStage()->AddObject(pObject, Type);
			pObject->Init();
		}
		break;
		case TASK_TYPE::DELETE_OBJECT:
		{
			Object* pObject = (Object*)m_TASK[i].Param0;

			// Dead 처리가 안된 경우에만 처리해준다. 
			// 동시에 같은 오브젝트에 대해서 Delete 요청이 여러번인 경우 대처하기 위함
			if (!pObject->IsDead())
			{
				pObject->m_Dead = true;
				m_GARBAGE.push_back(pObject);
			}
		}
		break;
		case TASK_TYPE::CHANGE_STAGE:
		{
			STAGE_TYPE tNEXTSTAGE = (STAGE_TYPE)m_TASK[i].Param0;

			StageMGR::GetInstance()->ChangeStage(tNEXTSTAGE);
		}
		break;
		}
	}

	m_TASK.clear();
}
