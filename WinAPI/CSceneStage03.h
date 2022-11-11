#pragma once
#include "CScene.h"

class CPlayer;
class CMaps;
class CImage;

class CSceneStage03 :
	public CScene
{

public:
	CSceneStage03();
	virtual ~CSceneStage03();

private:
	CPlayer* pPlayer;
	CMaps* map;

	float camScale = 1;
private:
	void Init()		override;
	void Enter()	override;
	void Update()	override;
	void Render()	override;
	void Exit()		override;
	void Release()	override;


};

