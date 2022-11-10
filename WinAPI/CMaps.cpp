#include "framework.h"
#include "CMaps.h"

#include "CRenderManager.h"

#include "CImage.h"


CMaps::CMaps()
{
	m_pImage = nullptr;
	m_pNextMap = nullptr;
	m_pPrevMap = nullptr;
	
	m_vecPos = Vector(0, 0);
	m_layer = Layer::Map;
	m_strName = L"¸Ê";
}

CMaps::~CMaps()
{
}

CImage* CMaps::GetIamge()
{
	return m_pImage;
}

void CMaps::SetImage(CImage* pImage)
{
	m_pImage = pImage;
}
void CMaps::SetNextMapImage(CImage* pImage)
{
	m_pNextMap = pImage;
}
void CMaps::SetPrevMapImage(CImage* pImage)
{
	m_pPrevMap = pImage;
}
void CMaps::Init()
{
	
}

void CMaps::Update()
{
}

void CMaps::Render()
{
	if (nullptr != m_pPrevMap)
	{
		RENDER->Image(
			m_pPrevMap,
			m_vecPos.x - (float)m_pImage->GetWidth() - (float)m_pNextMap->GetWidth(),
			m_vecPos.y,
			m_vecPos.x - (float)m_pNextMap->GetWidth(),
			m_vecPos.y + (float)m_pNextMap->GetHeight()
		);
	}
	if (nullptr != m_pImage)
	{
		RENDER->Image(
			m_pImage,
			m_vecPos.x,
			m_vecPos.y,
			m_vecPos.x+(float)m_pImage->GetWidth(),
			m_vecPos.y+(float)m_pImage->GetHeight()
		);
	}
	if (nullptr != m_pNextMap)
	{
		RENDER->Image(
			m_pNextMap,
			m_vecPos.x + (float)m_pImage->GetWidth(),
			m_vecPos.y,
			m_vecPos.x + (float)m_pImage->GetWidth() + (float)m_pNextMap->GetWidth(),
			m_vecPos.y + (float)m_pNextMap->GetHeight()
		);
	}
}

void CMaps::Release()
{
}
