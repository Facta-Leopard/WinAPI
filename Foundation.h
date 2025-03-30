#pragma once
#include "PreCompile.h"

class Foundation
{
public:
	Foundation();
	Foundation(const Foundation& _ORIGIN);
	virtual ~Foundation();

private:
	static UINT g_NextID;

private:
	wstring		m_Name;
	const UINT	m_ID;

public:
	void SetName(const wstring& _IN)
	{
		m_Name = _IN;
	}

	const wstring& GetName()
	{
		return m_Name;
	}
	
	UINT GetID()
	{
		return m_ID;
	}
	
	void operator =(const Foundation& _OTHER)
	{
		m_Name = _OTHER.m_Name;
	}
};