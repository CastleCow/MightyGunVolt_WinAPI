#pragma once
#include "CUI.h"

// �Լ������� : �Լ��� ����Ű�� ������ ������ �Լ��� �����ּҸ� �����ϴ� ����
// ��ȯ�� (*�Լ������� �̸�)(�Ű�������...)
// ex) void (*FuncPointer)(int);
// ����Ű�� �ִ� �Լ��� ȣ���ϱ� ���ؼ��� �Լ������� �̸��� ���ؼ� ����
// ex) FuncPointer(10);
typedef void(*CallbackFunc)(DWORD_PTR, DWORD_PTR);

class CButton : public CUI
{
public:
	CButton();
	virtual ~CButton();

private:
	CallbackFunc	m_pCallback;
	DWORD_PTR		m_pParam1;
	DWORD_PTR		m_pParam2;

	wstring			m_strText;
	float			m_iSizeText;
	Color			m_colorText;

public:
	void SetClickedCallback(CallbackFunc pCallback, DWORD_PTR pParam1, DWORD_PTR pParam2);

	void SetText(const wstring& text, float fontSize = 12, Color color = Color(0, 0, 0, 1));

private:
	void Init() override;
	void Update() override;
	void Render() override;
	void Release() override;

	// final : ���̻� �ڽ��� ������ �Ҽ� ������ ����
	// �θ��� ������ ��ɸ��� ����ϵ��� ����
	// ��ư�� ��� Ŭ���Ͽ� �����ϱ� ���� �뵵�θ� ���
	void OnMouseEnter() final;
	void OnMouseOver() final;
	void OnMouseExit() final;
	void OnMouseUp() final;
	void OnMouseDown() final;
	void OnMouseClicked() final;

	// delete : ���̻� �ش��Լ��� ��� �Ҽ� ������ ����
	// �θ𿡼� ������ ����� �ڽ��� ������� �ʱ⸦ �ٶ���� ���
	void AddChildUI(CUI* pChildUI) = delete;
};

