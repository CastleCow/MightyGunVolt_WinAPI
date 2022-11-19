#include "framework.h"
#include "CBossBullet.h"

#include"CImage.h"

CBossBullet::CBossBullet()
{
	m_vecScale = Vector(10, 10);
	m_vecDir = Vector(0, 0);
	m_pAnimator = nullptr;
	m_fVelocity = 250;
	bulDelTime = 0;
	Dir[0] = { 0 };
	m_layer = Layer::MonsterBullet;
	m_strName = L"보스미사일";
	m_Image = nullptr;

}

CBossBullet::~CBossBullet()
{
}

void CBossBullet::Init()
{
	AddCollider(ColliderType::Circle, Vector(8, 8), Vector(0, 0));
	m_Image = RESOURCE->LoadImg(L"Bullet", L"Image\\Monster\\BOSS_MWATER.png");

	m_pAnimator->CreateAnimation(L"Water", m_Image, Vector(150.f*12.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.0f, 1);
	m_pAnimator->CreateAnimation(L"Icing", m_Image, Vector(150.f*13.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.0f, 1);

	m_pAnimator->Play(L"Water", false);
	AddComponent(m_pAnimator);
}

void CBossBullet::Update()
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

	AnimatorUpdate();
}

void CBossBullet::Render()
{
}

void CBossBullet::Release()
{
}

void CBossBullet::AnimatorUpdate()
{
	wstring str = L"";
	if (m_vecDir.x > 0) str += L"Right";
	else if (m_vecDir.x < 0) str += L"Left";

	if (bulenhace) str += L"+";
	else str += L"";


	m_pAnimator->Play(str, false);
}

void CBossBullet::OnCollisionEnter(CCollider* pOtherCollider)
{
	Logger::Debug(L"미사일이 충돌체와 부딪혀 사라집니다.");
	DELETEOBJECT(this);
}

void CBossBullet::SetDir(Vector dir)
{
	m_vecDir = dir.Normalized();
}

void CBossBullet::SetVelocity(float velocity)
{
	m_fVelocity = velocity;
}
