#pragma once

//============================================
//## Logger (Visual Studio ���â�� ����ǥ��	##
//============================================

class Logger
{
private:
	static void Log(const wchar_t tag[], const wchar_t content[])
	{
		SYSTEMTIME st;
		GetLocalTime(&st);

		WCHAR str[30];
		swprintf_s(str, L"%d/%d/%d %02d:%02d:%02d",
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

		OutputDebugStringW(str);
		OutputDebugStringW(L" ");
		OutputDebugStringW(tag);
		OutputDebugStringW(L" ");
		OutputDebugStringW(content);
		OutputDebugStringW(L"\n");
	}
public:
	static void Debug(wstring content)
	{
#ifdef _DEBUG	// ���� ������ Debug�� ��� ����
		Log(L"[Debug]", content.c_str());
#endif
	}

	static void Info(wstring content)
	{
		Log(L"[ Info]", content.c_str());
	}

	static void Warning(wstring content)
	{
		Log(L"[ Warn]", content.c_str());
	}

	static void Error(wstring content)
	{
		Log(L"[Error]", content.c_str());
	}
};