
// ClientDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MyDiskInfo.h"
#include "MD5.h"
#include "DynamicEncryption.h"
#include "DesTest.h"

using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

CString sz_str;//比较值
CString sz_strHardware;//比较值
int nType = -1;//第几种
string nTx = "";//

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


// CClientDlg 对话框




CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CClientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_REGIS, &CClientDlg::OnBnClickedBtnRegis)
	ON_BN_CLICKED(IDCANCEL, &CClientDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CClientDlg 消息处理程序

BOOL CClientDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint()
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CClientDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	sz_str.Empty();
	CMyDiskInfo DiskInfo;
	CString disk_info, cpu_info, mac_info;
	//获取cpu ID
	cpu_info = DiskInfo.GetCPUID();
	//GetDlgItem(IDC_EDIT_CPU)->SetWindowText(cpu_info);

	//获取网卡的MAC
	mac_info = DiskInfo.GetMAC();
	//GetDlgItem(IDC_EDIT_MAC)->SetWindowText(mac_info);

	//获取硬盘ID

	/*int b = DiskInfo.GetDiskInfo();
	if (b == 0)
	{
		disk_info = DiskInfo.szSerialNumber;
	}
	else
		disk_info = "";*/

	//wmic方式获取磁盘ID
	int w = DiskInfo.GetDiskSerialNumber();
	if (w == 0)
	{
		disk_info = DiskInfo.serialNumber.data();
	}
	else
		disk_info = "";
	//m_edit->SetWindowTextA(DiskInfo.szModelNumber);	
	//GetDlgItem(IDC_EDIT_HD)->SetWindowText(disk_info);

	string tx = "";
	int type = -1;

	//CString info;
	//if (type == -1 || tx == "")
	//{
	//	type = 0;
	//	info = cpu_info;     //用于加密的信息
	//	if (info.IsEmpty())
	//	{
	//		info = mac_info;
	//		type = 1;
	//		if (info.IsEmpty())
	//		{
	//			info = disk_info;
	//			type = 2;
	//			if (info.IsEmpty())
	//			{
	//				type = -1;
	//				return;
	//			}
	//		}
	//	}
	//}
	CString info;
	CString random[3] = { cpu_info, mac_info,disk_info };
	//0代表cpu 1代表网络地址 2代表硬盘信息
	if (type == -1 || tx == "")
	{
		// 使用当前时间作为种子，初始化随机数生成器
		srand(static_cast<unsigned int>(time(0)));

		while (info.IsEmpty())
		{
			// 生成 0 到 2 之间的随机数
			int random_number = rand() % 3;
			info = random[random_number];
			type = random_number;
		}
		if (info.IsEmpty())
		{
			type = -1;
			return;
		}
		
	}
	if (type != -1 && tx == "")
	{
		CTime m_time;
		CTime c_time;
		c_time = m_time.GetCurrentTime();
		CString temp = c_time.Format("%Y%m%d%H%M%S");
		USES_CONVERSION;
		string tx_temp = temp.GetBuffer();
		string temp1 = tx_temp.substr(0, 1);
		string temp2 = tx_temp.substr(1, 1);
		string temp3 = tx_temp.substr(2, 1);
		string temp4 = tx_temp.substr(3, 2);
		string temp5 = tx_temp.substr(5, 2);
		string temp6 = tx_temp.substr(7, 4);
		string temp7 = tx_temp.substr(11, 3);

		tx = temp7 + temp1 + temp5 + temp4 + temp6 + temp3;
	}

	if (info.IsEmpty() || tx == "")
	{
		type = -1;
		return;
	}

	CString hardwareInfo = info.GetString();
	info = info + (CString)tx.c_str();

	/************************MD5加密*********************************/
	//这里只是对硬盘进行加密啊
	//char szDigest[16];   //加密后的字符
	char *encrypt = (LPSTR)(LPCTSTR)info;//Cstring转char*
	sz_str = md5(encrypt).c_str();

	char *encryptTemp = (LPSTR)(LPCTSTR)hardwareInfo;//Cstring转char*
	sz_strHardware = md5(encryptTemp).c_str();

	//for (UINT i =0;i < strlen(encrypt);i++)			//一个字节是两个十六进制数
	//{
	//	CString str;
	//	str.Format("%02x",encrypt[i]);
	//	sz_str += str;
	//}

	//GetDlgItem(IDC_EDIT_MD5)->SetWindowText(sz_str);//MD5值32位

	//随机矩阵处理时间数据     (产生秘钥)
	CDynamicEncryption dynamic;
	CTime m_time; CTime c_time;
	c_time = m_time.GetCurrentTime();
	CString strTime = c_time.Format("%Y%m%d%H%M%S");
	int len = strTime.GetLength();
	CString output_time1, output_time2;
	dynamic.EncryptFunc1(strTime, output_time1);
	dynamic.EncryptFunc2(output_time1, output_time2);
	CString key = output_time2.Right(8);				//取时间为明文，但是加密后的后八位为密钥

	/****************DES 加密***************************/

	CString md5Str1 = sz_str.Mid(2, 8);
	//CString md5Str2 = sz_str.Mid(12,8);
	//分别进行加密
	CDesTest DesTest1(md5Str1, key);  //CDesTest DesTest2(md5Str2,key);
	DesTest1.initial();				 //DesTest2.initial();
	//加密
	DesTest1.DESDIEDAI();			 //DesTest2.DESDIEDAI();
	//显示密文
	//DesTest1.MEWEN += DesTest2.MEWEN;
	//GetDlgItem(IDC_EDIT_DES)->SetWindowText(DesTest1.MEWEN);
	DesTest1.MEWEN += key;
	GetDlgItem(IDC_EDIT_NUM)->SetWindowText(DesTest1.MEWEN);
	nType = type;
	nTx = tx;
}


