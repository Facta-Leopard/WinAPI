#include "PreCompile.h"
#include "Texture.h"

Texture::Texture()
	: Asset(ASSET_TYPE::TEXTURE)
	, m_HANDLEBITMAP(nullptr)
	, m_DC(nullptr)
	, m_BITMAPINFORMATION{}
	, m_IMAGE(nullptr)
{
}

Texture::~Texture()
{
	DeleteDC(m_DC);
	DeleteObject(m_HANDLEBITMAP);

	if (nullptr != m_IMAGE)
		delete m_IMAGE;
}


int Texture::Load(const wstring& _FilePath)
{
	wstring strContent = PathMGR::GetContentPath();
	strContent += _FilePath;

	wchar_t ext[50] = {};
	_wsplitpath_s(strContent.c_str(), 0, 0, 0, 0, 0, 0, ext, 50);


	if (!wcscmp(ext, L".bmp") || !wcscmp(ext, L".BMP"))
	{
		// ��ηο� �����ϴ� �̹��� ������ ��Ʈ�� ���·� �޸𸮿� �ε�
		m_HANDLEBITMAP = (HBITMAP)LoadImage(nullptr, strContent.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	}
	else if (!wcscmp(ext, L".PNG") || !wcscmp(ext, L".PNG"))
	{
		// png �ε�
		m_IMAGE = Image::FromFile(strContent.c_str(), false);
		Bitmap* pBITMAP = (Bitmap*)m_IMAGE->Clone();

		Status stat = pBITMAP->GetHBITMAP(Color(0, 0, 0, 0), &m_HANDLEBITMAP);
		if (stat != Status::Ok)
			assert(nullptr);
	}

	// ��Ʈ���� Ÿ������ ������ DC ����
	m_DC = CreateCompatibleDC(GameEngine::GetInstance()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	DeleteObject(SelectObject(m_DC, m_HANDLEBITMAP));

	// ��Ʈ���� ������ �޾ƿ´�.
	GetObject(m_HANDLEBITMAP, sizeof(BITMAP), &m_BITMAPINFORMATION);

	return S_OK;
}

void Texture::Create(UINT _Width, UINT _Height)
{
	m_HANDLEBITMAP = CreateCompatibleBitmap(GameEngine::GetInstance()->GetMainDC(), _Width, _Height);

	m_DC = CreateCompatibleDC(GameEngine::GetInstance()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	DeleteObject(SelectObject(m_DC, m_HANDLEBITMAP));

	// ��Ʈ���� ������ �޾ƿ´�.
	GetObject(m_HANDLEBITMAP, sizeof(BITMAP), &m_BITMAPINFORMATION);
}