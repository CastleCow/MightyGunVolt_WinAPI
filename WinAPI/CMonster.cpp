#include "framework.h"
#include "CMonster.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"


CMonster::CMonster()
{
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
	m_strName = L"몬스터";
	m_MonImg = nullptr;
	m_pAnimator = nullptr;
	m_bIsHit = false;
	m_fIsAttacked;
	m_fHP=5;
}

CMonster::~CMonster()
{
}

void CMonster::Init()
{
	m_MonImg = RESOURCE->LoadImg(L"Fly",L"Image\\Monster\\Mon_FlyingBot_Sort.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Flying", m_MonImg, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,5);

	AddComponent(m_pAnimator);
	m_pAnimator->Play(L"Flying", false);
	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
	
	
}

void CMonster::Update()
{
	
	Vector metoP = m_vecPos - PLAYERPOS;
	if (m_fIsAttacked > 0)
	{
		m_fIsAttacked -= 10*DT;
		m_vecPos += metoP.Normalized() * 150 * DT;
	}
	else if (m_bIsHit)
	{
		if (m_fTimer > 0)
		{
			m_fTimer -= DT;
			m_vecPos += metoP.Normalized() * 100 * DT;

		}
		else
		{
			m_bIsHit = false;
		}
	}
	else if(metoP.x<200&&
		metoP.y<200)
	m_vecPos -=metoP.Normalized() * 100 * DT;


	if (m_fHP <= 0)
		DELETEOBJECT(this);
	AnimatorUpdate();
}

void CMonster::Render()
{
	

}

void CMonster::Release()
{
}

void CMonster::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 충돌진입");
		m_bIsHit = true;
		m_fTimer = 2.f;
	}
	else if (pOtherCollider->GetObjName() == L"미사일")
	{
		Logger::Debug(L"몬스터가 미사일과 충돌진입");
		m_fIsAttacked++;
		m_fHP--;
	}
}

void CMonster::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CMonster::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 충돌해제");
	}
	else if (pOtherCollider->GetObjName() == L"미사일")
	{
		Logger::Debug(L"몬스터가 미사일과 충돌해제");
	}
}

void CMonster::AnimatorUpdate()
{
	wstring str;
	m_pAnimator->Play(L"Flying", false);
}
