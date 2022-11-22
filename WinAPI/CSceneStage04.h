#pragma once
#include "CScene.h"

class CPlayer;
class CMaps;
class CImage;
class CScreenUI;
class CGotoNextArea;
class CSceneStage04 :
	public CScene
{

public:
	CSceneStage04();
	virtual ~CSceneStage04();

private:
	CPlayer* pPlayer;
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

