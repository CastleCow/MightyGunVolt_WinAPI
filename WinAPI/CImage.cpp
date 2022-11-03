#include "framework.h"
#include "CImage.h"

#include "CRenderManager.h"

CImage::CImage()
{
	m_pBitmap = nullptr;
}

CImage::~CImage()
{
	if (nullptr != m_pBitmap)
		m_pBitmap->Release();
	m_pBitmap = nullptr;
}

ID2D1Bitmap* CImage::GetImage()
{
	return m_pBitmap;
}

int CImage::GetWidth()
{
	return (int)m_pBitmap->GetSize().width;
}

int CImage::GetHeight()
{
	return (int)m_pBitmap->GetSize().height;
}

void CImage::Load(const wstring& filePath)
{
	HRESULT hResult;

	IWICBitmapDecoder*		p_decoder;		// ����� �̹����� ������ ��ü
	IWICBitmapFrameDecode*	p_frame;		// Ư�� �׸��� ������ ��ü
	IWICFormatConverter*	p_converter;	// �̹��� ��ȯ ��ü

	// WIC�� Factory ��ü�� ����Ͽ� �̹��� ���� ������ ���� ��ü�� ����
	hResult = RENDER->GetImageFactory()->CreateDecoderFromFilename(filePath.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &p_decoder);
	assert(S_OK == hResult && "Decoder Create Failed");

	// ������ �����ϴ� �̹��� �߿��� ù��° �̹����� ����
	hResult = p_decoder->GetFrame(0, &p_frame);
	assert(S_OK == hResult && "Decoder GetFrame Failed");
	
	// IWICBitmap������ ��Ʈ���� ID2D1Bitmap. �������� ��ȯ�ϱ� ���� ��ü ����
	hResult = RENDER->GetImageFactory()->CreateFormatConverter(&p_converter);
	assert(S_OK == hResult && "Format Convert Failed");

	// ���õ� �׸��� � ������ ��Ʈ������ ��ȯ�� ������ ����
	hResult = p_converter->Initialize(p_frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);
	assert(S_OK == hResult && "Converter Initialize Failed");

	// IWICBitmap ������ ��Ʈ������ ID2D1Bitmap ��ü�� ����
	hResult = RENDER->GetRenderTarget()->CreateBitmapFromWicBitmap(p_converter, NULL, &m_pBitmap);
	assert(S_OK == hResult && "Bitmap Create Failed");

	p_converter->Release();		// �̹��� ��ȯ ��ü ����
	p_frame->Release();			// �׸����Ͽ� �ִ� �̹����� �����ϱ� ���� ����� ��ü ����
	p_decoder->Release();		// ������ �����ϱ� ���� ������ ��ü ����
}