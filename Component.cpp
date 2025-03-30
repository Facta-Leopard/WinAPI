#include "PreCompile.h"
#include "Component.h"

Component::Component(COMPONENT_TYPE _TYPE)
	: m_OWNER(nullptr)
	, m_TYPE(_TYPE)
{
}

Component::~Component()
{
}
