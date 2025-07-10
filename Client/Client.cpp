
// Client.cpp : 定义应用程序的类行为。
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
// CClientApp 构造

CClientApp::CClientApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CClientApp 对象

CClientApp theApp;


// CClientApp 初始化

BOOL CClientApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	run();

	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	/*
	 //与原有注册信息对比验证
	{
		int type = -1;
		pair<CString, string>SerialNo;
		SerialNo = getSerialNO(type);// 原序列号
		std::string txtx = SerialNo.second;

		if (SerialNo.first.Compare((LPSTR)(LPCTSTR)"信息不匹配") == 0 || txtx == "")
		{
			return FALSE;
		}

		// 原激活码
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
			//使用次数解密
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

			//减少1次使用次数，并写入yt.dat
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
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
		success = true;
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	if (success)
	{
		return TRUE;
	}
	*/
	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}


//BOOL CClientApp::InitInstance()
//{
//	// 如果一个运行在 Windows XP 上的应用程序清单指定要
//	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
//	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
//	INITCOMMONCONTROLSEX InitCtrls;
//	InitCtrls.dwSize = sizeof(InitCtrls);
//	// 将它设置为包括所有要在应用程序中使用的
//	// 公共控件类。
//	InitCtrls.dwICC = ICC_WIN95_CLASSES;
//	InitCommonControlsEx(&InitCtrls);
//
//	CWinApp::InitInstance();
//
//
//	AfxEnableControlContainer();
//
//	// 创建 shell 管理器，以防对话框包含
//	// 任何 shell 树视图控件或 shell 列表视图控件。
//	CShellManager* pShellManager = new CShellManager;
//
//	// 标准初始化
//	// 如果未使用这些功能并希望减小
//	// 最终可执行文件的大小，则应移除下列
//	// 不需要的特定初始化例程
//	// 更改用于存储设置的注册表项
//	// TODO: 应适当修改该字符串，
//	// 例如修改为公司或组织名
//	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
//
//
//	// 与原有注册信息对比验证
//	{
//		int type = -1;
//		pair<CString, string>SerialNo;
//		SerialNo = getSerialNO(type);// 原序列号
//		std::string txtx = SerialNo.second;
//
//		if (SerialNo.first.Compare((LPSTR)(LPCTSTR)"信息不匹配") == 0 || txtx == "")
//		{
//			return FALSE;
//		}
//
//		// 原激活码
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
//		// TODO: 在此放置处理何时用
//		//  “确定”来关闭对话框的代码
//		success = true;
//	}
//	else if (nResponse == IDCANCEL)
//	{
//		// TODO: 在此放置处理何时用
//		//  “取消”来关闭对话框的代码
//	}
//
//	// 删除上面创建的 shell 管理器。
//	if (pShellManager != NULL)
//	{
//		delete pShellManager;
//	}
//
//	if (success)
//	{
//		return TRUE;
//	}
//	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
//	//  而不是启动应用程序的消息泵。
//	return FALSE;
//}

void CClientApp::run() {
	///////////////////////////////////////进程通信初始化//////////////////////////////
#ifndef LZBDEBUG
	printf("开始等待命名管道\n");
	if (WaitNamedPipe(pStrPipeName, NMPWAIT_WAIT_FOREVER) == FALSE)
	{
		printf("Error! 连接命名管道失败\n");
		return;
	}

	printf("打开命名管道\n");
	hPipe = CreateFile(pStrPipeName, GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	printf("向服务端发送数据\n");
	const int BUFFER_MAX_LEN = 256;
	char szBuffer[BUFFER_MAX_LEN];
	DWORD dwLen = 0;
#endif
	bool needRegis = false;
	// 验证环境
	int type = -1;
	pair<CString, string>SerialNo;
	SerialNo = getSerialNO(type);// 原序列号
	std::string txtx = SerialNo.second;

	if (SerialNo.first.Compare((LPSTR)(LPCTSTR)"信息不匹配") == 0 || txtx == "")
	{
		needRegis = true;
	}

	if (!needRegis)
	{
		// 原激活码
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
			//使用次数解密
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
			//减少1次使用次数，并写入yt.dat
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
	// 环境信息不匹配，重新注册
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

	//关闭管道
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
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
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
