#include "framework.h"
#include "CPlayerSkill.h"

#include "WinAPI.h"

#include "CCollider.h"
#include "CImage.h"
#include "CAnimator.h"

#include "CLightningSphere.h"
#include "CSparkCaliver.h"


CPlayerSkill::CPlayerSkill()
{
	
	
	m_pAnimator = nullptr;

	
	m_SelBut	= nullptr;
	m_Blank		= nullptr;

	m_layer		= Layer::Skill;
	sel			= SkillSel::Idle;
	
	m_strName	= L"½ºÅ³";

	LiSpTimer	= 0;
}

CPlayerSkill::~CPlayerSkill()
{
}

void CPlayerSkill::Init()
{
	
	
	m_SelBut= RESOURCE->LoadImg(L"SkillButton", L"Image\\Player\\SkillButton.png");
	m_Blank = RESOURCE->LoadImg(L"Blank", L"Image\\Player\\BlancBox.png");
	
	m_pAnimator = new CAnimator;
	m_pAnimator->CreateAnimation(L"Idle", m_Blank, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 0.f), 0.1f, 1);
	m_pAnimator->CreateAnimation(L"Button", m_SelBut, Vector(0.f, 0.f), Vector(100.f, 100.f), Vector(0.f, 0.f), 0.1f, 1);
	
	m_pAnimator->Play(L"Idle", false);
	AddComponent(m_pAnimator);
}

void CPlayerSkill::Update()
{
	LiSpTimer += DT;
	TIME->SetTimeScale(0.5f);
	if (LiSpTimer > 1.f)
	{
		sel = SkillSel::Idle;
		
		LiSpTimer = 0;
		
		TIME->SetTimeScale(1.f);
		DELETEOBJECT(this);
	}
	

	if (BUTTONDOWN(VK_LEFT))
	{
		sel = SkillSel::LightningSphere;
		TIME->SetTimeScale(1.f);
		DELETEOBJECT(this);
	}
	
	if (BUTTONDOWN(VK_RIGHT))
	{
		sel = SkillSel::SparkCaliber;
		TIME->SetTimeScale(1.f);
		DELETEOBJECT(this);
	}
	
	AnimatorUpdate();
}

void CPlayerSkill::Render()
{
}

void CPlayerSkill::Release()
{
}

void CPlayerSkill::AnimatorUpdate()
{
	wstring str = L"";

	str += L"Button";
	m_pAnimator->Play(str, false);
	
}
