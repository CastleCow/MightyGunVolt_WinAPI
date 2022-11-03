#pragma once

class CAnimator;
class CImage;

struct AniFrame
{
	Vector	lt;
	Vector	slice;
	float	duration;
};

class CAnimation
{
	friend CAnimator;
public:
	CAnimation();
	virtual ~CAnimation();

private:
	CAnimator*			m_pAnimator;	// �ִϸ�����

	wstring				m_strName;		// �ִϸ��̼� �̸�
	CImage*				m_pImage;		// �ִϸ��̼� �̹���
	vector<AniFrame>	m_vecFrame;		// �ִϸ��̼��� ������ ������
	UINT				m_iCurFrame;	// ���� �÷������� �������� �ε���
	float				m_fAccTime;		// ���� �÷������� �������� �����ð�
	bool				m_bRepeat;		// �ִϸ��̼��� �ݺ� ����

public:
	const wstring& GetName();

private:
	void SetName(const wstring& name);

	void Create(CImage* pImg, Vector lt, Vector slice, Vector step, float duration, UINT count, bool repeat);	// �ִϸ��̼� ����
	void Replay();	// �ִϸ��̼� ó������ �ٽ� ����

private:
	void Init();
	void Update();
	void Render();
	void Release();
};
