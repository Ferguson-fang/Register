
// Client.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "regis.h"
#include <iostream>
#include <fstream>
#include <string>
#include <io.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DynamicEncryption.h"
#include "DesTest.h"

#define PATH1 "C:\\Windows\\cdata"
#define PATH2 "C:\\cdata"
#define PATH3 "D:\\cdata"

// CClientApp

BEGIN_MESSAGE_MAP(CClientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

const char* pStrPipeName = "\\\\.\\pipe\\fcg_Pipe";
HANDLE hPipe;
string path = "";
// CClientApp ����

CClientApp::CClientApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CClientApp ����

CClientApp theApp;


// CClientApp ��ʼ��

BOOL CClientApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	run();

	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	/*
	 //��ԭ��ע����Ϣ�Ա���֤
	{
		int type = -1;
		pair<CString, string>SerialNo;
		SerialNo = getSerialNO(type);// ԭ���к�
		std::string txtx = SerialNo.second;

		if (SerialNo.first.Compare((LPSTR)(LPCTSTR)"��Ϣ��ƥ��") == 0 || txtx == "")
		{
			return FALSE;
		}

		// ԭ������
		string ac = "";
		fstream f("ym.dat",ios::in);
		f >> ac;
		f.close();

		string lt = "";
		fstream file("yt.dat", ios::in);
		file >> lt;
		file.close();
		CString leftTimeFromFile;
		CString desStr1,mkey;
		if (file)
		{
			//ʹ�ô�������
			CString useTime(lt.c_str());
			desStr1 = useTime.Left(16);
			mkey = useTime.Right(8);

			CDesTest Dencryption1(mkey);
			Dencryption1.initialJIEMI();
			Dencryption1.jiqimaerjinzhi(desStr1);
			Dencryption1.DESJIEMI();

			CString YUANWEN(Dencryption1.YUANWEN);
			int j = 0;
			while (YUANWEN.GetAt(j) != 'a')
			{
				leftTimeFromFile.AppendChar(YUANWEN.GetAt(j));
				j++;
			}
			lt = leftTimeFromFile.GetString();
		}



		bool bWorking = false;
		bool hasLeftTime = false;
		int leftTimes = 0;
		if (ac != "")
			bWorking = isRegisSuccess((CString)ac.c_str(), SerialNo.first);
		
		if (lt != "")
		{
			if (lt == "-1")
				hasLeftTime = true;
			else
			{
				leftTimes = stoi(lt) - 1;
				hasLeftTime = leftTimes > 0;
			}
		}

		if (bWorking && hasLeftTime)
		{
			string time = to_string(leftTimes);
			CString count(time.c_str());
			CString encryption;
			encryption.Append(count);
			while (encryption.GetLength() < 8)
			{
				encryption.AppendChar('a');
			}
			CDesTest DesTest1(encryption, mkey);
			DesTest1.initial();
			DesTest1.DESDIEDAI();
			DesTest1.MEWEN += mkey;

			//����1��ʹ�ô�������д��yt.dat
			fstream rfile;
			rfile.open("yt.dat", ios::out);
			rfile << DesTest1.MEWEN.GetString() << '\n';
			rfile.close();
			return TRUE;	
		}
	}
	
	CClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	bool success = false;
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
		success = true;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	if (success)
	{
		return TRUE;
	}
	*/
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


//BOOL CClientApp::InitInstance()
//{
//	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
//	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
//	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
//	INITCOMMONCONTROLSEX InitCtrls;
//	InitCtrls.dwSize = sizeof(InitCtrls);
//	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
//	// �����ؼ��ࡣ
//	InitCtrls.dwICC = ICC_WIN95_CLASSES;
//	InitCommonControlsEx(&InitCtrls);
//
//	CWinApp::InitInstance();
//
//
//	AfxEnableControlContainer();
//
//	// ���� shell ���������Է��Ի������
//	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
//	CShellManager* pShellManager = new CShellManager;
//
//	// ��׼��ʼ��
//	// ���δʹ����Щ���ܲ�ϣ����С
//	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
//	// ����Ҫ���ض���ʼ������
//	// �������ڴ洢���õ�ע�����
//	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
//	// �����޸�Ϊ��˾����֯��
//	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
//
//
//	// ��ԭ��ע����Ϣ�Ա���֤
//	{
//		int type = -1;
//		pair<CString, string>SerialNo;
//		SerialNo = getSerialNO(type);// ԭ���к�
//		std::string txtx = SerialNo.second;
//
//		if (SerialNo.first.Compare((LPSTR)(LPCTSTR)"��Ϣ��ƥ��") == 0 || txtx == "")
//		{
//			return FALSE;
//		}
//
//		// ԭ������
//		string ac = "";
//		fstream f("ym.dat", ios::in);
//		f >> ac;
//		f.close();
//
//		bool bWorking = false;
//		if (ac != "")
//			bWorking = isRegisSuccess((CString)ac.c_str(), SerialNo.first);
//		if (bWorking)
//		{
//			return TRUE;
//		}
//	}
//
//	CClientDlg dlg;
//	m_pMainWnd = &dlg;
//	INT_PTR nResponse = dlg.DoModal();
//
//	bool success = false;
//	if (nResponse == IDOK)
//	{
//		// TODO: �ڴ˷��ô����ʱ��
//		//  ��ȷ�������رնԻ���Ĵ���
//		success = true;
//	}
//	else if (nResponse == IDCANCEL)
//	{
//		// TODO: �ڴ˷��ô����ʱ��
//		//  ��ȡ�������رնԻ���Ĵ���
//	}
//
//	// ɾ�����洴���� shell ��������
//	if (pShellManager != NULL)
//	{
//		delete pShellManager;
//	}
//
//	if (success)
//	{
//		return TRUE;
//	}
//	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
//	//  ����������Ӧ�ó������Ϣ�á�
//	return FALSE;
//}

void CClientApp::run() {
	///////////////////////////////////////����ͨ�ų�ʼ��//////////////////////////////
#ifndef LZBDEBUG
	printf("��ʼ�ȴ������ܵ�\n");
	if (WaitNamedPipe(pStrPipeName, NMPWAIT_WAIT_FOREVER) == FALSE)
	{
		printf("Error! ���������ܵ�ʧ��\n");
		return;
	}

	printf("�������ܵ�\n");
	hPipe = CreateFile(pStrPipeName, GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	printf("�����˷�������\n");
	const int BUFFER_MAX_LEN = 256;
	char szBuffer[BUFFER_MAX_LEN];
	DWORD dwLen = 0;
#endif
	bool needRegis = false;
	// ��֤����
	int type = -1;
	pair<CString, string>SerialNo;
	SerialNo = getSerialNO(type);// ԭ���к�
	std::string txtx = SerialNo.second;

	if (SerialNo.first.Compare((LPSTR)(LPCTSTR)"��Ϣ��ƥ��") == 0 || txtx == "")
	{
		needRegis = true;
	}

	if (!needRegis)
	{
		// ԭ������
		string ac = "";
		fstream f("ym.dat", ios::in);
		f >> ac;
		f.close();

		string lt = "";
		fstream file("yt.dat", ios::in);
		file >> lt;
		file.close();
		CString leftTimeFromFile;
		CString desStr1, mkey;
		if (file)
		{
			//ʹ�ô�������
			CString useTime(lt.c_str());
			desStr1 = useTime.Left(16);
			mkey = useTime.Right(8);

			CDesTest Dencryption1(mkey);
			Dencryption1.initialJIEMI();
			Dencryption1.jiqimaerjinzhi(desStr1);
			Dencryption1.DESJIEMI();

			CString YUANWEN(Dencryption1.YUANWEN);
			int j = 0;
			while (YUANWEN.GetAt(j) != 'a')
			{
				leftTimeFromFile.AppendChar(YUANWEN.GetAt(j));
				j++;
			}
			lt = leftTimeFromFile.GetString();
		}

		bool bWorking = false;
		bool hasLeftTime = false;
		int leftTimes = 0;
		if (ac != "")
			bWorking = isRegisSuccess((CString)ac.c_str(), SerialNo.first);

		if (lt != "")
		{
			if (lt == "-1")
			{
				hasLeftTime = true;
				leftTimes = -1;
			}
			else
			{
				leftTimes = stoi(lt) - 1;
				hasLeftTime = leftTimes > 0;
			}
		}

		if (bWorking && hasLeftTime)
		{
			/*string time = to_string(leftTimes);
			if (lt == "-1")
				time = lt;*/
			string time = to_string(leftTimes);
			CString count(time.c_str());
			CString encryption;
			encryption.Append(count);
			while (encryption.GetLength() < 8)
			{
				encryption.AppendChar('a');
			}
			CDesTest DesTest1(encryption, mkey);
			DesTest1.initial();
			DesTest1.DESDIEDAI();
			DesTest1.MEWEN += mkey;
			//����1��ʹ�ô�������д��yt.dat
			fstream rfile;
			rfile.open("yt.dat", ios::out);
			rfile << DesTest1.MEWEN.GetString() << '\n';
			rfile.close();
#ifndef LZBDEBUG
			sprintf(szBuffer, "%s", "lefttime");
			if (!WriteFile(hPipe, szBuffer, strlen(szBuffer) + 1, &dwLen, NULL))
			{
				TRACE("Client Write File to Pipe Failed...");
				return;
			}
#endif
		}
		else
			needRegis = true;
	}
	bool regisRes = true;
	// ������Ϣ��ƥ�䣬����ע��
	if (needRegis)
	{
		regisRes = regist();
	}


#ifndef LZBDEBUG
	sprintf(szBuffer, "%s", "ClientExit");
	if (!WriteFile(hPipe, szBuffer, strlen(szBuffer) + 1, &dwLen, NULL))
	{
		return;
	}
#endif

	//�رչܵ�
	CloseHandle(hPipe);
}

bool CClientApp::regist() {
	const int BUFFER_MAX_LEN = 256;
	char szBuffer[BUFFER_MAX_LEN];
	DWORD dwLen = 0;
#ifndef LZBDEBUG
	sprintf(szBuffer, "%s", "EnterRegistered");
	if (!WriteFile(hPipe, szBuffer, strlen(szBuffer) + 1, &dwLen, NULL))
	{
		return FALSE;
	}
#endif

	CClientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
#ifndef LZBDEBUG
		sprintf(szBuffer, "%s", "lefttime");
		if (!WriteFile(hPipe, szBuffer, strlen(szBuffer) + 1, &dwLen, NULL))
		{
			TRACE("Client Write File to Pipe Failed...");
			return false;
		}
#endif
		return true;
	}
	else if (nResponse == IDCANCEL)
	{
#ifndef LZBDEBUG
		sprintf(szBuffer, "%s", "ExitRegistered");
		if (!WriteFile(hPipe, szBuffer, strlen(szBuffer) + 1, &dwLen, NULL))
		{
			return FALSE;
		}
#endif
		return false;
	}

	return false;
}
