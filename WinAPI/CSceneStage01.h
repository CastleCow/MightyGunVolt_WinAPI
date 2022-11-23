#pragma once
#include "CScene.h"

class CPlayer;
class CMaps;
class CImage;
class CSound;
class CScreenUI;
class CGotoNextArea;

class CSceneStage01 : public CScene
{
public:
	CSceneStage01();
	virtual ~CSceneStage01();

	
private:
	CPlayer* pPlayer;
	CSound* pSound;
	CMaps* map;
	CScreenUI* SideUI;
	CGotoNextArea* goNext;
	float camScale = 1;
private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;
};
