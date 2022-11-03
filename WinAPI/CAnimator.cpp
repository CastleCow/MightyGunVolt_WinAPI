#include "framework.h"
#include "CAnimator.h"

#include "CAnimation.h"

CAnimator::CAnimator()
{
	m_pCurAni = nullptr;
}

CAnimator::~CAnimator()
{
}

void CAnimator::Init()
{
}

void CAnimator::Update()
{
	if (nullptr != m_pCurAni)
		m_pCurAni->Update();
}

void CAnimator::Render()
{
	if (nullptr != m_pCurAni)
		m_pCurAni->Render();
}

void CAnimator::Release()
{
	for (pair<wstring, CAnimation*> animation : m_mapAni)
	{
		delete animation.second;
	}
	m_mapAni.clear();
}

void CAnimator::CreateAnimation(const wstring& aniName, CImage* pImg, Vector lt, Vector slice, Vector step, float duration, UINT count, bool repeat)
{
	// ���� �̸��� �ִϸ��̼��� �̹� ���� ��� ���α׷� ���
	CAnimation* pAni = FindAnimation(aniName);
	assert(nullptr == pAni && L"Animation already exist");

	// �ִϸ��̼��� �̸��� ���� �� �ڷᱸ���� ����
	pAni = new CAnimation;
	pAni->SetName(aniName);
	pAni->Create(pImg, lt, slice, step, duration, count, repeat);
	pAni->m_pAnimator = this;

	m_mapAni.insert(make_pair(aniName, pAni));
}

void CAnimator::RemoveAnimation(const wstring& aniName)
{
	// ���� �̸��� �ִϸ��̼��� ã���� ��� ����
	CAnimation* pAni = FindAnimation(aniName);

	if (nullptr != pAni)
		m_mapAni.erase(aniName);
}

CAnimation* CAnimator::FindAnimation(const wstring& aniName)
{
	// �̸��� ���� �ڷᱸ������ �ִϸ��̼��� Ž���ϰ� ���� ��� ��ȯ
	auto iter = m_mapAni.find(aniName);
	if (iter == m_mapAni.end())
		return nullptr;
	else
		return m_mapAni[aniName];
}

void CAnimator::Play(const wstring& aniName, bool trigger)
{
	// ���� �ִϸ��̼��� �÷����ϰ��� �ϴ� �ִϸ��̼��̸�
	// Tigger�� �ƴ� ��� ���� �ִϸ��̼��� �������� ����
	// Tigger : ���� �ִϸ��̼��� ó������ ��� (ex. ���� ���ó�� ���������� ó������ ����ؾ��ϴ� �ִϸ��̼�)
	if (nullptr != m_pCurAni && aniName == m_pCurAni->GetName() && !trigger)
		return;

	// �ִϸ��̼� �ڷᱸ������ �ִϸ��̼��� Ž��
	CAnimation* pAnimation = FindAnimation(aniName);
	// Ž���� ��� �ִϸ��̼��� ���� ��� ���α׷� ���
	assert(nullptr != pAnimation && L"Animation no exist");
	// Ʈ���� Ÿ���� ����̰ų� �ִϸ��̼��� �ٲ���� ��� �ִϸ��̼��� ó������ ���
	if (trigger || m_pCurAni != pAnimation) pAnimation->Replay();
	// ���� �ִϸ��̼��� Ž���� �ִϸ��̼����� ��ü
	m_pCurAni = pAnimation;
}

void CAnimator::Stop()
{
	// ���� �ִϸ��̼��� ������ �Ͽ� ����
	m_pCurAni = nullptr;
}
