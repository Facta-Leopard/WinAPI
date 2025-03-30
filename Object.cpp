#include "PreCompile.h"
#include "Object.h"
#include "GameEngine.h"
#include "Component.h"
#include "CameraMGR.h"

Object::Object()
	: m_POSITION{}
	, m_SCALE{}
	, m_LAYERTYPE(LAYER_TYPE::EOL)
	, m_Dead(false)
{
}

Object::~Object()
{
	//Delete_Vector(m_COMPONENT);
}

void Object::Init()
{

}

void Object::FinalTick()
{
	//for (size_t i = 0; i < m_COMPONENT.size(); ++i)
	//{
	//	m_COMPONENT[i]->FinalTick();
	//}
}

void Object::Render()
{
	HDC dc = GameEngine::GetInstance()->GetMemoryDC();

	FloatPoint tPOS = GetCameraViewPosition();

	Rectangle(dc
		, tPOS.x - m_SCALE.x / 2
		, tPOS.y - m_SCALE.y / 2
		, tPOS.x + m_SCALE.x / 2
		, tPOS.y + m_SCALE.y / 2);
}

//Component* Object::AddComponent(Component* _Component)
//{
//	m_COMPONENT.push_back(_Component);
//
//	_Component->m_OWNER = this;
//
//	return _Component;
//}

//Component* Object::GetComponent(const wstring& _Name)
//{
//	for (size_t i = 0; i < m_COMPONENT.size(); ++i)
//	{
//		if (m_COMPONENT[i]->GetName() == _Name)
//			return m_COMPONENT[i];
//	}
//
//	return nullptr;
//}

//Component* Object::GetComponent(COMPONENT_TYPE _TYPE)
//{
//	for (size_t i = 0; i < m_COMPONENT.size(); ++i)
//	{
//		if (m_COMPONENT[i]->GetType() == _TYPE)
//			return m_COMPONENT[i];
//	}
//
//	return nullptr;
//}

FloatPoint Object::GetCameraViewPosition()
{
	return CameraMGR::GetInstance()->GetCameraView(m_POSITION);
}

FloatPoint Object::GetIngameViewPosition()
{
	return CameraMGR::GetInstance()->GetInGameView(m_POSITION);
}