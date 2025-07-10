// MyDiskInfo.h: interface for the CMyDiskInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYDISKINFO_H__FF310990_FA82_421A_94CD_1F696F3AB948__INCLUDED_)
#define AFX_MYDISKINFO_H__FF310990_FA82_421A_94CD_1F696F3AB948__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <string>
class CMyDiskInfo  
{
public:
	int GetDiskInfo(int driver=0);
	int GetDiskSerialNumber();
	char szModelNumber[64];
	char szSerialNumber[64];
	std::string serialNumber;
	CMyDiskInfo();
	virtual ~CMyDiskInfo();
	CString GetCPUID();
	CString GetMAC();
};

#endif // !defined(AFX_MYDISKINFO_H__FF310990_FA82_421A_94CD_1F696F3AB948__INCLUDED_)
