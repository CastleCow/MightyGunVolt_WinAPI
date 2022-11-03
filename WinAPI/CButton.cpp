#include "framework.h"
#include "CButton.h"

#include "CRenderManager.h"

CButton::CButton()
{
	m_pCallback = nullptr;
	m_pParam1 = 0;
	m_pParam2 = 0;

	m_strText = L"";
	m_iSizeText = 12;
	m_colorText = Color(0, 0, 0, 1);
}

CButton::~CButton()
{
}

void CButton::SetClickedCallback(CallbackFunc pCallback, DWORD_PTR pParam1, DWORD_PTR pParam2)
{
	m_pCallback = pCallback;
	m_pParam1 = pParam1;
	m_pParam2 = pParam2;
}

void CButton::SetText(const wstring& text, float fontSize, Color color)
{
	m_strText = text;
	m_iSizeText = fontSize;
	m_colorText = color;
}

void CButton::Init()
{
}

void CButton::Update()
{
}

void CButton::Render()
{
	RENDER->FillRect(
		m_vecRenderPos.x,
		m_vecRenderPos.y,
		m_vecRenderPos.x + m_vecScale.x,
		m_vecRenderPos.y + m_vecScale.y,
		Color(255, 255, 255, 1)
	);

	RENDER->FrameRect(
		m_vecRenderPos.x,
		m_vecRenderPos.y,
		m_vecRenderPos.x + m_vecScale.x,
		m_vecRenderPos.y + m_vecScale.y,
		Color(0, 0, 0, 1)
	);

	RENDER->Text(
		m_strText,
		m_vecRenderPos.x,
		m_vecRenderPos.y,
		m_vecRenderPos.x + m_vecScale.x,
		m_vecRenderPos.y + m_vecScale.y,
		m_colorText,
		m_iSizeText
	);
}

void CButton::Release()
{
}

void CButton::OnMouseEnter()
{
}

void CButton::OnMouseOver()
{
}

void CButton::OnMouseExit()
{
}

void CButton::OnMouseUp()
{
}

void CButton::OnMouseDown()
{
	if (nullptr != m_pCallback)
		m_pCallback(m_pParam1, m_pParam2);
}

void CButton::OnMouseClicked()
{
}
