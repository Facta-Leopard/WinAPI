#include "PreCompile.h"
#include "Foundation.h"

UINT Foundation::g_NextID = 0;

Foundation::Foundation()
	: m_ID(g_NextID++)
{
}

Foundation::Foundation(const Foundation& _ORIGIN)
	: m_Name(_ORIGIN.m_Name)
	, m_ID(g_NextID++)
{
}

Foundation::~Foundation()
{
}