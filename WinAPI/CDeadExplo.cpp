#include "framework.h"
#include "CDeadExplo.h"

#include"CImage.h"


CDeadExplo::CDeadExplo()
{
	m_vecScale = Vector(10, 10);

	Dir[0] = { 0 };
	m_layer = Layer::MonsterBullet;
	m_strName = L"Á×À½";
	m_Image = nullptr;

}

CDeadExplo::~CDeadExplo()
{
}

void CDeadExplo::Init()
{
	
	m_Image = RESOURCE->LoadImg(L"Explosion", L"Image\\Monster\\Explosion Effect.png");
	m_pAnimator = new CAnimator();
	m_pAnimator->CreateAnimation(L"Explode", m_Image, Vector(1.f ,71.f), Vector(58.f, 56.f), Vector(61.f, 0.f), 0.1f, 10);//59,127
	//m_pAnimator->CreateAnimation(L"Icing", m_Image, Vector(150.f * 13.f, 0.f), Vector(100.f, 100.f), Vector(150.f, 0.f), 0.0f, 1);

	m_pAnimator->Play(L"Explode", false);
	AddComponent(m_pAnimator);
}

void CDeadExplo::Update()
{
	DelTime += DT;
	if(DelTime>1.f)
		DELETEOBJECT(this);
	AnimatorUpdate();
}

void CDeadExplo::Render()
{
}

void CDeadExplo::Release()
{
}

void CDeadExplo::AnimatorUpdate()
{

	//m_pAnimator->Play(, false);
}


