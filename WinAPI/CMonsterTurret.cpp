#include "framework.h"
#include "CMonsterTurret.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"
#include"CMonsterTurretMissile.h"
#include"CDeadExplo.h"

CMonsterTurret::CMonsterTurret()
{
	m_vecScale = Vector(100, 100);
	m_vecDir = Vector(0, 0);
	m_layer = Layer::Monster;
	m_strName = L"몬스터";
	m_MonImg = nullptr;
	m_pAnimator = nullptr;
	m_bIsShot = false;
	m_fIsAttacked=false;
	m_fHP=5;
	//m_fTimer = -1.f;
}

CMonsterTurret::~CMonsterTurret()
{
}

void CMonsterTurret::Init()
{
	m_MonImg = RESOURCE->LoadImg(L"Turret",L"Image\\Monster\\Mon_turret_sort.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Idle0Left", m_MonImg,  Vector(0.f, 0.f),   Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,1);
	m_pAnimator->CreateAnimation(L"Idle30Left", m_MonImg, Vector(150.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,1);
	m_pAnimator->CreateAnimation(L"Idle45Left", m_MonImg, Vector(300.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,1);
	m_pAnimator->CreateAnimation(L"Idle60Left", m_MonImg, Vector(450.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,1);
	m_pAnimator->CreateAnimation(L"Idle90Left", m_MonImg, Vector(600.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,1);
	
	m_pAnimator->CreateAnimation(L"Shot0Left", m_MonImg, Vector(0.f, 0.f), Vector(100.f, 100.f),    Vector(0.f, 150.f), 0.9f, 2);
	m_pAnimator->CreateAnimation(L"Shot30Left", m_MonImg, Vector(150.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 150.f), 0.9f, 2);
	m_pAnimator->CreateAnimation(L"Shot45Left", m_MonImg, Vector(300.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 150.f), 0.9f, 2);
	m_pAnimator->CreateAnimation(L"Shot60Left", m_MonImg, Vector(450.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 150.f), 0.9f, 2);
	m_pAnimator->CreateAnimation(L"Shot90Left", m_MonImg, Vector(600.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 150.f), 0.9f, 2);

	m_pAnimator->CreateAnimation(L"Idle0Right", m_MonImg, Vector(750.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"Idle30Right", m_MonImg, Vector(900.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"Idle45Right", m_MonImg, Vector(1050.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"Idle60Right", m_MonImg, Vector(1200.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"Idle90Right", m_MonImg, Vector(1350.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);

	m_pAnimator->CreateAnimation(L"Shot0Right", m_MonImg, Vector(750.f, 0.f), Vector(100.f, 100.f),   Vector(0.f, 150.f), 0.9f, 2);
	m_pAnimator->CreateAnimation(L"Shot30Right", m_MonImg, Vector(900.f, 0.f), Vector(100.f, 100.f),  Vector(0.f, 150.f), 0.9f, 2);
	m_pAnimator->CreateAnimation(L"Shot45Right", m_MonImg, Vector(1050.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 150.f), 0.9f, 2);
	m_pAnimator->CreateAnimation(L"Shot60Right", m_MonImg, Vector(1200.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 150.f), 0.9f, 2);
	m_pAnimator->CreateAnimation(L"Shot90Right", m_MonImg, Vector(1350.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 150.f), 0.9f, 2);
	AddComponent(m_pAnimator);

	m_pAnimator->Play(L"Idle0Left", false);
	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, 0),1.f);
	
	
}

void CMonsterTurret::Update()
{
	m_fTimer += DT;
	Vector metoP =PLAYERPOS-m_vecPos;
	if (abs(metoP.x < 300) &&
		abs(metoP.y < 300) &&
		m_fTimer>1.5f)
		CreateMissile();
	

	if (m_fHP <= 0)
	{
		CDeadExplo* dead = new CDeadExplo();
		dead->SetPos(m_vecPos);
		ADDOBJECT(dead);
		DELETEOBJECT(this);
	}
		

	AnimatorUpdate();
}

void CMonsterTurret::Render()
{
	

}

void CMonsterTurret::Release()
{
}

void CMonsterTurret::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 충돌진입");
		
		m_fTimer = 2.f;
	}
	else if (pOtherCollider->GetObjName() == L"미사일")
	{
		Logger::Debug(L"몬스터가 미사일과 충돌진입");
		m_fIsAttacked++;
		m_fHP--;
	}
	else if (pOtherCollider->GetObjName() == L"스킬")
		m_fHP -= pOtherCollider->GetDamage();
	

	if (pOtherCollider->GetObjName() == L"땅")
	{
		m_bOnGround = true;
	}
		
}

void CMonsterTurret::OnCollisionStay(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"땅")
	{
		//m_vecPos.y -= pOtherCollider->GetPos().y-pOtherCollider->GetScale().y+4;
	}
}

void CMonsterTurret::OnCollisionExit(CCollider* pOtherCollider)
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

void CMonsterTurret::AnimatorUpdate()
{
	Vector metoP = PLAYERPOS-m_vecPos;
	wstring str;

	if (metoP.x > 300)
		str += L"Idle";
	else str+=L"Shot";

	if (metoP.Normalized().y > 0)
		str += L"0";
	else if (0<abs(metoP.Normalized().x * 0.5f) - abs(metoP.Normalized().y)&& 
		abs(metoP.Normalized().x * 0.5f) - abs(metoP.Normalized().y)<1)
	{
		str += L"30";
	}
	else if (0 < abs(metoP.Normalized().x ) - abs(metoP.Normalized().y) &&
		abs(metoP.Normalized().x ) - abs(metoP.Normalized().y) < 1)
	{
		str += L"45";
	}
	else if (0 < abs(metoP.Normalized().x * 2.f) - abs(metoP.Normalized().y) &&
		abs(metoP.Normalized().x * 2.f) - abs(metoP.Normalized().y) < 1)
	{
		str += L"60";
		
	}
	else 
	{
		str += L"90";
		
	}

	if (m_vecPos.x <= PLAYERPOS.x)
		str += L"Right";
	else str += L"Left";

	m_pAnimator->Play(str, false);
}

void CMonsterTurret::CreateMissile()
{
	m_fTimer =0;
	Logger::Debug(L"미사일 생성");
	Vector metoP = PLAYERPOS - m_vecPos;
	CMonsterTurretMissile* pMissile = new CMonsterTurretMissile();
	pMissile->SetPos(m_vecPos);
	pMissile->SetDir(metoP.Normalized());
	ADDOBJECT(pMissile);


}