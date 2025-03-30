#include "PreCompile.h"

#include "State.h"
#include "FSM.h"

FSM::FSM()
	: Component(COMPONENT_TYPE::FSM)
	, m_CURRENTSTATE(nullptr)
	, m_PREVSTATE(nullptr)
{
}

FSM::~FSM()
{
	Delete_Map(m_MAPSTATE);
}

void FSM::FinalTick()
{
	if (nullptr == m_CURRENTSTATE)
		return;

	m_CURRENTSTATE->FinalTick();
}

State* FSM::FindState(const wstring& _Key)
{
	map<wstring, State*>::iterator iter = m_MAPSTATE.find(_Key);

	if (iter == m_MAPSTATE.end())
		return nullptr;

	return iter->second;
}

void FSM::AddState(const wstring& _Key, State* _STATE)
{
	assert(!FindState(_Key));

	_STATE->m_OWNER = this;
	m_MAPSTATE.insert(make_pair(_Key, _STATE));
}


void FSM::ChangeState(const wstring& _NextState)
{
	State* pNextState = FindState(_NextState);
	assert(pNextState);

	if (nullptr != m_CURRENTSTATE)
		m_CURRENTSTATE->DeInit();

	m_CURRENTSTATE = pNextState;

	m_CURRENTSTATE->Enter();
}