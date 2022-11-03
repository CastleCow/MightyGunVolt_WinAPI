#include "framework.h"
#include "CEventManager.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CGameObject.h"

#include "CTimeManager.h"

CEventManager::CEventManager()
{
	m_pChangeScene = nullptr;
}

CEventManager::~CEventManager()
{
}

void CEventManager::Init()
{
}

void CEventManager::Update()
{
	ProgressAddObject();
	ProgressDeleteObject();

	// �� ��ȯ�� �ٸ� �̺�Ʈ���� ���� �������� ����
	ProgressChangeScene();
}

void CEventManager::Release()
{
}

void CEventManager::EventAddObject(CGameObject* pObj)
{
	// ���� �����ӿ� �߰��� ���ӿ�����Ʈ�� �ڷᱸ���� ����
	m_queueAddObject.push(pObj);
}

void CEventManager::EventDeleteObject(CGameObject* pObj)
{
	// ���� ������ ���ӿ�����Ʈ�� �ڷᱸ���� ����
	m_queueDeleteObject.push(pObj);
}

void CEventManager::EventChangeScene(GroupScene scene, float delay)
{
	// �� ��ȯ �̺�Ʈ�� �ڷᱸ���� ����
	if (nullptr == m_pChangeScene)
	{
		m_pChangeScene = new pair<GroupScene, float>(scene, delay);
	}
	else if (m_pChangeScene->second > delay)
	{
		delete m_pChangeScene;
		m_pChangeScene = new pair<GroupScene, float>(scene, delay);
	}
	else
	{
		// �����̰� ���� ū ����ȯ �̺�Ʈ�� ����
	}
}

void CEventManager::ProgressAddObject()
{
	// �������� �ʱ⿡ �߰��� ���ӿ�����Ʈ�� �߰�

	while (!m_queueAddObject.empty())
	{
		CGameObject* pGameObject = m_queueAddObject.front();
		m_queueAddObject.pop();
		SCENE->GetCurScene()->AddGameObject(pGameObject);
	}
}

void CEventManager::ProgressDeleteObject()
{
	// ���� ������ ���ӿ�����Ʈ�� �������� ǥ�ø� ����

	while (!m_queueDeleteObject.empty())
	{
		CGameObject* pGameObject = m_queueDeleteObject.front();
		m_queueDeleteObject.pop();
		pGameObject->SetReserveDelete();
	}
}

void CEventManager::ProgressChangeScene()
{
	// ����� �� ��ȯ �̺�Ʈ �� ���� �������� �̺�Ʈ�� ����

	if (nullptr == m_pChangeScene)
		return;

	// �������� �̺�Ʈ�� �ܿ��ð��� ��� �����Ǿ��� ��� �̺�Ʈ ����
	m_pChangeScene->second -= DT;
	if (m_pChangeScene->second <= 0)
	{
		GroupScene scene = m_pChangeScene->first;
		delete m_pChangeScene;
		m_pChangeScene = nullptr;
		SCENE->ChangeScene(scene);
	}
}
