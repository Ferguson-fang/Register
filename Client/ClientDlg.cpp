
// ClientDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

CString sz_str;//�Ƚ�ֵ
CString sz_strHardware;//�Ƚ�ֵ
int nType = -1;//�ڼ���
string nTx = "";//

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CClientDlg �Ի���




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


// CClientDlg ��Ϣ�������

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CClientDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sz_str.Empty();
	CMyDiskInfo DiskInfo;
	CString disk_info, cpu_info, mac_info;
	//��ȡcpu ID
	cpu_info = DiskInfo.GetCPUID();
	//GetDlgItem(IDC_EDIT_CPU)->SetWindowText(cpu_info);

	//��ȡ������MAC
	mac_info = DiskInfo.GetMAC();
	//GetDlgItem(IDC_EDIT_MAC)->SetWindowText(mac_info);

	//��ȡӲ��ID

	/*int b = DiskInfo.GetDiskInfo();
	if (b == 0)
	{
		disk_info = DiskInfo.szSerialNumber;
	}
	else
		disk_info = "";*/

	//wmic��ʽ��ȡ����ID
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
	//	info = cpu_info;     //���ڼ��ܵ���Ϣ
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
	//0����cpu 1���������ַ 2����Ӳ����Ϣ
	if (type == -1 || tx == "")
	{
		// ʹ�õ�ǰʱ����Ϊ���ӣ���ʼ�������������
		srand(static_cast<unsigned int>(time(0)));

		while (info.IsEmpty())
		{
			// ���� 0 �� 2 ֮��������
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

	/************************MD5����*********************************/
	//����ֻ�Ƕ�Ӳ�̽��м��ܰ�
	//char szDigest[16];   //���ܺ���ַ�
	char *encrypt = (LPSTR)(LPCTSTR)info;//Cstringתchar*
	sz_str = md5(encrypt).c_str();

	char *encryptTemp = (LPSTR)(LPCTSTR)hardwareInfo;//Cstringתchar*
	sz_strHardware = md5(encryptTemp).c_str();

	//for (UINT i =0;i < strlen(encrypt);i++)			//һ���ֽ�������ʮ��������
	//{
	//	CString str;
	//	str.Format("%02x",encrypt[i]);
	//	sz_str += str;
	//}

	//GetDlgItem(IDC_EDIT_MD5)->SetWindowText(sz_str);//MD5ֵ32λ

	//���������ʱ������     (������Կ)
	CDynamicEncryption dynamic;
	CTime m_time; CTime c_time;
	c_time = m_time.GetCurrentTime();
	CString strTime = c_time.Format("%Y%m%d%H%M%S");
	int len = strTime.GetLength();
	CString output_time1, output_time2;
	dynamic.EncryptFunc1(strTime, output_time1);
	dynamic.EncryptFunc2(output_time1, output_time2);
	CString key = output_time2.Right(8);				//ȡʱ��Ϊ���ģ����Ǽ��ܺ�ĺ��λΪ��Կ

	/****************DES ����***************************/

	CString md5Str1 = sz_str.Mid(2, 8);
	//CString md5Str2 = sz_str.Mid(12,8);
	//�ֱ���м���
	CDesTest DesTest1(md5Str1, key);  //CDesTest DesTest2(md5Str2,key);
	DesTest1.initial();				 //DesTest2.initial();
	//����
	DesTest1.DESDIEDAI();			 //DesTest2.DESDIEDAI();
	//��ʾ����
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
		MessageBox("ע��������");
		return;
	}
	CDynamicEncryption dynamic;
	CString desStr1 = registernum.Left(16);//���ڱȶ��Ƿ�ע��ɹ�

	/*********************��ԭ���棨С���任************************/
	int len = desStr1.GetLength();

	//ȡ��һλ���鿴�Ƿ�������
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
		//������ʹ�õĻ�countΪ-1
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


		//���������ʱ������     (������Կ)
		CDynamicEncryption dynamic;
		CTime m_time; CTime c_time;
		c_time = m_time.GetCurrentTime();
		CString strTime = c_time.Format("%Y%m%d%H%M%S");
		int len = strTime.GetLength();
		CString output_time1, output_time2;
		dynamic.EncryptFunc1(strTime, output_time1);
		dynamic.EncryptFunc2(output_time1, output_time2);
		CString key = output_time2.Right(8);				//ȡʱ��Ϊ���ģ����Ǽ��ܺ�ĺ��λΪ��Կ

		//��ʹ�ô������м���
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

		MessageBox("ע��ɹ���");
		CDialogEx::OnOK();
	}
	else  MessageBox("ע��ʧ�ܣ�");

	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�����ַ��������
char CClientDlg::MakecodeChar(char c, int key){
	return c = c^key;
}
//�����ַ�����
char CClientDlg::CutcodeChar(char c, int key){
	return c^key;
}

//����
void CClientDlg::Makecode(char *pstr, int *pkey){
	int len = strlen(pstr);//��ȡ����
	for (int i = 0; i < len; i++)
		*(pstr + i) = MakecodeChar(*(pstr + i), pkey[i % 5]);
}
//����
void CClientDlg::Cutecode(char *pstr, int *pkey){
	int len = strlen(pstr);
	for (int i = 0; i < len; i++)
		*(pstr + i) = CutcodeChar(*(pstr + i), pkey[i % 5]);
}

/*�����Ӻ�����ʼ*/
void CClientDlg::dofile(char *in_fname, char *pwd, char *out_file)
{
	FILE *fp1, *fp2;
	register char ch;
	int j = 0;
	int j0 = 0;

	fp1 = fopen(in_fname, "rb");
	if (fp1 == NULL){
		printf("cannot open in-file./n");
		exit(1);/*������ܴ�Ҫ���ܵ��ļ�,���˳�����*/
	}
	fp2 = fopen(out_file, "wb");
	if (fp2 == NULL){
		printf("cannot open or create out-file./n");
		exit(1);/*������ܽ������ܺ���ļ�,���˳�*/
	}
	while (pwd[++j0]);
	ch = fgetc(fp1);

	/*�����㷨��ʼ*/
	while (!feof(fp1)){
		fputc(ch^pwd[j >= j0 ? j = 0 : j++], fp2);/*����д��fp2�ļ�*/
		ch = fgetc(fp1);
	}
	fclose(fp1);/*�ر�Դ�ļ�*/
	fclose(fp2);/*�ر�Ŀ���ļ�*/
}


void CClientDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
