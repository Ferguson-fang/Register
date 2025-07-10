
// ClientDlg.h : ͷ�ļ�
//

#pragma once


// CClientDlg �Ի���
class CClientDlg : public CDialogEx
{
// ����
public:
	CClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnRegis();
	afx_msg void OnBnClickedCancel();

private:
	void dofile(char *in_fname, char *pwd, char *out_file);
	char MakecodeChar(char c, int key);
	char CutcodeChar(char c, int key);
	void Cutecode(char *pstr, int *pkey);
	void Makecode(char *pstr, int *pkey);
};
