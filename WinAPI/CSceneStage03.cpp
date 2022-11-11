#include "framework.h"
#include "CSceneStage03.h"

#include "WinAPI.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CGotoNextArea.h"
#include "CCameraController.h"
#include "CMaps.h"

#include "CButton.h"
#include "CPanel.h"
#include "CScreenUI.h"

CSceneStage03::CSceneStage03()
{
	pPlayer = nullptr;
	map = nullptr;
}

CSceneStage03::~CSceneStage03()
{
}

void CSceneStage03::Init()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(100, 350);
	pPlayer->SetScale(pPlayer->GetScale() * 2);
	AddGameObject(pPlayer);

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(1000, WINSIZEY * 0.5f);
	AddGameObject(pMonster);

	CCameraController* pCamController = new CCameraController;
	CAMERA->SetTargetPos(pPlayer->GetPos(), 0.f);
	AddGameObject(pCamController);

	camScale = 1.f;
	//camScale = 2.5f;
	CScreenUI* SideUI = new CScreenUI();
	SideUI->SetScreenFixed(true);
	SideUI->SetCamScale(camScale);
	AddGameObject(SideUI);

	map = new CMaps();
	map->SetImage(RESOURCE->LoadImg(L"map_part1", L"Image\\MAP\\Map_part1_2x.png"));
	
	AddGameObject(map);

	CGotoNextArea* goNext = new CGotoNextArea();
	goNext->SetPos(map->GetIamge()->GetWidth()-100, map->GetIamge()->GetHeight() * 0.2f);
	goNext->SetScale(30, 200);
	goNext->SetScene(GroupScene::Stage02);
	AddGameObject(goNext);
}

void CSceneStage03::Enter()
{
	CAMERA->FadeIn(0.25f);

	//LoadTileMapPos(GETPATH + L"Tile\\Stage01.tile", Vector(0, WINSIZEY * 0.5f));
}

void CSceneStage03::Update()
{
}

void CSceneStage03::Render()
{
}

void CSceneStage03::Exit()
{
}

void CSceneStage03::Release()
{
}
