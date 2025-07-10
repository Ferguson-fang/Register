
// ServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <time.h> 
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DynamicEncryption.h"
#include "DesTest.h"



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CServerDlg 对话框




CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CServerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CServerDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// CServerDlg 消息处理程序

BOOL CServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//CFont MyFont; 
	MyFont.CreatePointFont(200,_T("隶书"));
	GetDlgItem(IDC_STATIC1)->SetFont(&MyFont);
	//MyFont.DeleteObject();
	MyFont2.CreatePointFont(120,_T("宋体"));
	GetDlgItem(IDC_STATIC2)->SetFont(&MyFont2);
	GetDlgItem(IDC_STATIC3)->SetFont(&MyFont2);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString m_MachineId;
	GetDlgItem(IDC_CN)->GetWindowText(m_MachineId);
	if (m_MachineId.GetLength() != 24)
	{
		MessageBox(_T("请输入24位字符"), NULL, NULL);
		return;
	}

	CString desStr1 = m_MachineId.Left(16);
	//CString desStr2 = m_MachineId.Mid(16,16);
	CString mkey = m_MachineId.Right(8); //取得的明文

	//获取使用次数
	CString leftTime;
	BOOL isInfinite;
	GetDlgItem(IDC_SN2)->GetWindowText(leftTime);
	isInfinite = IsDlgButtonChecked(IDC_CHECK1);
	if (leftTime.GetLength() == 0 && !isInfinite)
	{
		MessageBox(_T("请输入使用次数"), NULL, NULL);
		return;
	}

	/****************DES 解密***************************/
	CDesTest Dencryption1(mkey);		    //CDesTest Dencryption2(mkey);
	Dencryption1.initial();			        //Dencryption2.initial();	
	Dencryption1.jiqimaerjinzhi(desStr1);  // Dencryption2.jiqimaerjinzhi(desStr2);
	//DES解密，恢复原文
	Dencryption1.DESJIEMI();		        //Dencryption2.DESJIEMI();
	//Dencryption1.YUANWEN += Dencryption2.YUANWEN;

	//GetDlgItem(IDC_MD5)->SetWindowText(Dencryption1.YUANWEN);

	//产生随机数
	int randomNumber[8];
	//cout<<"生成8个0~9的随机数："<<endl; 
	//一共插入8位伪码，获取使用次数的位数，生成随机数的个数为8 - n，n为使用次数的位数
	int n = leftTime.GetLength();

	for (int i = 0; i != (7 - n); ++i)
		randomNumber[i] = rand() % 10;

	int j = 0;
	CString zhuceNumber(Dencryption1.YUANWEN);
	
	//如果无限次使用，第0位插入0，否则插入位数
	if (isInfinite)
	{
		zhuceNumber.Insert(0, '0');
	}
	else {
		zhuceNumber.Insert(0, static_cast<TCHAR>('0' + n));
	}
	for (int i = 2; i < 2 * (n+1); i = i + 2)
	{
		zhuceNumber.Insert(i, leftTime.GetAt(j++));
	}
	for (int i = 2 * (n+1); i < 16; i = i + 2)
	{
		zhuceNumber.Insert(i, static_cast<TCHAR>('0' + randomNumber[i]));
	}
	GetDlgItem(IDC_SN)->SetWindowText(zhuceNumber);
	return;
}



//void CServerDlg::OnBnClickedOk()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString m_MachineId;
//	GetDlgItem(IDC_CN)->GetWindowText(m_MachineId);
//	if (m_MachineId.GetLength()!= 24)
//	{
//		MessageBox(_T("请输入24位字符"),NULL,NULL);
//		return ;
//	}
//
//	CString desStr1 = m_MachineId.Left(16);
//	//CString desStr2 = m_MachineId.Mid(16,16);
//	CString mkey = m_MachineId.Right(8); //取得的明文
//	
//	/****************DES 解密***************************/
//	CDesTest Dencryption1(mkey);		    //CDesTest Dencryption2(mkey);
//	Dencryption1.initial();			        //Dencryption2.initial();	
//	Dencryption1.jiqimaerjinzhi(desStr1);  // Dencryption2.jiqimaerjinzhi(desStr2);
//	//DES解密，恢复原文
//	Dencryption1.DESJIEMI();		        //Dencryption2.DESJIEMI();
//	//Dencryption1.YUANWEN += Dencryption2.YUANWEN;
//
//	//GetDlgItem(IDC_MD5)->SetWindowText(Dencryption1.YUANWEN);
//
//	//产生随机数
//	int randomNumber[8];
//	//cout<<"生成8个0~9的随机数："<<endl; 
//	srand((unsigned)time(NULL));
//	for (int i = 0; i != 8; ++i)
//		randomNumber[i] = rand() % 10;
//
//	int j = 0;
//	CString zhuceNumber(Dencryption1.YUANWEN);
//	char* pBuf = (char*)malloc(2 * sizeof(char));
//	for (int i = 0; i < 16; i = i + 2)
//	{
//		_itoa(randomNumber[j++], pBuf, 10);
//		zhuceNumber.Insert(i, *pBuf);
//	}
//	CString strTemp = zhuceNumber;
//	GetDlgItem(IDC_SN)->SetWindowText(strTemp);
//	int a = strlen(pBuf);
//	free(pBuf);
//	return;
//}



void CServerDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	bool isInfinite = IsDlgButtonChecked(IDC_CHECK1);
	GetDlgItem(IDC_SN2)->EnableWindow(!isInfinite);
}
