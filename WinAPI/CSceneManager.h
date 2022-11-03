#pragma once
#include "WinAPI.h"

class CCore;
class CEventManager;
class CCollisionManager;
class CUIManager;
class CScene;

class CSceneManager : public SingleTon<CSceneManager>
{
	friend SingleTon<CSceneManager>;
	friend CCore;
	friend CEventManager;
	friend CCollisionManager;
	friend CUIManager;
private:
	CSceneManager();
	virtual ~CSceneManager();

	map<GroupScene, CScene*> m_mapScene;	// ���Ӿ����� �����ϴ� �ڷᱸ��
	CScene* m_pCurScene;					// ���� ���Ӿ�

	void Init();
	void Update();
	void Render();
	void Release();

public:
	CScene* GetCurScene();					// ���� ���Ӿ� ��ȯ
	void ChangeScene(GroupScene scene);		// ���Ӿ� ����
};

#define SCENE				CSceneManager::GetInstance()