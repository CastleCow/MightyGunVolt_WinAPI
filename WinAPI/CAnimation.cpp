#include "framework.h"
#include "CAnimation.h"

#include "CTimeManager.h"
#include "CRenderManager.h"
#include "CAnimator.h"
#include "CGameObject.h"

CAnimation::CAnimation()
{
	m_pAnimator = nullptr;

	m_strName = L"";
	m_pImage = nullptr;
	m_iCurFrame = 0;
	m_fAccTime = 0;
	m_bRepeat = true;
}

CAnimation::~CAnimation()
{
}

const wstring& CAnimation::GetName()
{
	return m_strName;
}

void CAnimation::SetName(const wstring& name)
{
	m_strName = name;
}

void CAnimation::Create(CImage* pImg, Vector lt, Vector slice, Vector step, float duration, UINT count, bool repeat)
{
	m_pImage = pImg;	// ������ �̹����� ���ִ� �̹��� ����
	m_bRepeat = repeat;	// �ݺ�����

	// �ٵ��ǽ� ������ �̹����� ����ų ��ġ�� ����
	// lt		: ������ �̹����� ������� ��ǥ
	// step		: ������ �̹����� ����
	// slice	: ������ �̹����� ũ��
	// duration : ������ �̹����� ���ӽð�
	AniFrame frame;
	for (UINT i = 0; i < count; i++)
	{
		frame.lt = lt + step * i;
		frame.slice = slice;
		frame.duration = duration;

		m_vecFrame.push_back(frame);
	}
}

void CAnimation::Replay()
{
	// �ִϸ��̼� ����� : ���� �����Ӱ� �����ð��� �ʱ�ȭ
	m_iCurFrame = 0;
	m_fAccTime = 0;
}

void CAnimation::Init()
{
}

void CAnimation::Update()
{
	// ���� �÷������� �������� �����ð�
	m_fAccTime += DT;

	// �����ð��� ���� �÷������� �������� ���ӽð����� Ŀ���� ���
	// -> ���� �������� ������� �ϴ� ���
	if (m_vecFrame[m_iCurFrame].duration < m_fAccTime)
	{
		m_iCurFrame++;	// ���� �÷������� �������� �ε����� �ϳ� ����
		m_fAccTime = 0;	// ���� �÷������� �������� �����ð� �ʱ�ȭ

		// ���� �÷������� �������� ������ �������̾��� ���
		if (m_iCurFrame == m_vecFrame.size())
		{
			// �ݺ� �ִϸ��̼��̶�� ó������, �ƴ϶�� �������� �ٽ� ���
			if (m_bRepeat)	m_iCurFrame = 0;
			else			m_iCurFrame--;
		}
	}
}

void CAnimation::Render()
{
	Vector pos = m_pAnimator->GetOwner()->GetPos();	// �ִϸ��̼��� �׷��� ��ġ Ȯ��
	AniFrame frame = m_vecFrame[m_iCurFrame];		// �ִϸ��̼��� �׷��� ������ Ȯ��

	// ������ �̹��� �׸���
	RENDER->FrameImage(
		m_pImage,
		pos.x - frame.slice.x * 0.5f,
		pos.y - frame.slice.y * 0.5f,
		pos.x + frame.slice.x * 0.5f,
		pos.y + frame.slice.y * 0.5f,
		frame.lt.x,
		frame.lt.y,
		frame.lt.x + frame.slice.x,
		frame.lt.y + frame.slice.y
	);
}

void CAnimation::Release()
{
}
