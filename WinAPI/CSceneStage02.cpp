#include "framework.h"
#include "CSceneStage02.h"

#include "WinAPI.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCameraController.h"
#include "CMaps.h"

#include "CButton.h"
#include "CPanel.h"
#include "CScreenUI.h"

CSceneStage02::CSceneStage02()
{
	pPlayer = nullptr;
	map = nullptr;

}

CSceneStage02::~CSceneStage02()
{
}

void CSceneStage02::Init()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(70, 188);
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
	map->SetImage(RESOURCE->LoadImg(L"map_part2", L"Image\\MAP\\Map_part2_2x.png"));
	AddGameObject(map);
}

void CSceneStage02::Enter()
{
	CAMERA->FadeIn(0.25f);

	LoadTileMapPos(GETPATH + L"Tile\\Stage02.tile", Vector(0, WINSIZEY * 0.5f));

}

void CSceneStage02::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}
	if(pPlayer->GetPos().x < map->GetPos().x * 0.9f &&pPlayer->GetPos().x>map->GetPos().x*0.1f)
	CAMERA->SetTargetPos(pPlayer->GetPos(), 0.5f);
	CAMERA->ZoomInOut(camScale);
}

void CSceneStage02::Render()
{
}

void CSceneStage02::Exit()
{
}

void CSceneStage02::Release()
{
}
