#pragma once

class SelectGDI
{
private:
	HDC		 m_HDC;
	HGDIOBJ	 m_PREVOBJECT;

public:
	SelectGDI(HDC _HDC, HGDIOBJ _INPUT);
	~SelectGDI();
};