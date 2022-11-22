#include "framework.h"
#include "CMonsterTurretMissile.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include"CImage.h"
CMonsterTurretMissile::CMonsterTurretMissile()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(0, 0);
	m_pAnimator = nullptr;
	m_fVelocity = 250;
	bulDelTime = 0;
	Dir[0] = {0};
	m_layer = Layer::MonsterBullet;
	m_strName = L"몬스터미사일";
	m_Image = nullptr;

}

CMonsterTurretMissile::~CMonsterTurretMissile()
{
}

void CMonsterTurretMissile::Init()
{
	AddCollider(ColliderType::Circle, Vector(8, 8), Vector(0, 0),1.f);
	m_Image = RESOURCE->LoadImg(L"TurretBullet", L"Image\\Monster\\Mon_turret_sort.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Left", m_Image, Vector(1500.f, 0.f), Vector(100.f,100.f), Vector(150.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"Right", m_Image, Vector(1500.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 1);

	m_pAnimator->Play(L"Right", false);
	AddComponent(m_pAnimator);

}

void CMonsterTurretMissile::Update()
{
	m_vecPos += m_vecDir * m_fVelocity * DT;

	bulDelTime += DT;
	if (bulDelTime > 2.0f) { 
		DELETEOBJECT(this);	
	}
	
	AnimatorUpdate();
	
}

void CMonsterTurretMissile::Render()
{
	
	


}

void CMonsterTurretMissile::Release()
{
}

void CMonsterTurretMissile::AnimatorUpdate()
{
	wstring str = L"";
	if (m_vecDir.x > 0) str += L"Right";
	else if (m_vecDir.x < 0) str += L"Left";


	m_pAnimator->Play(str, false);

}

void CMonsterTurretMissile::OnCollisionEnter(CCollider* pOtherCollider)
{

	Logger::Debug(L"미사일이 충돌체와 부딪혀 사라집니다.");
	DELETEOBJECT(this);
}

void CMonsterTurretMissile::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CMonsterTurretMissile::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
