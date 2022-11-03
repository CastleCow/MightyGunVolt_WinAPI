#pragma once

class CCore;
class CImage;

class CRenderManager : public SingleTon<CRenderManager>
{
	friend SingleTon<CRenderManager>;
	friend CCore;
private:
	CRenderManager();
	virtual ~CRenderManager();

private:
	ID2D1Factory*			m_pFactory;			// D2D ���丮
	ID2D1HwndRenderTarget*	m_pRenderTarget;	// �׷��� �ϴ� ȭ�� (D2D�� HDC)
	IWICImagingFactory*		m_pImageFactory;	// �̹��� ���丮
	IDWriteFactory*			m_pWriteFactory;	// �׸��� ���丮

	ID2D1SolidColorBrush*	m_pDefaultBrush;		// ������ �׸��� ���� �귯��
	IDWriteTextFormat*		m_pDefaultTextFormat;	// �ؽ�Ʈ�� �׸��� ���� ����

	ID2D1SolidColorBrush*	m_pCurBrush;		// ���� �귯��
	IDWriteTextFormat*		m_pCurTextFormat;	// ���� �ؽ�Ʈ ����

private:
	void Init();
	void BeginDraw();
	void EndDraw();
	void Release();

public:
	void SetBrush(Color color);
	void SetTextFormat(
		wstring fontName,
		DWRITE_FONT_WEIGHT fontWeight,
		DWRITE_FONT_STYLE fontStyle,
		DWRITE_FONT_STRETCH fontStretch,
		FLOAT fontSize,
		wstring localeName = L"ko");
	void SetTextAlignment(DWRITE_TEXT_ALIGNMENT textAlignment);
	void SetTextParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment);

public:
	void Text(wstring str, float dstX, float dstY, float dstW, float dstH);
	void Text(wstring str, float dstX, float dstY, float dstW, float dstH, Color color, float fontSize = 10.f);

	void Line(Vector startPoint, Vector endPoint);
	void Line(Vector startPoint, Vector endPoint, Color color, float strokeWidth = 1.f);

	void FrameRect(float startX, float startY, float endX, float endY);
	void FrameRect(float startX, float startY, float endX, float endY, Color color, float strokeWidth = 1.f);
	void FillRect(float startX, float startY, float endX, float endY);
	void FillRect(float startX, float startY, float endX, float endY, Color color);

	void FrameEllipse(float startX, float startY, float endX, float endY);
	void FrameEllipse(float startX, float startY, float endX, float endY, Color color, float strokeWidth = 1.f);
	void FillEllipse(float startX, float startY, float endX, float endY);
	void FillEllipse(float startX, float startY, float endX, float endY, Color color);

	void FrameCircle(float pointX, float pointY, float radius);
	void FrameCircle(float pointX, float pointY, float radius, Color color, float strokeWidth = 1.f);
	void FillCircle(float pointX, float pointY, float radius);
	void FillCircle(float pointX, float pointY, float radius, Color color);

	void Image(CImage* pImg, float startX, float startY, float endX, float endY, float alpha = 1.f);
	void FrameImage(CImage* pImg, float dstX, float dstY, float dstW, float dstH,
		float srcX, float srcY, float srcW, float srcH, float alpha = 1.f);

public:
	IWICImagingFactory*		GetImageFactory();
	ID2D1HwndRenderTarget*	GetRenderTarget();
};

#define	RENDER	CRenderManager::GetInstance()