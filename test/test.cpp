#include <winsock2.h> 
#include <iphlpapi.h> 
#include <stdio.h> 
#pragma comment(lib,"Iphlpapi.lib") 
int main() 
{ 
	// 初始化winsock
	PIP_ADAPTER_INFO pAdapterInfo; 
	PIP_ADAPTER_INFO pAdapter = NULL; 
	ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO); 
	pAdapterInfo = (PIP_ADAPTER_INFO)malloc(ulOutBufLen); 
	DWORD dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen);
	// 第一次调用GetAdapterInfo获取ulOutBufLen大小 
	if (dwRetVal == ERROR_BUFFER_OVERFLOW) 
	{ 
		free(pAdapterInfo); 
		pAdapterInfo = (IP_ADAPTER_INFO *) malloc (ulOutBufLen); 
		dwRetVal = GetAdaptersInfo( pAdapterInfo, &ulOutBufLen);
	} 
	if (dwRetVal == NO_ERROR)
	{ 
		pAdapter = pAdapterInfo; 
		while (pAdapter) 
		{ 
			printf("Adapter Name: \t%s\n", pAdapter->AdapterName); 
			printf("Adapter Desc: \t%s\n", pAdapter->Description); 
			printf("MAC Addr: \t%02x-%02x-%02x-%02x-%02x-%02x\n", 
				pAdapter->Address[0], 
				pAdapter->Address[1], 
				pAdapter->Address[2], 
				pAdapter->Address[3], 
				pAdapter->Address[4], 
				pAdapter->Address[5]); 
			printf("IP Address: \t%s\n", pAdapter->IpAddressList.IpAddress.String); 
			printf("IP Mask: \t%s\n", pAdapter->IpAddressList.IpMask.String); 
			printf("Gateway: \t%s\n", pAdapter->GatewayList.IpAddress.String); 
			pAdapter = pAdapter->Next; 
		}// end while 
	} 
	else 
	{ 
		printf("Call to GetAdaptersInfo failed.\n"); 
	} 
	//卸载winsock ...
		return 0;
} //end main
