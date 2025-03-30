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

	// 실행 프로세스의 경로(디버깅 모드로 실행할 경우 예외처리 필요, 프로젝트 구성->Debug->작업디렉터리 세팅
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