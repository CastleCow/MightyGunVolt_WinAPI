#include "framework.h"
#include "CSceneStage04.h"

#include "WinAPI.h"

#include "CPlayer.h"

#include "MonsterList.h"
#include "CGotoNextArea.h"
#include "CCameraController.h"
#include "CMaps.h"

#include "CButton.h"
#include "CPanel.h"
#include "CScreenUI.h"
#include "CImageObject.h"

CSceneStage04::CSceneStage04()
{
	pPlayer = nullptr;
	map = nullptr;
	pSound = nullptr;
}

CSceneStage04::~CSceneStage04()
{
}

void CSceneStage04::Init()
{
	pPlayer = new CPlayer();
	pPlayer->SetPos(150, 550);
	pPlayer->SetScale(pPlayer->GetScale() * 2);
	AddGameObject(pPlayer);


	cyro = new CMonsterWaterBoss;
	cyro->SetPos(WINSIZEX*0.8f, 350);
	AddGameObject(cyro);

	CCameraController* pCamController = new CCameraController;
	CAMERA->SetTargetPos(pPlayer->GetPos(), 0.f);
	AddGameObject(pCamController);

	camScale = 1.f;
	
	SideUI = new CScreenUI();
	SideUI->SetScreenFixed(true);
	SideUI->SetCamScale(camScale);
	AddGameObject(SideUI);

	map = new CMaps();
	map->SetImage(RESOURCE->LoadImg(L"map_part3_Boss", L"Image\\MAP\\Map_part3_Boss_2x.png"));
	AddGameObject(map);
	pSound = RESOURCE->LoadSound(L"BossBGM", L"Sound\\Mighty Gunvolt Burst OST  Boss Battle.mp3");;
	
	CImageObject* BossHp = new CImageObject();
	BossHp->SetImage(RESOURCE->LoadImg(L"BossHpBar", L"Image\\UI\\UI_BossHpbar.png"));
	BossHp->SetLayer(Layer::Map);
	BossHp->SetPos(Vector(WINSIZEX * 0.6f, WINSIZEY * 0.9f));
	BossHp->SetScale(Vector(2.f,2.f));
	AddGameObject(BossHp);
}

void CSceneStage04::Enter()
{
	CAMERA->FadeIn(0.25f);
	if(PLAYERHP!=0.f)
	pPlayer->SetHP(PLAYERHP);
	//pPlayer->SetPos(70, 188);
	LoadTile(GETPATH + L"Tile\\Stage04.tile");
	SOUND->Play(pSound,1.5f,true);
}

void CSceneStage04::Update()
{
	if (BUTTONDOWN(VK_ESCAPE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Title, 0.25f);
	}
	SideUI->SetHp(20 - pPlayer->GetHP());
	SideUI->SetMp(pPlayer->GetMp());
	//goNext->SetPHP(pPlayer->GetHP());
	CAMERA->SetTargetPos(Vector(WINSIZEX * 0.5f, WINSIZEY * 0.5f));
	CAMERA->ZoomInOut(camScale);
	//Logger::Debug(L"플레이어 현재체력:" + to_wstring(pPlayer->GetHP()));
}

void CSceneStage04::Render()
{
	RENDER->FillRect(WINSIZEX*0.65f,WINSIZEY*0.95f,WINSIZEX*0.65f+(30-cyro->GetBHP())*10,WINSIZEY*0.96f+10.f,Color(0,0,0,1));
}

void CSceneStage04::Exit()
{
}

void CSceneStage04::Release()
{
}
