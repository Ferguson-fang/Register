
// ServerDlg.cpp : ʵ���ļ�
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



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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


// CServerDlg �Ի���




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


// CServerDlg ��Ϣ�������

BOOL CServerDlg::OnInitDialog()
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
	//CFont MyFont; 
	MyFont.CreatePointFont(200,_T("����"));
	GetDlgItem(IDC_STATIC1)->SetFont(&MyFont);
	//MyFont.DeleteObject();
	MyFont2.CreatePointFont(120,_T("����"));
	GetDlgItem(IDC_STATIC2)->SetFont(&MyFont2);
	GetDlgItem(IDC_STATIC3)->SetFont(&MyFont2);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CServerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString m_MachineId;
	GetDlgItem(IDC_CN)->GetWindowText(m_MachineId);
	if (m_MachineId.GetLength() != 24)
	{
		MessageBox(_T("������24λ�ַ�"), NULL, NULL);
		return;
	}

	CString desStr1 = m_MachineId.Left(16);
	//CString desStr2 = m_MachineId.Mid(16,16);
	CString mkey = m_MachineId.Right(8); //ȡ�õ�����

	//��ȡʹ�ô���
	CString leftTime;
	BOOL isInfinite;
	GetDlgItem(IDC_SN2)->GetWindowText(leftTime);
	isInfinite = IsDlgButtonChecked(IDC_CHECK1);
	if (leftTime.GetLength() == 0 && !isInfinite)
	{
		MessageBox(_T("������ʹ�ô���"), NULL, NULL);
		return;
	}

	/****************DES ����***************************/
	CDesTest Dencryption1(mkey);		    //CDesTest Dencryption2(mkey);
	Dencryption1.initial();			        //Dencryption2.initial();	
	Dencryption1.jiqimaerjinzhi(desStr1);  // Dencryption2.jiqimaerjinzhi(desStr2);
	//DES���ܣ��ָ�ԭ��
	Dencryption1.DESJIEMI();		        //Dencryption2.DESJIEMI();
	//Dencryption1.YUANWEN += Dencryption2.YUANWEN;

	//GetDlgItem(IDC_MD5)->SetWindowText(Dencryption1.YUANWEN);

	//���������
	int randomNumber[8];
	//cout<<"����8��0~9���������"<<endl; 
	//һ������8λα�룬��ȡʹ�ô�����λ��������������ĸ���Ϊ8 - n��nΪʹ�ô�����λ��
	int n = leftTime.GetLength();

	for (int i = 0; i != (7 - n); ++i)
		randomNumber[i] = rand() % 10;

	int j = 0;
	CString zhuceNumber(Dencryption1.YUANWEN);
	
	//������޴�ʹ�ã���0λ����0���������λ��
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
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString m_MachineId;
//	GetDlgItem(IDC_CN)->GetWindowText(m_MachineId);
//	if (m_MachineId.GetLength()!= 24)
//	{
//		MessageBox(_T("������24λ�ַ�"),NULL,NULL);
//		return ;
//	}
//
//	CString desStr1 = m_MachineId.Left(16);
//	//CString desStr2 = m_MachineId.Mid(16,16);
//	CString mkey = m_MachineId.Right(8); //ȡ�õ�����
//	
//	/****************DES ����***************************/
//	CDesTest Dencryption1(mkey);		    //CDesTest Dencryption2(mkey);
//	Dencryption1.initial();			        //Dencryption2.initial();	
//	Dencryption1.jiqimaerjinzhi(desStr1);  // Dencryption2.jiqimaerjinzhi(desStr2);
//	//DES���ܣ��ָ�ԭ��
//	Dencryption1.DESJIEMI();		        //Dencryption2.DESJIEMI();
//	//Dencryption1.YUANWEN += Dencryption2.YUANWEN;
//
//	//GetDlgItem(IDC_MD5)->SetWindowText(Dencryption1.YUANWEN);
//
//	//���������
//	int randomNumber[8];
//	//cout<<"����8��0~9���������"<<endl; 
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bool isInfinite = IsDlgButtonChecked(IDC_CHECK1);
	GetDlgItem(IDC_SN2)->EnableWindow(!isInfinite);
}
