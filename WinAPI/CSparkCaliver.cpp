#include "framework.h"
#include "CSparkCaliver.h"

#include "WinAPI.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

CSparkCaliver::CSparkCaliver()
{
	m_strName = L"스파크칼리버";
	m_layer = Layer::Skill;
	m_bIsSpCal = false;
	m_pAnimator = nullptr;
	m_vecPos = Vector(0, 0);
	m_SparkCal = nullptr;
}

CSparkCaliver::~CSparkCaliver()
{
}

void CSparkCaliver::Init()
{
	m_SparkCal = RESOURCE->LoadImg(L"SpCal", L"Image\\Player\\SparkCaliber_Ani.png");
	m_Blank = RESOURCE->LoadImg(L"Blank", L"Image\\Player\\BlancBox.png");

	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"Idle", m_Blank, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"SpCalRight", m_SparkCal, Vector(0.f, 0.f), Vector(250.f, 162.f), Vector(250.f, 0.f), 0.08f, 5, false);
	m_pAnimator->CreateAnimation(L"SpCalLeft", m_SparkCal, Vector(0.f, 163.f), Vector(250.f, 162.f), Vector(250.f, 0.f), 0.08f, 5, false);
	m_pAnimator->Play(L"Idle", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Rect, Vector(200, 100), Vector(0, 0));
}

void CSparkCaliver::Update()
{
	Timer += DT;
	if (Timer > 1.f)
		DELETEOBJECT(this);
	AnimatorUpdate();
}

void CSparkCaliver::Render()
{
}

void CSparkCaliver::Release()
{
}

void CSparkCaliver::AnimatorUpdate()
{
	wstring str = L"";
	str += L"SpCal";
	if (m_vecLookDir.x > 0) str += L"Right";
	else if (m_vecLookDir.x < 0) str += L"Left";
	m_pAnimator->Play(str, false);

}

void CSparkCaliver::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CSparkCaliver::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CSparkCaliver::OnCollisionExit(CCollider* pOtherCollider)
{
}
