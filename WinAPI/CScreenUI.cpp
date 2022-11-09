#include "framework.h"
#include "CScreenUI.h"
#include"CPlayer.h"
#include"CImage.h"
CScreenUI::CScreenUI()
{
	m_layer = Layer::Ui;
	m_vecRenderPos = Vector(0, 0);
	m_Hpbar = nullptr;
	m_PIcon = nullptr;
	m_SideBar = nullptr;
}

CScreenUI::~CScreenUI()
{
}

void CScreenUI::Init()
{
	m_Hpbar = RESOURCE->LoadImg(L"HPbar", L"Image\\UI\\UI_HPbarFull.png");
	m_PIcon = RESOURCE->LoadImg(L"Icon", L"Image\\UI\\GV_profile1.png");
	m_SideBar = RESOURCE->LoadImg(L"SideUI", L"Image\\UI\\GV_SIDEUI.png");
}

void CScreenUI::Update()
{


}

void CScreenUI::Render()
{
	
	
	RENDER->Image(m_Hpbar, (m_vecRenderPos.x + 100), (m_vecRenderPos.y), (m_vecRenderPos.x + 100 + WINSIZEX * 0.2f), (m_vecRenderPos.y + WINSIZEY * 0.1f));
	RENDER->Image(m_PIcon, (m_vecRenderPos.x + 110), (m_vecRenderPos.y), (m_vecRenderPos.x + 170), (m_vecRenderPos.y + WINSIZEY * 0.09f));
	RENDER->Image(m_SideBar, m_vecRenderPos.x-100, m_vecRenderPos.y, m_vecRenderPos.x+100, m_vecRenderPos.y+WINSIZEY );
	RENDER->Image(m_SideBar, WINSIZEX+m_vecRenderPos.x-100, m_vecRenderPos.y,WINSIZEX+ m_vecRenderPos.x +100, m_vecRenderPos.y+ WINSIZEY);
	
	RENDER->FillRect(m_vecRenderPos.x + 325, m_vecRenderPos.y +11, m_vecRenderPos.x +345, m_vecRenderPos.y +22 , Color(0,0,0,1));
	
	RENDER->Text(L"RETRY",m_vecRenderPos.x+50 , m_vecRenderPos.y+WINSIZEY-150, m_vecRenderPos.x + 100, m_vecRenderPos.y + WINSIZEY -100);
	
}

void CScreenUI::Release()
{
}

void CScreenUI::OnMouseEnter()
{
}

void CScreenUI::OnMouseOver()
{
}

void CScreenUI::OnMouseExit()
{
}

void CScreenUI::OnMouseUp()
{
}

void CScreenUI::OnMouseDown()
{
}

void CScreenUI::OnMouseClicked()
{
}