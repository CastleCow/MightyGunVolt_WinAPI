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
public:
	Vector GetPos() { return PlayerPos; }
	void SetPos(Vector a) { PlayerPos=a; }
};

#define GAME CGameManager::GetInstance()
#define PLAYERPOS CGameManager::GetInstance()->GetPos()