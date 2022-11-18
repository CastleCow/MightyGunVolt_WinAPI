#pragma once
#include"WinAPI.h"

class CGameManager:public SingleTon<CGameManager>
{
	friend SingleTon<CGameManager>;
	friend CCore;
public:
	CGameManager();
	virtual ~CGameManager();


private:
	void Init();
	void Update();
	void Release();

	Vector PlayerPos;
	float PlayerHP;
	float UpTime=0;
	int min=0;
	wstring Timer=L"";
public:
	Vector GetPos() { return PlayerPos; }
	void SetPos(Vector a) { PlayerPos=a; }
	float GetPlayerHP() { return PlayerHP; }
	void SetPlayerHP(float a) { PlayerHP = a; }
	wstring GetTimer() { return Timer; }
	
};

#define GAME CGameManager::GetInstance()
#define PLAYERPOS CGameManager::GetInstance()->GetPos()
#define PLAYERHP CGameManager::GetInstance()->GetPlayerHP()
#define UPTIME CGameManager::GetInstance()->GetTimer()