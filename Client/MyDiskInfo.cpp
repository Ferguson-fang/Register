// MyDiskInfo.cpp: implementation of the CMyDiskInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Client.h"
#include "MyDiskInfo.h"

#include <iostream>
#include <Windows.h>
#include <Wbemidl.h>
#include <comdef.h>

#pragma comment(lib, "wbemuuid.lib")


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const WORD IDE_ATAPI_IDENTIFY = 0xA1;   // 读取ATAPI设备的命令
const WORD IDE_ATA_IDENTIFY   = 0xEC;   // 读取ATA设备的命令

#define _WIN32_WINNT 0x0400
#include "winioctl.h"

#include <winsock2.h> 
#include <iphlpapi.h> 
#pragma comment(lib,"Iphlpapi.lib") 


//#include "NTDDSCSI.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyDiskInfo::CMyDiskInfo()
{

}

CMyDiskInfo::~CMyDiskInfo()
{

}

BOOL __fastcall DoIdentify( HANDLE hPhysicalDriveIOCTL, 
							PSENDCMDINPARAMS pSCIP,
							PSENDCMDOUTPARAMS pSCOP, 
							BYTE btIDCmd, 
							BYTE btDriveNum,
							PDWORD pdwBytesReturned)
{
    pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
    pSCIP->irDriveRegs.bFeaturesReg = 0;
    pSCIP->irDriveRegs.bSectorCountReg  = 1;
    pSCIP->irDriveRegs.bSectorNumberReg = 1;
    pSCIP->irDriveRegs.bCylLowReg  = 0;
    pSCIP->irDriveRegs.bCylHighReg = 0;

    pSCIP->irDriveRegs.bDriveHeadReg = (btDriveNum & 1) ? 0xB0 : 0xA0;
    pSCIP->irDriveRegs.bCommandReg = btIDCmd;
    pSCIP->bDriveNumber = btDriveNum;
    pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;

    return DeviceIoControl(	hPhysicalDriveIOCTL, 
							SMART_RCV_DRIVE_DATA,
							(LPVOID)pSCIP,
							sizeof(SENDCMDINPARAMS) - 1,
							(LPVOID)pSCOP,
							sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
							pdwBytesReturned, NULL);
}

