#pragma once
#include "CGameObject.h"


class CImage;
class CAnimator;

class CDeadExplo :
	public CGameObject
{
public:
	CDeadExplo();
	virtual ~CDeadExplo();

private:

	CAnimator* m_pAnimator;
	CImage* m_Image;
	
	
	float DelTime;
	float Dir[2];



private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	void AnimatorUpdate();

	

public:
	
};