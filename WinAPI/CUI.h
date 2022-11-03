#pragma once
#include "CGameObject.h"

class CUIManager;

class CUI : public CGameObject
{
	friend CUIManager;
public:
	CUI();
	virtual ~CUI();

protected:
	list<CUI*>	m_listChildUI;		// �ڽ� UI���� ������ �ڷᱸ��
	CUI*		m_pParentUI;		// �θ� UI

	// Vector	m_vecPos;			// �θ� ���������� ��� ��ġ
	Vector		m_vecAbsolutePos;	// ���ӿ����� ���� ��ġ
	Vector		m_vecRenderPos;		// ���ӿ����� �׷��� ��ġ
	bool		m_bScreenFixed;		// ȭ�� ���� ����

	bool		m_bPrevMouseOn;		// UI�� ���� �����ӿ� ���콺�� �÷��� ����
	bool		m_bCurMouseOn;		// UI�� ���� �����ӿ� ���콺�� �÷��� ����
	bool		m_bPrevDown;		// UI�� ���� �����ӿ� ���ȴ��� ����
	bool		m_bCurDown;			// UI�� ���� �����ӿ� ���ȴ��� ����

public:
	CUI* GetParentUI();
	void AddChildUI(CUI* pChildUI);

	bool GetScreenFixed();
	void SetScreenFixed(bool fixed);

protected:
	void MouseOnCheck();

private:
	// UI �θ� ���� �Լ��� :
	// UI�� �ִ� ��� �ڽ� UI�� ����
	void GameObjectInit() override;
	void GameObjectUpdate() override;
	void GameObjectRender() override;
	void GameObjectRelease() override;

	// UI�� ���콺 �̺�Ʈ �������Ͽ� ��� ����
	virtual void OnMouseEnter() = 0;
	virtual void OnMouseOver() = 0;
	virtual void OnMouseExit() = 0;
	virtual void OnMouseUp() = 0;
	virtual void OnMouseDown() = 0;
	virtual void OnMouseClicked() = 0;
};

