#include "framework.h"
#include "CGameManager.h"

CGameManager::CGameManager()
{
	PlayerPos = Vector(0, 0);
}
CGameManager::~CGameManager()
{

}

void CGameManager::Init()
{

}
void CGameManager::Update()
{
	if (BUTTONDOWN(VK_F2))
	{
		if (m_debugMode == true)
			m_debugMode = false;
		else
			m_debugMode = true;
	}
	if (BUTTONDOWN(VK_F5))
	{
		SCENE->ChangeScene(GroupScene::Stage04);
	}
	UpTime += DT;
	if (UpTime >= 60)
	{
		min++;
		UpTime = 0;
	}
	Timer = to_wstring(min) + L":" + to_wstring((int)UpTime);
}
void CGameManager::Release()
{

}

