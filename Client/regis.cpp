#include "stdafx.h"
#include "regis.h"
#include "MyDiskInfo.h"
#include "MD5.h"
#include "DynamicEncryption.h"
#include "DesTest.h"
#include "resource.h"
#include <fstream>

using namespace std;

pair<CString, string> getSerialNO(int&type)
{
	type = -1;

	CString sz_str;
	CMyDiskInfo DiskInfo;
	CString disk_info, cpu_info, mac_info;
	//获取cpu ID
	cpu_info = DiskInfo.GetCPUID();
	////GetDlgItem(IDC_EDIT_CPU)->SetWindowText(cpu_info);
	//获取网卡的MAC
	mac_info = DiskInfo.GetMAC();
	////GetDlgItem(IDC_EDIT_MAC)->SetWindowText(mac_info);
	//获取硬盘ID
	/*int b = DiskInfo.GetDiskInfo();
	if (b == 0)
	{
		disk_info = DiskInfo.szSerialNumber;
	}
	else
		disk_info = "";*/
	//m_edit->SetWindowTextA(DiskInfo.szModelNumber);	
	////GetDlgItem(IDC_EDIT_HD)->SetWindowText(disk_info);

	//wmic方式获取磁盘ID
	int w = DiskInfo.GetDiskSerialNumber();
	if (w == 0)
	{
		disk_info = DiskInfo.serialNumber.data();
	}
	else
		disk_info = "";


	string tx = "";
	fstream rfile;
	rfile.open("yx.dat", ios::in);
	rfile >> type >> tx;
	rfile.close();
	if (type != 0 && type != 1 && type != 2)
	{
		type = -1;
		tx = "";
	}
	
	CString info;
	if (type == -1 || tx == "")
	{
		type = 0;
		info = cpu_info;     //用于加密的信息
		if (info.IsEmpty())
		{
			info = mac_info;
			type = 1;
			if (info.IsEmpty())
			{
				info = disk_info;
				type = 2;
				if (info.IsEmpty())
				{
					type = -1;
					pair<CString, string> re(L"信息不匹配", "");
					return re;
				}
			}
		}
	}
	else if (type == 0)
	{
		info = cpu_info;
		if (info.IsEmpty())
		{
			type = -1;
			pair<CString, string> re(L"信息不匹配", "");
			return re;
		}
	}
	else if (type == 1)
	{
		info = mac_info;
		if (info.IsEmpty())
		{
			type = -1;
			pair<CString, string> re(L"信息不匹配", "");
			return re;
		}
	}
	else if (type == 2)
	{
		info = disk_info;
		if (info.IsEmpty())
		{
			type = -1;
			pair<CString, string> re(L"信息不匹配", "");
			return re;
		}
	}
	else
	{
		type = -1;
		pair<CString, string> re(L"信息不匹配", "");
		return re;
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

	if (info.IsEmpty()||tx=="")
	{
		type = -1;
		pair<CString, string> re(L"信息不匹配", "");
		return re;
	}

	info = info + (CString)tx.c_str();

	/************************MD5加密*********************************/
	USES_CONVERSION;
	char *encrypt = (LPSTR)(LPCTSTR)info;//Cstring转char*
	sz_str = md5(encrypt).c_str();

	pair<CString, string> re(sz_str, tx);
	return re;
}

bool isRegisSuccess(CString registernum, CString md5Str1)
{
	CString sz_str = md5Str1;

	if (registernum.GetLength() < 16)
	{
		return false;
	}

	CString desStr1 = registernum.Left(16);//用于比对是否注册成功

	/*********************将原文逆（小）变换************************/
	int len = desStr1.GetLength();
	int i = len - 2;
	for (; i >= 0; i -= 2)
	{
		desStr1.Delete(i);
	}

	if (desStr1.Left(8) == sz_str.Mid(2, 8))
	{
		return true;
	}
	return false;
}