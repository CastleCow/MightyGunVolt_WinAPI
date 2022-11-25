#include "framework.h"
#include "CGotoNextArea.h"

CGotoNextArea::CGotoNextArea()
{
	m_vecScale = Vector(100, 100);
	//m_layer = Layer::Tile;
	m_layer = Layer::Monster;
	m_strName = L"����������";
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
	
}

void CGotoNextArea::Release()
{
}

void CGotoNextArea::OnCollisionEnter(CCollider* pOtherCollider)
{
	if (pOtherCollider->GetObjName() == L"�÷��̾�")
	{
		//���⼭ ���������� ��Ʈ���� ī��Ʈ HP MP���� �Ѱ��ش�
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
