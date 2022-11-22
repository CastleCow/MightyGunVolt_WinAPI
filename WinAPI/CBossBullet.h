#pragma once
#include "CGameObject.h"

class CImage;
class CAnimator;

class CBossBullet :
    public CGameObject
{
public:
	CBossBullet();
	virtual ~CBossBullet();

private:
	Vector m_vecDir;
	CAnimator* m_pAnimator;
	CImage* m_Image;
	
	float m_fVelocity;
	float bulDelTime;
	float Dir[2];
	
	bool bulenhace;
	bool m_bIsDel;
private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();

	void OnCollisionEnter(CCollider* pOtherCollider) override;

public:
	void SetDir(Vector dir);
	void SetVelocity(float velocity);
	void SetDelete(bool a) { m_bIsDel = a; }
	void SetBullet(bool a) { bulenhace = a; }
	void MoveCircle();
};

/*
int totalPoint, xPoint, yPoint;
	// �簢 �� �浹 : �簢���� �߽����� ���� ��� ������ �ִ��Ŀ� ���� �ٸ��� ó��
	/*	totalPoint (xPoint, yPoint)

		-4 (-1,-1) | -3 ( 0,-1) | -2 (+1,-1)
		-----------+------------+-----------
		-1 (-1, 0) |  0 ( 0, 0) | +1 (+1, 0)
		-----------+------------+-----------
		+2 (-1,+1) | +3 ( 0,+1) | +4 (+1,+1)
	
if (circlePos.x < rectPos.x - rectScale.x * 0.5f)
	xPoint = -1;
else if (circlePos.x > rectPos.x + rectScale.x * 0.5f)
xPoint = 1;
else
xPoint = 0;

if (circlePos.y < rectPos.y - rectScale.y * 0.5f)
	yPoint = -1;
else if (circlePos.y > rectPos.y + rectScale.y * 0.5f)
yPoint = 1;
else
yPoint = 0;

totalPoint = 3 * yPoint + xPoint;

switch (totalPoint)
	{
	// �簢�� �ȿ� ���� ���� ��� : �׻� �浹
	case 0:
		return true;
		break;
	// �¿쿡 ���� ���� ��� : �簢���� ���� ũ�� + ���� �������� �ѻ����� �Ÿ����� ������� �浹
	case -1:
	case +1:
		if (abs(rectPos.x - circlePos.x) < rectScale.x * 0.5f + circleScale)
			return true;
		break;
	// ���Ͽ� ���� ���� ��� : �簢���� ���� ũ�� + ���� �������� �ѻ����� �Ÿ����� ������� �浹
	case -3:
	case +3:
		if (abs(rectPos.y - circlePos.y) < rectScale.y * 0.5f + circleScale)
			return true;
		break;
	// �簢���� �밢���� ���� ���� ��� : �簢���� �ڳʰ� �� �ȿ� ���� ��� �浹
	case -4:
	case -2:
	case +2:
	case +4:
	{
		float cornerX = (xPoint < 0) ? rectPos.x - rectScale.x * 0.5f : rectPos.x + rectScale.x * 0.5f;
		float cornerY = (yPoint < 0) ? rectPos.y - rectScale.y * 0.5f : rectPos.y + rectScale.y * 0.5f;
		if (pow(cornerX - circlePos.x, 2) + pow(cornerY - circlePos.y, 2)
			< pow(circleScale, 2))
			return true;
		break;
	}
	}

	return false;

*/