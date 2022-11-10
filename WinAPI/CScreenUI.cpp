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
	camScale = 1;
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
	UpTime += DT;
	if (UpTime >= 60)
	{
		min++;
		UpTime = 0;
	}
	Timer = to_wstring(min) + L":" + to_wstring((int)UpTime);

}

void CScreenUI::Render()
{
	
	
	RENDER->Image(m_Hpbar, (m_vecRenderPos.x + 100),
		(m_vecRenderPos.y),
		(m_vecRenderPos.x + 100 + WINSIZEX * 0.2f),
		(m_vecRenderPos.y + WINSIZEY * 0.1f) );
	RENDER->Image(m_PIcon, (m_vecRenderPos.x + 110) , (m_vecRenderPos.y + 10) ,
							(m_vecRenderPos.x + 160) , (m_vecRenderPos.y + 62) );
	RENDER->Image(m_SideBar, (m_vecRenderPos.x - 104) , (m_vecRenderPos.y) ,
		(m_vecRenderPos.x + 104) , (m_vecRenderPos.y + WINSIZEY) );
	RENDER->Image(m_SideBar, WINSIZEX+m_vecRenderPos.x-100, m_vecRenderPos.y,WINSIZEX+ m_vecRenderPos.x +100, m_vecRenderPos.y+ WINSIZEY);
	
	RENDER->FillRect(m_vecRenderPos.x + 325, m_vecRenderPos.y +11, m_vecRenderPos.x +345, m_vecRenderPos.y +22 , Color(0,0,0,1));
	
	
	RENDER->Text(L"RETRY",m_vecRenderPos.x+30 , m_vecRenderPos.y+WINSIZEY-150, m_vecRenderPos.x + 100, m_vecRenderPos.y + WINSIZEY -60,Color(0,255,0,1));
	RENDER->Text(to_wstring(RetryCount),m_vecRenderPos.x+30 , m_vecRenderPos.y+WINSIZEY-130, m_vecRenderPos.x + 100, m_vecRenderPos.y + WINSIZEY -40,Color(0,255,0,1));
	RENDER->Text(L"TIME",m_vecRenderPos.x+WINSIZEX-130 , m_vecRenderPos.y+WINSIZEY-150, m_vecRenderPos.x+WINSIZEX - 30, m_vecRenderPos.y + WINSIZEY -60,Color(0,255,0,1));
	RENDER->Text(Timer, m_vecRenderPos.x + WINSIZEX - 130, m_vecRenderPos.y + WINSIZEY - 130, m_vecRenderPos.x + WINSIZEX - 30, m_vecRenderPos.y + WINSIZEY - 40, Color(0, 255, 0, 1));
	
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
