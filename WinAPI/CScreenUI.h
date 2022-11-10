#pragma once
#include "CUI.h"
class CImage;
class CScreenUI : public CUI
{

public:
	CScreenUI();
	virtual ~CScreenUI();

	
private:
	CImage* m_Hpbar;
	CImage* m_PIcon;
	CImage* m_SideBar;

	float UpTime=0;
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

