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

