#include "framework.h"
#include "CMonsterMissileBotMissile.h"

#include "CRenderManager.h"
#include "CTimeManager.h"
#include "CEventManager.h"
#include "CCollider.h"
#include "CImage.h"

CMonsterMissileBotMissile::CMonsterMissileBotMissile()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(0, 0);
	m_pAnimator = nullptr;
	m_fVelocity = 250;
	bulDelTime = 0;
	Dir[0] = {0};
	m_layer = Layer::Missile;
	m_strName = L"미사일";
	m_Image = nullptr;

}

CMonsterMissileBotMissile::~CMonsterMissileBotMissile()
{
}

void CMonsterMissileBotMissile::Init()
{
	AddCollider(ColliderType::Circle, Vector(8, 8), Vector(0, 0));
	m_Image = RESOURCE->LoadImg(L"Bullet", L"Image\\Player\\Monster_MissileBot_Ani_Bullet.png");
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Left", m_Image, Vector(0.f, 0.f), Vector(100.f,100.f), Vector(150.f, 0.f), 0.1f, 5);
	m_pAnimator->CreateAnimation(L"Right", m_Image, Vector(0.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 5);

	
	m_pAnimator->CreateAnimation(L"Left+", m_Image ,Vector(750.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f, 3);
	m_pAnimator->CreateAnimation(L"Right+",m_Image ,Vector(750.f, 150.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.1f,3);

	m_pAnimator->Play(L"Right", false);
	AddComponent(m_pAnimator);

}

void CMonsterMissileBotMissile::Update()
{
	m_vecPos += m_vecDir * m_fVelocity * DT;

	bulDelTime += DT;
	if (bulDelTime > 2.0f) { 
		DELETEOBJECT(this);
		
	}
	if (BUTTONDOWN('A'))
	{
		bulenhace++;
		bulenhace = (int)bulenhace % 2;
	}
	
	// 화면밖으로 나갈경우 삭제
	/*if (m_vecPos.x < 0 ||
		m_vecPos.x > WINSIZEX ||
		m_vecPos.y < 0 ||
		m_vecPos.y > WINSIZEY)
		DELETEOBJECT(this);*/
	AnimatorUpdate();
	
}

void CMonsterMissileBotMissile::Render()
{
	RENDER->FrameCircle(
		m_vecPos.x,
		m_vecPos.y,
		m_vecScale.x);
	
	/*RENDER->Image(m_Image, 
		m_vecPos.x,
		m_vecPos.y, 
		(m_vecPos.x)+m_Image->GetWidth(),
		(m_vecPos.y) + m_Image->GetHeight());*/
	//RENDER->Image(m_ImageRV, m_vecPos.x, m_vecPos.y, (m_vecPos.x) + m_ImageRV->GetWidth(), (m_vecPos.y) + m_ImageRV->GetHeight());


}

void CMonsterMissileBotMissile::Release()
{
}

void CMonsterMissileBotMissile::AnimatorUpdate()
{
	wstring str = L"";
	if (m_vecDir.x > 0) str += L"Right";
	else if (m_vecDir.x < 0) str += L"Left";

	if (bulenhace) str += L"+";
	else str += L"";


	m_pAnimator->Play(str, false);

}

void CMonsterMissileBotMissile::OnCollisionEnter(CCollider* pOtherCollider)
{

	Logger::Debug(L"미사일이 충돌체와 부딪혀 사라집니다.");
	DELETEOBJECT(this);
}

void CMonsterMissileBotMissile::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CMonsterMissileBotMissile::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
