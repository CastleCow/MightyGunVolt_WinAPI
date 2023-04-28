#include "framework.h"
#include "CSceneStage03.h"

#include "WinAPI.h"

#include "CPlayer.h"
#include "MonsterList.h"
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
	pSound = nullptr;
}

CSceneStage03::~CSceneStage03()
{
}

void CSceneStage03::Init()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(200, 350);
	pPlayer->SetScale(pPlayer->GetScale() * 2);
	AddGameObject(pPlayer);

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(1000, WINSIZEY * 0.5f);
	AddGameObject(pMonster);

	CCameraController* pCamController = new CCameraController;
	CAMERA->SetTargetPos(pPlayer->GetPos(), 0.f);
	AddGameObject(pCamController);

	camScale = 1.f;
	
	SideUI = new CScreenUI();
	SideUI->SetScreenFixed(true);
	SideUI->SetCamScale(camScale);
	AddGameObject(SideUI);

	map = new CMaps();
	map->SetImage(RESOURCE->LoadImg(L"map_part3", L"Image\\MAP\\Map_part3_2x.png"));
	AddGameObject(map);




	goNext = new CGotoNextArea();
	goNext->SetPos(map->GetIamge()->GetWidth()-100, map->GetIamge()->GetHeight() * 0.2f);
	goNext->SetScale(30, 200);
	goNext->SetScene(GroupScene::Stage02);
	AddGameObject(goNext);
	pSound = RESOURCE->LoadSound(L"BGM", L"Sound\\Mighty_Gunvolt_Burst_OST_TitleTheme.mp3");;

}

void CSceneStage03::Enter()
{
	CAMERA->FadeIn(0.25f);
	pPlayer->SetHP(PLAYERHP);
	pPlayer->SetPos(70, 188);
	LoadTile(GETPATH + L"Tile\\Stage03.tile");
	SOUND->Play(pSound,1.5f);
}

void CSceneStage03::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}
	SideUI->SetHp(20 - pPlayer->GetHP());
	SideUI->SetMp(pPlayer->GetMp());
	goNext->SetPHP(pPlayer->GetHP());
	CAMERA->SetTargetPos(pPlayer->GetPos(), 0.5f);
	CAMERA->ZoomInOut(camScale);
	Logger::Debug(L"플레이어 현재체력:" + to_wstring(pPlayer->GetHP()));
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
