#include "framework.h"
#include "CGotoNextArea.h"

CGotoNextArea::CGotoNextArea()
{
	m_vecScale = Vector(100, 100);
	//m_layer = Layer::Tile;
	m_layer = Layer::Monster;
	m_strName = L"다음맵으로";
	nextScene = GroupScene::Stage01;
}

CGotoNextArea::~CGotoNextArea()
{
}

void CGotoNextArea::Init()
{
	AddCollider(ColliderType::Rect, m_vecScale, Vector(0, 0));
}

void CGotoNextArea::Update()
{
}

void CGotoNextArea::Render()
{
	RENDER->FrameRect(
		m_vecPos.x - m_vecScale.x * 0.5f,
		m_vecPos.y - m_vecScale.y * 0.5f,
		m_vecPos.x + m_vecScale.x * 0.5f,
		m_vecPos.y + m_vecScale.y * 0.5f);
}

void CGotoNextArea::Release()
{
}

void CGotoNextArea::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"플레이어")
	{
		//여기서 다음씬으로 리트라이 카운트 HP MP등을 넘겨준다
		GAME->SetPlayerHP(PHP);
		CHANGESCENE(nextScene);
	
	}
}

void CGotoNextArea::OnCollisionStay(CCollider* pOtherCollider)
{
}

void CGotoNextArea::OnCollisionExit(CCollider* pOtherCollider)
{
}
