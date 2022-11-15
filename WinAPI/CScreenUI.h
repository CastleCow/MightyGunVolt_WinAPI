#pragma once
#include "CUI.h"
class CImage;
class CScreenUI : public CUI
{

public:
	CScreenUI();
	virtual ~CScreenUI();

	void SetHp(float a) { Hp = a; }
	float GetHP() { return Hp; }
	void SetMp(float a) { Mp = a; }
	float GetMP() { return Mp; }
private:
	CImage* m_Hpbar;
	CImage* m_MP;
	CImage* m_PIcon;
	CImage* m_SideBar;

	float UpTime=0;
	float Hp = 0;
	float Mp = 6;
	float alpha[6] = { 1 };
	int RetryCount = 0;
	int min = 0;
	wstring Timer = L"";

private:
	// CUI을(를) 통해 상속됨
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	

	// CUI을(를) 통해 상속됨
	virtual void OnMouseEnter() override;

	virtual void OnMouseOver() override;

	virtual void OnMouseExit() override;

	virtual void OnMouseUp() override;

	virtual void OnMouseDown() override;

	virtual void OnMouseClicked() override;

};

