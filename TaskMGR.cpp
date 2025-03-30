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
	// Dead ������Ʈ ó��
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

			// Dead ó���� �ȵ� ��쿡�� ó�����ش�. 
			// ���ÿ� ���� ������Ʈ�� ���ؼ� Delete ��û�� �������� ��� ��ó�ϱ� ����
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