//05B2E519788ACC7ANIGGHIJH
//2181c36840d7f76494601e9b0ad37f33
//58715c7326488480


void CClientDlg::OnBnClickedBtnRegis()
{
	//sz_str.Empty();
	//GetDlgItem(IDC_EDIT_MD5)->GetWindowText(sz_str);

	CString md5Str1 = sz_str.GetString();

	CString registernum;
	CString output_time1;
	GetDlgItem(IDC_EDIT_REGIS)->GetWindowText(registernum);
	if (registernum.GetLength() < 16)
	{
		MessageBox("注册码有误");
		return;
	}
	CDynamicEncryption dynamic;
	CString desStr1 = registernum.Left(16);//用于比对是否注册成功

	/*********************将原文逆（小）变换************************/
	int len = desStr1.GetLength();

	//取第一位数查看是否无数次
	char first = desStr1.GetAt(0);
	CString count = "";
	if (first != '0')
	{
		int n = first - '0';
		for (int i = 2; i <= 2 * n; i += 2)
		{
			count.AppendChar(desStr1.GetAt(i));
		}
	}
	else
	{
		//无数次使用的话count为-1
		count = "-1";
	}
	int i=len-2;
	//char tempchar = registernum.GetAt(i);
	for(;i>=0;i-=2)
	{
		desStr1.Delete(i);
	}

	//registernum.SetAt(i,tempchar);

	//if((registernum.Left(8)==sz_str.Mid(2,8))&&(registernum.Right(8)==sz_str.Mid(12,8)))
	if (desStr1.Left(8) == sz_str.Mid(2, 8))
	{


		//随机矩阵处理时间数据     (产生秘钥)
		CDynamicEncryption dynamic;
		CTime m_time; CTime c_time;
		c_time = m_time.GetCurrentTime();
		CString strTime = c_time.Format("%Y%m%d%H%M%S");
		int len = strTime.GetLength();
		CString output_time1, output_time2;
		dynamic.EncryptFunc1(strTime, output_time1);
		dynamic.EncryptFunc2(output_time1, output_time2);
		CString key = output_time2.Right(8);				//取时间为明文，但是加密后的后八位为密钥

		//对使用次数进行加密
		CString encryption;
		encryption.Append(count);
		while (encryption.GetLength() < 8)
		{
			encryption.AppendChar('a');
		}
		CDesTest DesTest1(encryption, key);
		DesTest1.initial();
		DesTest1.DESDIEDAI();
		DesTest1.MEWEN += key;





		string aa = CT2A(registernum.GetString());
		fstream f("ym.dat", ios::out);
		f << aa << '\n';
		f.close();

		fstream rfile;
		rfile.open("yx.dat", ios::out);
		rfile << nType << " " << nTx << '\n';
		rfile.close();

		fstream file;
		file.open("yt.dat", ios::out);
		file << DesTest1.MEWEN << '\n';
		file.close();
		/*fstream file;
		file.open("yt.dat", ios::out);
		file << count << '\n';
		file.close();*/

		MessageBox("注册成功！");
		CDialogEx::OnOK();
	}
	else  MessageBox("注册失败！");

	// TODO: 在此添加控件通知处理程序代码
}

//单个字符异或运算
char CClientDlg::MakecodeChar(char c, int key){
	return c = c^key;
}
//单个字符解密
char CClientDlg::CutcodeChar(char c, int key){
	return c^key;
}

//加密
void CClientDlg::Makecode(char *pstr, int *pkey){
	int len = strlen(pstr);//获取长度
	for (int i = 0; i < len; i++)
		*(pstr + i) = MakecodeChar(*(pstr + i), pkey[i % 5]);
}
//解密
void CClientDlg::Cutecode(char *pstr, int *pkey){
	int len = strlen(pstr);
	for (int i = 0; i < len; i++)
		*(pstr + i) = CutcodeChar(*(pstr + i), pkey[i % 5]);
}

/*加密子函数开始*/
void CClientDlg::dofile(char *in_fname, char *pwd, char *out_file)
{
	FILE *fp1, *fp2;
	register char ch;
	int j = 0;
	int j0 = 0;

	fp1 = fopen(in_fname, "rb");
	if (fp1 == NULL){
		printf("cannot open in-file./n");
		exit(1);/*如果不能打开要加密的文件,便退出程序*/
	}
	fp2 = fopen(out_file, "wb");
	if (fp2 == NULL){
		printf("cannot open or create out-file./n");
		exit(1);/*如果不能建立加密后的文件,便退出*/
	}
	while (pwd[++j0]);
	ch = fgetc(fp1);

	/*加密算法开始*/
	while (!feof(fp1)){
		fputc(ch^pwd[j >= j0 ? j = 0 : j++], fp2);/*异或后写入fp2文件*/
		ch = fgetc(fp1);
	}
	fclose(fp1);/*关闭源文件*/
	fclose(fp2);/*关闭目标文件*/
}


void CClientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
