#include "framework.h"
#include "CMonsterMissileBot.h"

#include "CRenderManager.h"
#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

#include"CMonsterMissileBotMissile.h"

CMonsterMissileBot::CMonsterMissileBot()
{
	m_vecScale = Vector(100, 100);
	BS = BotState::Idle;
	m_layer = Layer::Monster;
	m_strName = L"몬스터";
	m_MonImg = nullptr;
	m_pAnimator = nullptr;
	m_bIsHit = false;
	m_bIsShot = false;
	m_fIsAttacked=false;
	m_fHP=10;
}

CMonsterMissileBot::~CMonsterMissileBot()
{
}

void CMonsterMissileBot::Init()
{
	m_MonImg = RESOURCE->LoadImg(L"Bot",L"Image\\Monster\\Monster_MissileBot_Ani.png");

	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"IdleRight", m_MonImg, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,1);
	m_pAnimator->CreateAnimation(L"IdleLeft", m_MonImg, Vector(0.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,1);

	m_pAnimator->CreateAnimation(L"ShotMissileRight", m_MonImg, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 10,false);
	m_pAnimator->CreateAnimation(L"ShotMissileLeft", m_MonImg, Vector(0.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 10,false);
	
	m_pAnimator->CreateAnimation(L"ShotSparkRight", m_MonImg, Vector(0.f, 250.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 13,false);	
	m_pAnimator->CreateAnimation(L"ShotSparkLeft", m_MonImg,  Vector(0.f, 400.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 13,false);

	AddComponent(m_pAnimator);
	m_pAnimator->Play(L"IdleLeft", false);
	AddCollider(ColliderType::Rect, Vector(50, 50), Vector(0, -10));
	
	
}

void CMonsterMissileBot::Update()
{
	
	Vector metoP = PLAYERPOS-m_vecPos  ;
/*	if (m_fIsAttacked > 0)
	{
		m_fIsAttacked -= 10*DT;
		m_vecPos -= metoP.Normalized() * 10 * DT;
	}
	else */if (m_bIsHit)
	{
		if (m_fTimer > 0)
		{
			m_fTimer -= DT;
			//m_vecPos += metoP.Normalized() * 200 * DT;
		}
		else
		{
			m_bIsHit = false;
		}
	}
	else if (abs(metoP.x) < 400 &&
		abs(metoP.y) < 200)
	{
		CreateMissile();
		m_bIsHit = true;
	}


	if (m_fHP <= 0)
		DELETEOBJECT(this);
	AnimatorUpdate();
}

void CMonsterMissileBot::Render()
{
	

}

void CMonsterMissileBot::Release()
{
}

void CMonsterMissileBot::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		Logger::Debug(L"몬스터가 플레이어와 충돌진입");
		
	}
	else if (pOtherCollider->GetObjName() == L"미사일")
	{
		Logger::Debug(L"몬스터가 미사일과 충돌진입");
		m_fIsAttacked++;
		m_fHP--;
	}
	else if (pOtherCollider->GetObjName() == L"스킬")
		m_fHP -= pOtherCollider->GetDamage();
}

void CMonsterMissileBot::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CMonsterMissileBot::OnCollisionExit(CCollider* pOtherCollider)
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

void CMonsterMissileBot::AnimatorUpdate()
{
	wstring str;
	switch (BS)
	{
	case BotState::Idle:str += L"Idle";
		break;
	case BotState::Missile:str += L"ShotMissile";
		break;
	case BotState::Spark: str += L"ShotSpark";
		break;
	}
	
	if(m_vecPos.x<PLAYERPOS.x) str += L"Left";
	else str += L"Right";

	m_pAnimator->Play(str, false);
}

void CMonsterMissileBot::CreateMissile()
{
	Vector metoP = PLAYERPOS - m_vecPos;
	m_fTimer = 3.f;
	m_bIsShot==false ? BS=BotState::Missile : BS = BotState::Spark;

	if(BS == BotState::Missile)
	{
		CMonsterMissileBotMissile* Missile = new CMonsterMissileBotMissile;
		Missile->SetDir(metoP);
		Missile->SetPos(m_vecPos);
		Missile->SetBul(false);
		ADDOBJECT(Missile);
		CMonsterMissileBotMissile* Missile2 = new CMonsterMissileBotMissile;
		Missile2->SetDir(metoP);
		Missile2->SetPos(Vector(m_vecPos.x + 10 * metoP.Normalized().x, m_vecPos.y));
		Missile2->SetBul(false);
		ADDOBJECT(Missile2);

		m_bIsShot = true;
	}
	else
	{
		CMonsterMissileBotMissile* Missile = new CMonsterMissileBotMissile;
		Missile->SetDir(metoP);
		Missile->SetPos(Vector(m_vecPos.x + 20 * metoP.Normalized().x, m_vecPos.y+10));
		Missile->SetBul(true);
		ADDOBJECT(Missile);
		CMonsterMissileBotMissile* Missile2 = new CMonsterMissileBotMissile;
		Missile2->SetDir(metoP);
		Missile2->SetPos(Vector(m_vecPos.x + 10 * metoP.Normalized().x, m_vecPos.y+10));
		Missile2->SetBul(true);
		ADDOBJECT(Missile2);

		m_bIsShot = false;
	}


}