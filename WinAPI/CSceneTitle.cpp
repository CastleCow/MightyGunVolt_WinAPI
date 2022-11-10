#include "framework.h"
#include "CSceneTitle.h"

#include "WinAPI.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CEventManager.h"
#include "CCameraManager.h"

CSceneTitle::CSceneTitle()
{
}

CSceneTitle::~CSceneTitle()
{
}

void CSceneTitle::Init()
{
}

void CSceneTitle::Enter()
{
	CAMERA->FadeIn(0.25f);
}

void CSceneTitle::Update()
{
	Timer += DT;
	if (Timer > 2.f) {
		blink = Color(0, 0, 0, 1);
		Timer = 0;
	}
	else if (Timer > 1.f)
	{
		blink = Color(255, 255, 255, 1);
		
	}
	if (BUTTONDOWN(VK_F1))
	{
		CHANGESCENE(GroupScene::TileTool);
	}
	if (BUTTONDOWN(VK_SPACE))
	{
		CAMERA->FadeOut(0.25f);
		DELAYCHANGESCENE(GroupScene::Stage01, 0.25f);
	}
}

void CSceneTitle::Render()
{

	RENDER->Image(RESOURCE->LoadImg(L"LOGO",L"Image\\LOGO.png"),
		WINSIZEX * 0.33f - 100,
		WINSIZEY * 0.5f - 100,
		WINSIZEX * 0.63f + 100,
		WINSIZEY * 0.5f + 100);

	RENDER->Text(L"press space to start",
		WINSIZEX * 0.5f - 100,
		WINSIZEY * 0.7f - 10,
		WINSIZEX * 0.5f + 100,
		WINSIZEY * 0.7f + 10,
		blink,
		20.f);
}

void CSceneTitle::Exit()
{
}

void CSceneTitle::Release()
{
}
