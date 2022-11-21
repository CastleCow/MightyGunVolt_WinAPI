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
	Vector BossPos;
	Vector BossScale;

	bool m_debugMode = false;

	float UpTime=0;
	int min=0;
	wstring Timer=L"";
public:
	Vector GetPos() { return PlayerPos; }
	void SetPos(Vector a) { PlayerPos=a; }
	Vector GetBossPos() { return BossPos; }
	void SetBossPos(Vector a) {  BossPos=a; }
	Vector GetBossScale() { return BossScale; }
	void SetBossScale(Vector a) { BossScale = a; }
	float GetPlayerHP() { return PlayerHP; }
	void SetPlayerHP(float a) { PlayerHP = a; }
	wstring GetTimer() { return Timer; }

	bool GetDebug() { return m_debugMode; }
	//void SetDebug(bool a) { m_debugMode = a; }
	
};

#define GAME CGameManager::GetInstance()
#define PLAYERPOS CGameManager::GetInstance()->GetPos()
#define BOSSPOS CGameManager::GetInstance()->GetBossPos()
#define PLAYERHP CGameManager::GetInstance()->GetPlayerHP()
#define UPTIME CGameManager::GetInstance()->GetTimer()