char *__fastcall ConvertToString(DWORD dwDiskData[256], int nFirstIndex, int nLastIndex)
{
	static char szResBuf[1024];
	char ss[256];
	int nIndex = 0;
	int nPosition = 0;

	for(nIndex = nFirstIndex; nIndex <= nLastIndex; nIndex++)
	{
		ss[nPosition] = (char)(dwDiskData[nIndex] / 256);
		nPosition++;

		// Get low BYTE for 2nd character
		ss[nPosition] = (char)(dwDiskData[nIndex] % 256);
		nPosition++;
	}

	// End the string
	ss[nPosition] = '\0';

	int i, index=0;
	for(i=0; i<nPosition; i++)
	{
		if(ss[i]==0 || ss[i]==32)	continue;
		szResBuf[index]=ss[i];
		index++;
	}
	szResBuf[index]=0;

	return szResBuf;
}
CString CMyDiskInfo::GetCPUID()
{
	CString CPUID;
	unsigned long s1,s2;
	unsigned char vendor_id[]="------------";
	char sel;
	sel='1';
	CString VernderID;
	CString MyCpuID,CPUID1,CPUID2;
	switch(sel)
	{
	case '1':
		__asm{
			    xor eax,eax      //eax=0:取Vendor信息
				cpuid    //取cpu id指令，可在Ring3级使用
				mov dword ptr vendor_id,ebx
				mov dword ptr vendor_id[+4],edx
				mov dword ptr vendor_id[+8],ecx
				//mov  BYTE   PTR   OEMString+12,0 
		}
		VernderID.Format(_T("%s-"),vendor_id);
		__asm{
			    mov eax,01h   //eax=1:取CPU序列号
				xor edx,edx
				cpuid
				mov s1,edx
				mov s2,eax
		}
		CPUID1.Format(_T("%08X%08X"),s1,s2);
		__asm{
			mov eax,03h
				xor ecx,ecx
				xor edx,edx
				cpuid
				mov s1,edx
				mov s2,ecx
		}
		CPUID2.Format(_T("%08X%08X"),s1,s2);
		break;
	case '2':
		{
			__asm{
				mov ecx,119h
					rdmsr
					or eax,00200000h
					wrmsr
			}
		}
		AfxMessageBox(_T("CPU id is disabled."));
		break;
	}
	MyCpuID = CPUID1+CPUID2;
	CPUID = MyCpuID;
	return CPUID;
}
int CMyDiskInfo::GetDiskInfo(int driver)
{
	CString sFilePath;
	sFilePath.Format(_T("\\\\.\\PHYSICALDRIVE%d"), driver);

	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = ::CreateFile(sFilePath, 
						GENERIC_READ | GENERIC_WRITE, 
						FILE_SHARE_READ | FILE_SHARE_WRITE, 
						NULL, OPEN_EXISTING,
						0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)	return -1;

	DWORD dwBytesReturned;
	GETVERSIONINPARAMS gvopVersionParams;
	DeviceIoControl(hFile, 
					SMART_GET_VERSION,
					NULL, 
					0, 
					&gvopVersionParams,
					sizeof(gvopVersionParams),
					&dwBytesReturned, NULL);

	if(gvopVersionParams.bIDEDeviceMap <= 0)	return -2;

	// IDE or ATAPI IDENTIFY cmd
	int btIDCmd = 0;
	SENDCMDINPARAMS InParams;
	int nDrive =0;
	btIDCmd = (gvopVersionParams.bIDEDeviceMap >> nDrive & 0x10) ? IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;


	// 输出参数
	BYTE btIDOutCmd[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
	DWORD dwError;
	if (DoIdentify(hFile,
		&InParams,
		(PSENDCMDOUTPARAMS)btIDOutCmd,
		(BYTE)btIDCmd,
		(BYTE)nDrive, &dwBytesReturned) == FALSE)
	{
		dwError = GetLastError();  // 获取错误代码
	}
	DWORD out = dwError;
	if(DoIdentify(hFile,
					&InParams, 
					(PSENDCMDOUTPARAMS)btIDOutCmd,
					(BYTE)btIDCmd, 
					(BYTE)nDrive, &dwBytesReturned) == FALSE)	return -3;
	::CloseHandle(hFile);

	DWORD dwDiskData[256];
	USHORT *pIDSector; // 对应结构IDSECTOR，见头文件

	pIDSector = (USHORT*)((SENDCMDOUTPARAMS*)btIDOutCmd)->bBuffer;
	for(int i=0; i < 256; i++)	dwDiskData[i] = pIDSector[i];

	// 取系列号
	ZeroMemory(szSerialNumber, sizeof(szSerialNumber));
	strcpy(szSerialNumber, ConvertToString(dwDiskData, 10, 19));

	// 取模型号
	ZeroMemory(szModelNumber, sizeof(szModelNumber));
	strcpy(szModelNumber, ConvertToString(dwDiskData, 27, 46));

	return 0;
}



int CMyDiskInfo::GetDiskSerialNumber(){
	// 初始化 COM 库
	HRESULT hres = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hres)) {
		std::cerr << "COM library initialization failed" << std::endl;
		return -1;
	}

	// 设置安全性
	hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (FAILED(hres)) {
		std::cerr << "Failed to initialize security" << std::endl;
		CoUninitialize();
		return -2;
	}
	// 获取 WMI 服务对象
	IWbemLocator* pLoc = NULL;
	hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	if (FAILED(hres)) {
		std::cerr << "Failed to create IWbemLocator object" << std::endl;
		CoUninitialize();
		return -3;
	}

	IWbemServices* pSvc = NULL;
	hres = pLoc->ConnectServer(
		_bstr_t(L"ROOT\\CIMV2"), // WMI namespace
		NULL, NULL, 0, NULL, 0, 0, &pSvc
	);
	if (FAILED(hres)) {
		std::cerr << "Could not connect to WMI" << std::endl;
		pLoc->Release();
		CoUninitialize();
		return -4;
	}

	// 设置 WMI 安全
	hres = CoSetProxyBlanket(
		pSvc,                       // WMI 服务
		RPC_C_AUTHN_DEFAULT,         // 身份验证
		RPC_C_AUTHZ_DEFAULT,         // 授权
		NULL,                        // 服务器名称
		RPC_C_AUTHN_LEVEL_DEFAULT,   // 身份验证级别
		RPC_C_IMP_LEVEL_IMPERSONATE, // 模拟级别
		NULL,                        // 认证信息
		EOAC_NONE                    // 额外选项
	);
	if (FAILED(hres)) {
		std::cerr << "Could not set proxy blanket" << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return -5;
	}

	// 查询硬盘序列号
	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(
		bstr_t("WQL"),
		bstr_t("SELECT * FROM Win32_PhysicalMedia"),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator
	);
	if (FAILED(hres)) {
		std::cerr << "WMI query failed" << std::endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return -6;
	}

	IWbemClassObject* pclsObj = NULL;
	ULONG uReturn = 0;

	// 获取硬盘序列号
	while (pEnumerator) {
		hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn) break;

		VARIANT vtProp;
		hres = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
		if (SUCCEEDED(hres)) {
			serialNumber = _bstr_t(vtProp.bstrVal);
			VariantClear(&vtProp);
			break;
		}

		pclsObj->Release();
	}
	// 清理
	pSvc->Release();
	pLoc->Release();
	CoUninitialize();

	return serialNumber.empty();
}



CString CMyDiskInfo::GetMAC()
{
	// 初始化winsock
	PIP_ADAPTER_INFO pAdapterInfo; 
	PIP_ADAPTER_INFO pAdapter = NULL; 
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO); 
	pAdapterInfo = (PIP_ADAPTER_INFO)malloc(ulOutBufLen); 
	DWORD dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen);  // 第一次调用GetAdapterInfo获取ulOutBufLen大小 
	CString MACstr;
	MACstr.Empty();

	if (dwRetVal == ERROR_BUFFER_OVERFLOW) 
	{ 
		free(pAdapterInfo); 
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen); 
		dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen);
	} 
	if (dwRetVal == NO_ERROR)
	{ 
		pAdapter = pAdapterInfo; 
		if (pAdapter) 
		{ 
			for (int i =0;i <6;i++)			//一个字节是两个十六进制数
			{
				CString str;
				str.Format("%02x",pAdapter->Address[i]);
				MACstr += str;
			}	
			return MACstr;
		}
	} 
	else return MACstr; 

}