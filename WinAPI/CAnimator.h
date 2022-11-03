#pragma once
#include "CComponent.h"

class CAnimation;
class CImage;

class CAnimator : public CComponent
{
public:
	CAnimator();
	virtual ~CAnimator();

private:
	map<wstring, CAnimation*>	m_mapAni;	// �ִϸ��̼ǵ��� ��� ���� �ڷᱸ��
	CAnimation* m_pCurAni;					// ���� �ִϸ��̼�

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

public:
	void CreateAnimation(const wstring& aniName, CImage* pImg,	// �ִϸ��̼� ����
		Vector lt, Vector slice, Vector step, float duration, UINT count, bool repeat = true);
	void RemoveAnimation(const wstring& aniName);				// �ִϸ��̼� ����
	CAnimation* FindAnimation(const wstring& aniName);			// �ִϸ��̼� Ž��

	void Play(const wstring& aniName, bool trigger = false);	// �ִϸ��̼� ���
	void Stop();												// �ִϸ��̼� ����
};

