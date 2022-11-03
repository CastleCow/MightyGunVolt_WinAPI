#include "framework.h"
#include "CInputManager.h"

#include "CCameraManager.h"
#include "CUIManager.h"
#include "WinAPI.h"

CInputManager::CInputManager()
{
	// Ű ���¸� ��� ������ ���� ���·� �ʱ�ȭ
	m_arrPrevKey[0] = { false };
	m_arrCurKey[0] = { false };
	m_vecMousePos = { 0, 0 };
}

CInputManager::~CInputManager()
{
}

void CInputManager::Init()
{
}

void CInputManager::Update()
{
	// ���� ����(Focus)�� �����찡 ���� �������ΰ��� Ȯ��
	if (hWnd != GetFocus())
	{
		// �����찡 ����(Focus)�� ���°� �ƴ� ��� Ű�Է��� ������Ŵ
		for (int key = 0; key < VKEY_SIZE; key++)
		{
			m_arrPrevKey[key] = m_arrCurKey[key];
			m_arrCurKey[key] = false;
		}
		return;
	}

	// ��� Ű �����ŭ �ݺ��ϸ� �Է»��¸� Ȯ��
	for (int key = 0; key < VKEY_SIZE; key++)
	{
		m_arrPrevKey[key] = m_arrCurKey[key];
		if (GetAsyncKeyState(key) & 0x8000)
		{
			m_arrCurKey[key] = true;
		}
		else
		{
			m_arrCurKey[key] = false;
		}
	}

	POINT point;
	// GetCursorPos() �����쿡�� ����� �»�� ���� ���콺�� ��ǥ�� ��ȯ
	GetCursorPos(&point);
	// ����� �»�� ���� ���콺 ��ǥ�� ���� ������ ���� ���콺 ��ġ�� ���
	ScreenToClient(hWnd, &point);
	m_vecMousePos = Vector((float)point.x, (float)point.y);
}

void CInputManager::Release()
{
}

bool CInputManager::GetButton(const int key)
{
	// Ű�� ������ �ִ� ��
	return (true == m_arrCurKey[key] && true == m_arrPrevKey[key]);
}

bool CInputManager::GetButtonUp(const int key)
{
	// Ű�� �ö� ����
	return (false == m_arrCurKey[key] && true == m_arrPrevKey[key]);
}

bool CInputManager::GetButtonDown(const int key)
{
	// Ű�� ������ ����
	return (true == m_arrCurKey[key] && false == m_arrPrevKey[key]);
}

Vector CInputManager::GetMouseScreenPos()
{
	return m_vecMousePos;
}

Vector CInputManager::GetMouseWorldPos()
{
	return CAMERA->ScreenToWorldPoint(m_vecMousePos);
}

bool CInputManager::GetMouseOnUI()
{
	return UI->GetMouseOnUI();
}

bool CInputManager::GetLMouse(bool ignoreUI)
{
	if (GetButton(VK_LBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}

bool CInputManager::GetLMouseUp(bool ignoreUI)
{
	if (GetButtonUp(VK_LBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}

bool CInputManager::GetLMouseDown(bool ignoreUI)
{
	if (GetButtonDown(VK_LBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}

bool CInputManager::GetRMouse(bool ignoreUI)
{
	if (GetButton(VK_RBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}

bool CInputManager::GetRMouseUp(bool ignoreUI)
{
	if (GetButtonUp(VK_RBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}

bool CInputManager::GetRMouseDown(bool ignoreUI)
{
	if (GetButtonDown(VK_RBUTTON))
	{
		if (ignoreUI) return true;
		else return !GetMouseOnUI();
	}
	else
		return false;
}
