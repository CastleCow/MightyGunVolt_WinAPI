#include "framework.h"
#include "CMonsterWheel.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include "CDeadExplo.h"


CMonsterWheel::CMonsterWheel()
{
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
	m_strName = L"몬스터";
	m_MonImg = nullptr;
	m_pAnimator = nullptr;
	m_bIsHit = false;
	m_bOnGround = false;
	m_fIsAttacked;
	m_fHP=5;
	m_vecDir = Vector(0, 0);
}

CMonsterWheel::~CMonsterWheel()
{
}

void CMonsterWheel::Init()
{
	m_MonImg = RESOURCE->LoadImg(L"Wheel",L"Image\\Monster\\Mon_Wheel_ani.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Crawl", m_MonImg, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,3);

	AddComponent(m_pAnimator);
	m_pAnimator->Play(L"Crawl", false);
	AddCollider(ColliderType::Circle, Vector(15, 15), Vector(0, 0),1.5f);
	
	m_vecDir =  m_vecPos-PLAYERPOS;
}

void CMonsterWheel::Update()
{
	
	//Vector metoP = m_vecPos - PLAYERPOS;
	if (m_fIsAttacked > 0)
	{
		m_fIsAttacked -= 10*DT;
		m_vecPos.x += m_vecDir.Normalized().x * 150 * DT;
	}
	else if (m_bIsHit)
	{
		if (m_fTimer > 0)
		{
			m_fTimer -= DT;
			m_vecPos.x += m_vecDir.Normalized().x * 200 * DT;

		}
		else
		{
			m_bIsHit = false;
		}
	}
	//else if(m_vecDir.x<300)
		m_vecPos.x -= m_vecDir.Normalized().x * 100 * DT;


		if (m_fHP <= 0) {
			CDeadExplo* dead = new CDeadExplo();
			dead->SetPos(m_vecPos);
			ADDOBJECT(dead);
			DELETEOBJECT(this);
		}
	AnimatorUpdate();
	if(m_bOnGround==false)
		Fall();
}

void CMonsterWheel::Render()
{
	

}

void CMonsterWheel::Release()
{
}

void CMonsterWheel::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName()==L"땅")
	{
		m_vecPos.y = pOtherCollider->GetPos().y - pOtherCollider->GetScale().y * 0.9f;
		m_bOnGround = true;
	}
	if (pOtherCollider->GetObjName() == L"벽")
	{
		m_vecDir.x *= -1;
		m_vecPos.x += m_vecDir.x * DT;
	}
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
	else if (pOtherCollider->GetObjName() == L"스파크칼리버")
		m_fHP -= 5;
	else if (pOtherCollider->GetObjName() == L"라이트닝스피어")
		m_fHP -= 3;
}

void CMonsterWheel::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"땅")
	{
		m_vecPos.y = pOtherCollider->GetPos().y- pOtherCollider->GetScale().y*0.9f;
		m_bOnGround = true;
	}
}

void CMonsterWheel::OnCollisionExit(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 충돌해제");
	}
	else if (pOtherCollider->GetObjName() == L"미사일")
	{
		Logger::Debug(L"몬스터가 미사일과 충돌해제");
	}
	if (pOtherCollider->GetObjName() == L"땅")
	{
		
		m_bOnGround = false;
	}
}

void CMonsterWheel::AnimatorUpdate()
{
	wstring str;
	m_pAnimator->Play(L"Crawl", false);
}

void  CMonsterWheel::Fall()
{
	m_vecPos.y += 100 * DT;
}