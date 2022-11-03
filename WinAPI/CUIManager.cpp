#include "framework.h"
#include "CUIManager.h"

#include "CSceneManager.h"
#include "CInputManager.h"

#include "CScene.h"
#include "CUI.h"

CUIManager::CUIManager()
{
	m_pFocusedUI = nullptr;
	m_pMouseOnUI = false;
}

CUIManager::~CUIManager()
{
}

CUI* CUIManager::GetTopUI()
{
	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& listUI = pCurScene->m_listObj[(int)Layer::Ui];

	// ���� ���� �ִ� UI�� ���� ���ӿ�����Ʈ �ڷᱸ������ ���ʴ�� ��ȸ�ϸ� Render �Ѵٴ� ���� �̿��Ͽ�
	// ���� �������� �ִ� ���ӿ�����Ʈ�� ���� ���� �ִ� ���ӿ�����Ʈ
	// ������ �ݺ��� : ���� ���� ��Һ��� �������� ��ȸ
	for (auto iter = listUI.rbegin(); iter != listUI.rend(); iter++)
	{
		// �������� ��ȸ �� ������� ���콺�� �÷��� �ִ� UI�� ���콺 Ŭ���� ���
		CUI* pUI = static_cast<CUI*>(*iter);
		if (pUI->m_bCurMouseOn)
		{
			return pUI;
		}
	}

	return nullptr;
}

CUI* CUIManager::GetTopChildUI(CUI* pUI)
{
	if (nullptr == pUI)
		return nullptr;

	queue<CUI*> queueUI;
	CUI* pTargetUI = nullptr;

	// BFS �� ���ؼ� UI�� ���콺�� �ö� ���� �ڽ� UI Ȯ��
	queueUI.push(pUI);
	while (!queueUI.empty())
	{
		CUI* pUI = queueUI.front();
		queueUI.pop();

		if (pUI->m_bCurMouseOn)
		{
			pTargetUI = pUI;
		}

		for (CUI* pChildUI : pUI->m_listChildUI)
		{
			queueUI.push(pChildUI);
		}
	}

	return pTargetUI;
}

void CUIManager::MouseEvent(CUI* pUI, CUI* pTopChildUI)
{
	if (pUI->m_bCurMouseOn && pUI == pTopChildUI)
	{
		pUI->OnMouseOver();
		if (!pUI->m_bPrevMouseOn)
		{
			pUI->OnMouseEnter();
			pUI->m_bPrevMouseOn = true;
		}

		if (BUTTONDOWN(VK_LBUTTON))
		{
			pUI->OnMouseDown();
			pUI->m_bPrevDown = true;
		}
		else if (BUTTONUP(VK_LBUTTON))
		{
			pUI->OnMouseUp();

			if (pUI->m_bPrevDown)
			{
				pUI->OnMouseClicked();
			}
			pUI->m_bPrevDown = false;
		}
	}
	else
	{
		if (pUI->m_bPrevMouseOn)
		{
			pUI->OnMouseExit();
			pUI->m_bPrevMouseOn = false;
		}
		if (BUTTONUP(VK_LBUTTON))
		{
			pUI->m_bPrevDown = false;
		}
	}

	for (CUI* pChildUI : pUI->m_listChildUI)
	{
		MouseEvent(pChildUI, pTopChildUI);
	}

	for (CUI* pChildUI : pUI->m_listChildUI)
	{
		MouseEvent(pChildUI, pTopChildUI);
	}
}

CUI* CUIManager::GetFocusedUI()
{
	return m_pFocusedUI;
}

void CUIManager::SetFocusedUI(CUI* pUI)
{
	// �̹� ��Ŀ�̵� UI�� ��� �������� ����
	if (m_pFocusedUI == pUI)
		return;

	// ��Ŀ���� nullptr�� ������ ��� ��Ŀ�� UI �� nullptr�� ����
	if (nullptr == pUI)
	{
		m_pFocusedUI = nullptr;
		return;
	}

	m_pFocusedUI = pUI;

	// ��Ŀ�̵� UI�� �ֻ�ܿ� ��ġ�ϵ��� �ڷᱸ���� ���� �ڿ� ��ġ
	CScene* pCurScene = SCENE->GetCurScene();
	list<CGameObject*>& listUI = pCurScene->m_listObj[(int)Layer::Ui];

	listUI.remove(pUI);
	listUI.push_back(pUI);
}

bool CUIManager::GetMouseOnUI()
{
	return m_pMouseOnUI;
}

void CUIManager::Init()
{
}

void CUIManager::Update()
{
	CUI* pTopUI = GetTopUI();
	CUI* pTopChildUI = GetTopChildUI(pTopUI);

	m_pMouseOnUI = nullptr != pTopUI;

	if (BUTTONDOWN(VK_LBUTTON))
		SetFocusedUI(pTopUI);

	CScene* pCurScene = SCENE->GetCurScene();
	const list<CGameObject*>& listUI = pCurScene->m_listObj[(int)Layer::Ui];

	for (CGameObject* pGameObject : listUI)
	{
		CUI* pUI = dynamic_cast<CUI*>(pGameObject);
		MouseEvent(pUI, pTopChildUI);
	}
}

void CUIManager::Release()
{
}
