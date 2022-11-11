#include "framework.h"
#include "CNextMapTile.h"
#include"WinAPI.h"
CNextMapTile::CNextMapTile()
{
	m_strName = L"������";
}

CNextMapTile::~CNextMapTile()
{
}

void CNextMapTile::Init()
{
	CTile::Init();

	AddCollider(ColliderType::Rect,
		Vector(CTile::TILESIZE, CTile::TILESIZE),
		Vector(CTile::TILESIZE / 2, CTile::TILESIZE / 2));
}

void CNextMapTile::Update()
{
	CTile::Update();
}

void CNextMapTile::Render()
{
	CTile::Render();

	ComponentRender();
}

void CNextMapTile::Release()
{
	CTile::Release();
}

void CNextMapTile::OnCollisionEnter(CCollider* pOther)
{
	// �����ʰ� �浹���� ��� ó��
	Logger::Debug(L"���������� �̵�");

}

void CNextMapTile::OnCollisionStay(CCollider* pOther)
{
}

void CNextMapTile::OnCollisionExit(CCollider* pOther)
{
}
