#include "PreCompile.h"
#include "PathMGR.h"

wchar_t PathMGR::g_ContentPath[255] = {};
wchar_t PathMGR::g_BinPath[255] = {};
wchar_t PathMGR::g_SolutionPath[255] = {};

PathMGR::PathMGR()
{

}

PathMGR::~PathMGR()
{

}

void PathMGR::Init()
{
	wchar_t szBuff[255] = {};

	// ���� ���μ����� ���(����� ���� ������ ��� ����ó�� �ʿ�, ������Ʈ ����->Debug->�۾����͸� ����
	GetCurrentDirectory(255, szBuff);

	for (int i = wcslen(szBuff); 0 <= i; --i)
	{
		if (L'\\' == szBuff[i])
		{
			szBuff[i] = L'\0';
			break;
		}
	}

	wcscat_s(szBuff, 255, L"\\Content\\");

	wcscpy_s(g_ContentPath, 255, szBuff);
}