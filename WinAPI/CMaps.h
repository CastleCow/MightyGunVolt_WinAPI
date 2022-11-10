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
	CImage* m_pNextMap;
	CImage* m_pPrevMap;
	Vector m_vecPos;
public:
	CImage* GetIamge();
	void SetImage(CImage* pImage);
	void SetNextMapImage(CImage* pImage);
	void SetPrevMapImage(CImage* pImage);
	
	void SetVecPos(Vector a) { m_vecPos = a; }
	Vector GetVecPos() { return m_vecPos; }
private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
};

