#pragma once
#include "CGameObject.h"
class CImage;

class CMaps :
    public CGameObject
{
public:
	CMaps();
	virtual ~CMaps();

private:
	CImage* m_pImage;
	
	Vector m_vecPos;
public:
	CImage* GetIamge();
	void SetImage(CImage* pImage);
	
	void SetVecPos(Vector a) { m_vecPos = a; }
	Vector GetVecPos() { return m_vecPos; }
private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

