#include "PreCompile.h"
#include "Sprite.h"
#include "AssetMGR.h"

Sprite::Sprite()
	: Asset(ASSET_TYPE::SPRITE)
	, m_ATLAS(nullptr)
{
}

Sprite::~Sprite()
{
}

void Sprite::Create(Texture* _Atlas, FloatPoint _LeftTop, FloatPoint _Slice)
{
	m_ATLAS = _Atlas;
	m_UPLEFT = _LeftTop;
	m_SLICE = _Slice;
}

int Sprite::Save(const wstring& _RelativePath)
{
	wstring RelativePath = _RelativePath;
	CheckExt(L".sprite", RelativePath);

	// ������ �ڽ��� ��� ����Ǵ����� �˰� ��
	SetRelativePath(RelativePath);

	wstring strFilePath = PathMGR::GetContentPath() + RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"w");

	// ����Ű�� Atlas �ؽ����� Ű, ��θ� �����Ѵ�.	
	fwprintf_s(File, L"[KEY]\n");
	fwprintf_s(File, L"%s\n\n", GetKey().c_str());

	fwprintf_s(File, L"[PATH]\n");
	fwprintf_s(File, L"%s\n\n", GetRelativePath().c_str());

	wstring strAtlasKey, strAtlasPath;
	if (m_ATLAS)
	{
		strAtlasKey = m_ATLAS->GetKey();
		strAtlasPath = m_ATLAS->GetRelativePath();
	}
	fwprintf_s(File, L"[ATLAS_KEY]\n");
	fwprintf_s(File, L"%s\n", strAtlasKey.c_str());
	fwprintf_s(File, L"[ATLAS_PATH]\n");
	fwprintf_s(File, L"%s\n\n", strAtlasPath.c_str());


	fwprintf_s(File, L"[LEFT_TOP]\n");
	fwprintf_s(File, L"%d, %d\n\n", (int)m_UPLEFT.x, (int)m_UPLEFT.y);

	fwprintf_s(File, L"[SLICE]\n");
	fwprintf_s(File, L"%d, %d\n\n", (int)m_SLICE.x, (int)m_SLICE.y);

	fwprintf_s(File, L"[OFFSET]\n");
	fwprintf_s(File, L"%d, %d\n\n", (int)m_OFFSET.x, (int)m_OFFSET.y);


	fclose(File);

	return S_OK;
}

int Sprite::Load(const wstring& _RelativePath)
{
	wstring strFilePath = PathMGR::GetContentPath() + _RelativePath;

	FILE* File = nullptr;
	_wfopen_s(&File, strFilePath.c_str(), L"r");

	// ����Ű�� Atlas �ؽ����� Ű, ��θ� �����Ѵ�.
	wstring AtlasKey, AtlasPath;

	while (true)
	{
		wchar_t szBuff[255] = {};
		if (EOF == fwscanf_s(File, L"%s", szBuff, 255))
		{
			break;
		}

		if (!wcscmp(szBuff, L"[KEY]"))
		{
			fwscanf_s(File, L"%s", szBuff, 255);
			SetKey(szBuff);
		}

		else if (!wcscmp(szBuff, L"[PATH]"))
		{
			fwscanf_s(File, L"%s", szBuff, 255);
			SetRelativePath(szBuff);
		}

		else if (!wcscmp(szBuff, L"[ATLAS_KEY]"))
		{
			fwscanf_s(File, L"%s", szBuff, 255);
			AtlasKey = szBuff;
		}

		else if (!wcscmp(szBuff, L"[ATLAS_PATH]"))
		{
			fwscanf_s(File, L"%s", szBuff, 255);
			AtlasPath = szBuff;
			m_ATLAS = AssetMGR::GetInstance()->LoadTexture(AtlasKey, AtlasPath);
		}

		else if (!wcscmp(szBuff, L"[LEFT_TOP]"))
		{
			int x = 0, y = 0;
			fwscanf_s(File, L"%d, %d", &x, &y);
			m_UPLEFT = FloatPoint(x, y);
		}

		else if (!wcscmp(szBuff, L"[SLICE]"))
		{
			int x = 0, y = 0;
			fwscanf_s(File, L"%d, %d", &x, &y);
			m_SLICE = FloatPoint(x, y);
		}

		else if (!wcscmp(szBuff, L"[OFFSET]"))
		{
			int x = 0, y = 0;
			fwscanf_s(File, L"%d, %d", &x, &y);
			m_OFFSET = FloatPoint(x, y);
		}
	}


	fclose(File);

	return S_OK;
}