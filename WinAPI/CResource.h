#pragma once

// ���ҽ� : ���ӿ� �ʿ��� �ڵ� ���� �ڿ�
// ex) �̹���, ����, ��
class CResource
{
public:
	CResource();
	virtual ~CResource();

protected:
	wstring m_strKey;		// ���ҽ��� Ž���� Ű
	wstring m_strPath;		// ���ҽ��� ���

public:
	void SetKey(const wstring& key);
	void SetPath(const wstring& path);

public:
	const wstring& GetKey();
	const wstring& GetPath();
};
