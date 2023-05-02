#include "framework.h"
#include "CSceneStage02.h"

#include "WinAPI.h"

#include "CPlayer.h"
#include "MonsterList.h"
#include "CGotoNextArea.h"
#include "CCameraController.h"
#include "CMaps.h"

#include "CButton.h"
#include "CPanel.h"
#include "CScreenUI.h"
#include"CSceneStage01.h"

//extern CPlayer* pPlayer;
CSceneStage02::CSceneStage02()
{
	pPlayer = nullptr;
	map = nullptr;
	pSound = nullptr;
}

CSceneStage02::~CSceneStage02()
{
}

void CSceneStage02::Init()
{
	
	pPlayer = new CPlayer();
	
	pPlayer->SetPos(70, 188);
	pPlayer->SetScale(pPlayer->GetScale() * 2);
	pPlayer->SetResetPos(Vector(70, 188));
	AddGameObject(pPlayer);

	CMonster* pMonster = new CMonster();
	pMonster->SetPos(1000, WINSIZEY * 0.5f);
	AddGameObject(pMonster);
	//������m_vecPos	{x=430.901184 y=212 }	Vector
	//�ͷ�m_vecPos	{x=178.778824 y=756 }	Vector
	//�̻��Ϻ� m_vecPos	{x=302.648193 y=1140.00000 }	Vector
	//�ͷ� m_vecPos	{x=146.118622 y=1364.00000 }	Vector
	//������ m_vecPos	{x=558.874390 y=1844.00000 }	Vector
	//���ĸ� m_vecPos	{x=843.119934 y=1607.57898 }	Vector
	//�ͷ� +		m_vecPos	{x=1630.31372 y=1748.00000 }	Vector
	//������ +		m_vecPos	{x=1392.38245 y=1684.00000 }	Vector 
	//���ĸ� +		m_vecPos	{x=2319.97656 y=1606.08130 }	Vector
	// �ͷ�+		m_vecPos	{x=2240.14795 y=1844.00000 }	Vector
	// �̻��Ϻ�+		m_vecPos	{x=2471.73340 y=2324.00000 }	Vector
	// 
	//

	CCameraController* pCamController = new CCameraController;
	CAMERA->SetTargetPos(pPlayer->GetPos());
	AddGameObject(pCamController);

	camScale = 1.f;
	//camScale = 2.5f;
	SideUI = new CScreenUI();
	SideUI->SetScreenFixed(true);
	SideUI->SetCamScale(camScale);
	AddGameObject(SideUI);

	CMaps* prevMaps = new CMaps();
	prevMaps->SetImage(RESOURCE->LoadImg(L"map_part1", L"Image\\MAP\\Map_part1_2x.png"));
	prevMaps->SetVecPos(Vector(-1.f*prevMaps->GetIamge()->GetWidth(),0));
	AddGameObject(prevMaps);

	map = new CMaps();
	map->SetImage(RESOURCE->LoadImg(L"map_part2", L"Image\\MAP\\Map_part2_2x.png"));
	AddGameObject(map);

	CMaps* nextMaps = new CMaps();
	nextMaps->SetImage(RESOURCE->LoadImg(L"map_part3", L"Image\\MAP\\Map_part3_BG.png"));
	nextMaps->SetVecPos(Vector(map->GetIamge()->GetWidth()-500.f, map->GetIamge()->GetHeight()));
	AddGameObject(nextMaps);


	goNext = new CGotoNextArea();
	goNext->SetPos(map->GetIamge()->GetWidth()*0.9f, map->GetIamge()->GetHeight()*0.9f );
	goNext->SetScale(500, 30);
	goNext->SetScene(GroupScene::Stage03);
	AddGameObject(goNext);

	pSound = RESOURCE->LoadSound(L"BGM", L"Sound\\Mighty Gunvolt Burst OST   Title Theme.mp3");;

}

void CSceneStage02::Enter()
{
	CAMERA->FadeIn(0.25f);
	if(PLAYERHP!=0)
	pPlayer->SetHP(PLAYERHP);
	pPlayer->SetPos(70, 188);
	LoadTileMapPos(GETPATH + L"Tile\\Stage02.tile", Vector(0, WINSIZEY * 0.5f));

	SOUND->Play(pSound, 1.5f, true);
}

void CSceneStage02::Update()
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
	Logger::Debug(L"�÷��̾� ����ü��:" + to_wstring(pPlayer->GetHP()));
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
