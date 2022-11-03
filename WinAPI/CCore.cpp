#include "framework.h"
#include "CCore.h"
#include "WinAPI.h"

#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CInputManager.h"
#include "CSceneManager.h"
#include "CEventManager.h"
#include "CCollisionManager.h"
#include "CPathManager.h"
#include "CResourceManager.h"
#include "CCameraManager.h"
#include "CUIManager.h"
#include "CSoundManager.h"

CCore::CCore()
{

}

CCore::~CCore()
{

}

void CCore::Init()
{
	TIME->Init();
	RENDER->Init();
	INPUT->Init();
	EVENT->Init();
	COLLISION->Init();
	PATH->Init();
	RESOURCE->Init();
	CAMERA->Init();
	UI->Init();
	SOUND->Init();

	SCENE->Init();
}

void CCore::Update()
{
	// ���� �����ӿ��� �߰��� �̺�Ʈ�� ������ �ʱ⿡ �Ѳ����� ó��
	EVENT->Update();

	TIME->Update();
	INPUT->Update();
	SCENE->Update();
	CAMERA->Update();
	UI->Update();
	SOUND->Update();

	// ���� ������Ʈ���� ������Ʈ �� �� �浹ó�� ����
	COLLISION->Update();
}

void CCore::Render()
{
	RENDER->BeginDraw();

	//// ���� ǥ�� ����
	SCENE->Render();
	CAMERA->Render();

	//// ���ܿ� ���� ����FPS ��� (60������ �̻��� ��ǥ�� ����ȭ �ؾ���)
	Vector framePos = CAMERA->ScreenToWorldPoint(Vector(WINSIZEX - 50, 20));
	wstring frame = to_wstring(FPS);
	RENDER->Text(frame, framePos.x - 50, framePos.y - 10, framePos.x + 50, framePos.y + 10, Color(0, 0, 0, 1.f), 15);

	RENDER->EndDraw();
}

void CCore::Release()
{
	SCENE->Release();

	TIME->Release();
	RENDER->Release();
	INPUT->Release();
	EVENT->Release();
	COLLISION->Release();
	PATH->Release();
	RESOURCE->Release();
	CAMERA->Release();
	UI->Release();
	SOUND->Release();
}
