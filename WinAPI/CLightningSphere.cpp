#include "framework.h"
#include "CLightningSphere.h"

#include "WinAPI.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

CLightningSphere::CLightningSphere()
{
	m_strName = L"½ºÅ³";
	m_layer = Layer::Skill;
	m_bIsLiSp = false;
	m_pAnimator = nullptr;
	m_vecPos = Vector(0, 0);
	m_LiSph = nullptr;
}

CLightningSphere::~CLightningSphere()
{
}

void CLightningSphere::Init()
{
	m_LiSph = RESOURCE->LoadImg(L"LiSp", L"Image\\Player\\LightSphereAniRo.png");
	m_Blank = RESOURCE->LoadImg(L"Blank", L"Image\\Player\\BlancBox.png");

	m_pAnimator = new CAnimator;

	m_pAnimator->CreateAnimation(L"Idle", m_Blank, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"LightnigSphere", m_LiSph, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.3f, 8);
	m_pAnimator->Play(L"Idle", false);
	AddComponent(m_pAnimator);

	AddCollider(ColliderType::Circle, Vector(60, 60), Vector(0, 0),5.f);
}

void CLightningSphere::Update()
{
	Timer += DT;
	if (Timer > 2.0f)
		DELETEOBJECT(this);

	AnimatorUpdate();
}

void CLightningSphere::Render()
{
}

void CLightningSphere::Release()
{
}

void CLightningSphere::AnimatorUpdate()
{
	m_pAnimator->Play(L"LightnigSphere", false);
}

void CLightningSphere::OnCollisionEnter(CCollider* pOtherCollider)
{
}

void CLightningSphere::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CLightningSphere::OnCollisionExit(CCollider* pOtherCollider)
{
}
