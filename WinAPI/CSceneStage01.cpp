#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"
#include "CInputManager.h"
#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"
#include "CPathManager.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCameraController.h"
#include"CMaps.h"

#include "CButton.h"
#include "CPanel.h"

CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	map = nullptr;
	
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(200, WINSIZEY * 0.5f);
	AddGameObject(pPlayer);

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(1000, WINSIZEY * 0.5f);
	AddGameObject(pMonster);

	CCameraController* pCamController = new CCameraController;
	
	AddGameObject(pCamController);

	map = new CMaps();
	map->SetImage(RESOURCE->LoadImg(L"map_part1", L"Image\\MAP\\Map_part1.png"));
	AddGameObject(map);
}

void CSceneStage01::Enter()
{
	CAMERA->FadeIn(0.25f);
	LoadTile(GETPATH + L"Tile\\Stage01.tile");

	RESOURCE->LoadImg(L"map_part1", L"Image\\MAP\\Map_part1.png");
}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}
}

void CSceneStage01::Render()
{
	
	//RENDER->Image(map,0,0,map->GetWidth(),map->GetHeight());
	
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
