#include "PreCompile.h"
#include "Stage.h"
#include "Object.h"

Stage::Stage()
{
}

Stage::~Stage()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::EOL; ++i)
	{
		// Ȥ�ó� ������ ����ڵ� ������
		// �Ʊ� ���� �������� �������߰ڴ�
		if (0 != m_VECTOROBJECTS->size())
		{
			Delete_Vector(m_VECTOROBJECTS[i]);
		}
	}
}

void Stage::Init()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::EOL; ++i)
	{
		for (size_t j = 0; j < m_VECTOROBJECTS[i].size(); ++j)
		{
			m_VECTOROBJECTS[i][j]->Init();
		}
	}
}

void Stage::Tick()
{
	// ���������ӿ� ��ϵ� �浹ü�� ��� ����
	for (UINT i = 0; i < (UINT)LAYER_TYPE::EOL; ++i)
	{
		c_VECTORCOLLIDER[i].clear();
	}

	// �������� �ȿ� �ִ� ��ü�鿡�� Tick ȣ��
	for (UINT i = 0; i < (UINT)LAYER_TYPE::EOL; ++i)
	{
		for (size_t j = 0; j < m_VECTOROBJECTS[i].size(); ++j)
		{
			m_VECTOROBJECTS[i][j]->Tick();
		}
	}
}

void Stage::FinalTick()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::EOL; ++i)
	{
		for (size_t j = 0; j < m_VECTOROBJECTS[i].size(); ++j)
		{
			m_VECTOROBJECTS[i][j]->FinalTick();
		}
	}
}

void Stage::Render()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::EOL; ++i)
	{
		vector<Object*>& vector_OBJECTS = m_VECTOROBJECTS[i];
		vector<Object*>::iterator iter = vector_OBJECTS.begin();
		for (; iter != vector_OBJECTS.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = vector_OBJECTS.erase(iter);
			}
			else
			{
				(*iter)->Render();
				++iter;
			}
		}
	}
}

void Stage::AddObject(Object* _Object, LAYER_TYPE _Type)
{
	m_VECTOROBJECTS[(UINT)_Type].push_back(_Object);
	_Object->m_LAYERTYPE = _Type; // ������Ʈ�� �Ҽ� ���̾ �˷���
}

Object* Stage::FindObjectByName(LAYER_TYPE _Layer, const wstring& _Name)
{
	vector<Object*>& vec = m_VECTOROBJECTS[(UINT)_Layer];

	for (size_t i = 0; i < vec.size(); ++i)
	{
		if (vec[i]->GetName() == _Name)
			return vec[i];
	}

	return nullptr;
}

void Stage::DeleteObject(int _LayerIdx)
{
	for (size_t i = 0; i < m_VECTOROBJECTS[_LayerIdx].size(); ++i)
	{
		if ((nullptr != m_VECTOROBJECTS[_LayerIdx][i]) && (m_VECTOROBJECTS[_LayerIdx][i]->IsDead()))
			continue;

		delete m_VECTOROBJECTS[_LayerIdx][i];
	}

	m_VECTOROBJECTS[_LayerIdx].clear();
}

void Stage::DeleteAllObject()
{
	for (int i = 0; i < (int)LAYER_TYPE::EOL; ++i)
	{
		DeleteObject(i);
	}
}
