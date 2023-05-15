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
	pPlayer->SetPos(750, 350);
	pPlayer->SetScale(pPlayer->GetScale() * 2);
	AddGameObject(pPlayer);

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(1500, WINSIZEY * 0.5f);
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
	map->SetImage(RESOURCE->LoadImg(L"map_part3_front", L"Image\\MAP\\Map_part3_fix_2x.png"));
	
	back1 = new CMaps();
	back1->SetImage(RESOURCE->LoadImg(L"map_part3_Back1", L"Image\\MAP\\Map_part3_BG_2x.png"));
	back1->SetVecPos(map->GetVecPos());
	back1->SetVecPos(Vector(back1->GetVecPos().x, back1->GetVecPos().y+27));

	AddGameObject(back1);
	back2 = new CMaps();
	back2->SetImage(RESOURCE->LoadImg(L"map_part3_Back2", L"Image\\MAP\\Map_part3_BG_2x.png"));
	back2->SetVecPos(Vector(back1->GetVecPos().x+3000, back1->GetVecPos().y));
	AddGameObject(back2);

	AddGameObject(map);



	goNext = new CGotoNextArea();
	goNext->SetPos(map->GetIamge()->GetWidth()-100, map->GetIamge()->GetHeight());
	goNext->SetScale(30, 200);
	goNext->SetScene(GroupScene::Stage04);
	AddGameObject(goNext);
	pSound = RESOURCE->LoadSound(L"BGM", L"Sound\\Mighty Gunvolt Burst OST   Title Theme.mp3");;

}

void CSceneStage03::Enter()
{
	CAMERA->FadeIn(0.25f);
	pPlayer->SetHP(PLAYERHP);
	//pPlayer->SetPos(70, 188);
	LoadTile(GETPATH + L"Tile\\Stage03.tile");
	SOUND->Play(pSound,1.5f,true);
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
	back1->SetVecPos(Vector(back1->GetVecPos().x-100*DT, back1->GetVecPos().y));
	if (back1->GetVecPos().x < pPlayer->GetPos().x -5000)
		back1->SetVecPos(Vector(pPlayer->GetPos().x, 0));
	back2->SetVecPos(Vector(back2->GetVecPos().x - 100 * DT, back2->GetVecPos().y));
	if (back2->GetVecPos().x < pPlayer->GetPos().x -5000)
		back2->SetVecPos(Vector(pPlayer->GetPos().x, 0));
}

void CSceneStage03::Render()
{
	//RENDER->Image(RESOURCE->LoadImg(L"LOGO", L"Image\\Map_part3_BG_2x.png",));
}

void CSceneStage03::Exit()
{
}

void CSceneStage03::Release()
{
}
