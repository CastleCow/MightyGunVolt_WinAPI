#pragma once

class CCore;

class CInputManager : public SingleTon<CInputManager>
{
	friend SingleTon<CInputManager>;
	friend CCore;
private:
	CInputManager();
	virtual ~CInputManager();

	static const int VKEY_SIZE = 0xFF;	// VK�� �ִ� ����

	bool m_arrPrevKey[VKEY_SIZE];		// ���� Ű�� �Է»���
	bool m_arrCurKey[VKEY_SIZE];		// ���� Ű�� �Է»���
	Vector m_vecMousePos;				// ���� ���콺 ��ġ

	void Init();
	void Update();
	void Release();

public:

	bool GetButton(const int key);		// Ű�� ������ �ִ� ��
	bool GetButtonUp(const int key);	// Ű�� �ö� ����
	bool GetButtonDown(const int key);	// Ű�� ������ ����
	Vector GetMouseScreenPos();			// ���� ���콺 ȭ����ġ
	Vector GetMouseWorldPos();			// ���� ���콺 ������ġ

	bool GetMouseOnUI();				// ���� ���콺�� UI���� �ִ� ���� Ȯ��
	bool GetLMouse(bool ignoreUI);		// ���콺 ���� Ű�� ������ �ִ� ��
	bool GetLMouseUp(bool ignoreUI);	// ���콺 ���� Ű�� �ö� ����
	bool GetLMouseDown(bool ignoreUI);	// ���콺 ���� Ű�� ������ ����
	bool GetRMouse(bool ignoreUI);		// ���콺 ������ Ű�� ������ �ִ� ��
	bool GetRMouseUp(bool ignoreUI);	// ���콺 ������ Ű�� �ö� ����
	bool GetRMouseDown(bool ignoreUI);	// ���콺 ������ Ű�� ������ ����
};

#define	INPUT					CInputManager::GetInstance()
#define BUTTONSTAY(key)			CInputManager::GetInstance()->GetButton(key)
#define BUTTONUP(key)			CInputManager::GetInstance()->GetButtonUp(key)	
#define BUTTONDOWN(key)			CInputManager::GetInstance()->GetButtonDown(key)	
#define MOUSESCREENPOS			CInputManager::GetInstance()->GetMouseScreenPos()
#define MOUSEWORLDPOS			CInputManager::GetInstance()->GetMouseWorldPos()
#define LMOUSESTAY(ignoreUI)	CInputManager::GetInstance()->GetLMouse(ignoreUI)
#define LMOUSEUP(ignoreUI)		CInputManager::GetInstance()->GetLMouseUp(ignoreUI)
#define LMOUSEDOWN(ignoreUI)	CInputManager::GetInstance()->GetLMouseDown(ignoreUI)
#define RMOUSESTAY(ignoreUI)	CInputManager::GetInstance()->GetRMouse(ignoreUI)
#define RMOUSEUP(ignoreUI)		CInputManager::GetInstance()->GetRMouseUp(ignoreUI)
#define RMOUSEDOWN(ignoreUI)	CInputManager::GetInstance()->GetRMouseDown(ignoreUI)