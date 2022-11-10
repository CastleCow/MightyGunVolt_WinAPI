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
	// CUI��(��) ���� ��ӵ�
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;
	

	// CUI��(��) ���� ��ӵ�
	virtual void OnMouseEnter() override;

	virtual void OnMouseOver() override;

	virtual void OnMouseExit() override;

	virtual void OnMouseUp() override;

	virtual void OnMouseDown() override;

	virtual void OnMouseClicked() override;

};

