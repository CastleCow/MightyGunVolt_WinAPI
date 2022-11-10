#pragma once
#include "CScene.h"
class CPlayer;
class CMaps;
class CImage;

class CSceneStage02 :
	public CScene
{


public:
	CSceneStage02();
	virtual ~CSceneStage02();

private:
	CPlayer* pPlayer;
	CMaps* map;
	CImage* mapimg;
	float camScale = 1;
private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;


};

