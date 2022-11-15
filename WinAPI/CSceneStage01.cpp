#include "framework.h"
#include "CSceneStage01.h"

#include "WinAPI.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CGotoNextArea.h"
#include "CCameraController.h"
#include "CMaps.h"

#include "CButton.h"
#include "CPanel.h"
#include "CScreenUI.h"



CSceneStage01::CSceneStage01()
{
	pPlayer = nullptr;
	map = nullptr;
	SideUI = nullptr;
	
}

CSceneStage01::~CSceneStage01()
{
}

void CSceneStage01::Init()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(100, 350);
	pPlayer->SetScale(pPlayer->GetScale()*2);
	AddGameObject(pPlayer);
	
	CMonster* pMonster = new CMonster();
	pMonster->SetPos(1000, WINSIZEY * 0.5f);
	AddGameObject(pMonster);

	CCameraController* pCamController = new CCameraController;
	CAMERA->SetTargetPos(pPlayer->GetPos(), 0.f);
	AddGameObject(pCamController);

	camScale = 1.f;
	//camScale = 2.5f;
	SideUI=new CScreenUI();
	SideUI->SetScreenFixed(true);
	SideUI->SetCamScale(camScale);
	AddGameObject(SideUI);

	map = new CMaps();
	map->SetImage(RESOURCE->LoadImg(L"map_part1", L"Image\\MAP\\Map_part1_2x.png"));
	map->SetNextMapImage(RESOURCE->LoadImg(L"map_part2", L"Image\\MAP\\Map_part2_2x.png"));
	AddGameObject(map);

	CGotoNextArea* goNext = new CGotoNextArea();
	goNext->SetPos(map->GetIamge()->GetWidth(), map->GetIamge()->GetHeight()*0.2f);
	goNext->SetScale(30,500);
	goNext->SetScene(GroupScene::Stage02);
   	AddGameObject(goNext);
}

void CSceneStage01::Enter()
{
	CAMERA->FadeIn(0.25f);
	
	LoadTile(GETPATH + L"Tile\\Stage01.tile");
	

	
}

void CSceneStage01::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}
	SideUI->SetHp(20-pPlayer->GetHP());
	SideUI->SetMp(pPlayer->GetMp());
	CAMERA->SetTargetPos(pPlayer->GetPos(), 0.5f);
	CAMERA->ZoomInOut(camScale);
	Logger::Debug(L"플레이어 현재체력:" + to_wstring(pPlayer->GetHP()));
}

void CSceneStage01::Render()
{
	//CImage* temp = RESOURCE->LoadImg(L"SparkCaliber", L"Image\\Player\\SparkCaliber.png");
	//RENDER->Image(temp,pPlayer->GetPos().x+50.f, pPlayer->GetPos().y-70.f, pPlayer->GetPos().x+50.f+ temp->GetWidth(), pPlayer->GetPos().y-70.f+ temp->GetHeight());
	
}

void CSceneStage01::Exit()
{
}

void CSceneStage01::Release()
{
}
