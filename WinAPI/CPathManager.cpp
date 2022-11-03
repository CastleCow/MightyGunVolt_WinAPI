#include "framework.h"
#include "CPathManager.h"

CPathManager::CPathManager()
{
}

CPathManager::~CPathManager()
{
}

void CPathManager::Init()
{
	WCHAR path[255] = {};				// ��θ� �ޱ� ���� ���ڿ�
	GetCurrentDirectory(255, path);		// ���� ��θ� Ȯ��
	m_strPath = wstring(path);			// ���ڿ��� wstring ���� ��ȯ
	m_strPath += L"\\Resource\\";		// ��εڿ� ���ҽ� ������ �߰�

	Logger::Debug(L"���� ���");
	Logger::Debug(m_strPath);
}

void CPathManager::Release()
{
}

const wstring& CPathManager::GetPath()
{
	return m_strPath;
}
