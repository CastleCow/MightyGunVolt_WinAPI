#include "framework.h"
#include "CMonsterWaterBoss.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"


CMonsterWaterBoss::CMonsterWaterBoss()
{
	m_vecScale = Vector(100, 100);
	m_layer = Layer::Monster;
	m_strName = L"몬스터";
	m_MonImg = nullptr;
	m_pAnimator = nullptr;
	m_bIsHit = false;
	m_fIsAttacked;
	m_fHP=50;
}

CMonsterWaterBoss::~CMonsterWaterBoss()
{
}

void CMonsterWaterBoss::Init()
{
	m_MonImg = RESOURCE->LoadImg(L"No.2Cyro",L"Image\\Monster\\BOSS_MWATER.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"EntryRight", m_MonImg, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,2);
	m_pAnimator->CreateAnimation(L"EntryLeft", m_MonImg, Vector(0.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,2);
	
	m_pAnimator->CreateAnimation(L"IdleRight", m_MonImg, Vector(300.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_MonImg,  Vector(300.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3);
	
	m_pAnimator->CreateAnimation(L"JumpRight", m_MonImg, Vector(750.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3);
	m_pAnimator->CreateAnimation(L"JumpLeft", m_MonImg,  Vector(750.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3);

	m_pAnimator->CreateAnimation(L"SummonRight", m_MonImg, Vector(1150.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 4);
	m_pAnimator->CreateAnimation(L"SummonLeft", m_MonImg,  Vector(1150.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 4);

	m_pAnimator->CreateAnimation(L"BattingRight", m_MonImg, Vector(0.f, 250.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 5);
	m_pAnimator->CreateAnimation(L"BattingLeft", m_MonImg,  Vector(0.f, 400.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 5);

	m_pAnimator->CreateAnimation(L"HammerJumpRight", m_MonImg, Vector(750.f, 250.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);
	m_pAnimator->CreateAnimation(L"HammerJumpLeft", m_MonImg,  Vector(750.f, 400.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);
	m_pAnimator->CreateAnimation(L"HammerFallRight", m_MonImg, Vector(1050.f, 250.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);
	m_pAnimator->CreateAnimation(L"HammerFallLeft", m_MonImg,  Vector(1050.f, 400.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);

	m_pAnimator->CreateAnimation(L"HitRight", m_MonImg, Vector(1350.f, 250.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"HitLeft", m_MonImg,  Vector(1350.f, 400.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);

	m_pAnimator->CreateAnimation(L"FinshRight", m_MonImg, Vector(0.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3,false);
	m_pAnimator->CreateAnimation(L"FinshLeft",  m_MonImg, Vector(0.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3,false);

	m_pAnimator->CreateAnimation(L"FinshLoopRight", m_MonImg, Vector(450.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"FinshLoopLeft", m_MonImg,  Vector(450.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 8);
	m_pAnimator->CreateAnimation(L"FinshLoopEndRight", m_MonImg, Vector(150.f*11.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);
	m_pAnimator->CreateAnimation(L"FinshLoopEndLeft", m_MonImg,  Vector(150.f*11.f, 500.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 2,false);

	AddComponent(m_pAnimator);
	m_pAnimator->Play(L"EntryLeft", false);
	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0));
	
	
}

void CMonsterWaterBoss::Update()
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
			m_vecPos += metoP.Normalized() * 200 * DT;

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

void CMonsterWaterBoss::Render()
{
	

}

void CMonsterWaterBoss::Release()
{
}

void CMonsterWaterBoss::OnCollisionEnter(CCollider* pOtherCollider)
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

void CMonsterWaterBoss::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CMonsterWaterBoss::OnCollisionExit(CCollider* pOtherCollider)
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

void CMonsterWaterBoss::AnimatorUpdate()
{
	wstring str;
	m_pAnimator->Play(L"Flying", false);
}
