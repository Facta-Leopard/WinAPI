#include "PreCompile.h"
#include "Class.h"

SelectGDI::SelectGDI(HDC _HDC, HGDIOBJ _INPUT)
	: m_HDC(_HDC)
	, m_PREVOBJECT(nullptr)
{
	m_PREVOBJECT = SelectObject(m_HDC, _INPUT);
}

SelectGDI::~SelectGDI()
{
	SelectObject(m_HDC, m_PREVOBJECT);
}