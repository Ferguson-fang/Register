#pragma once
class CDesTest
{
public:
	int t1[65];//tl里面存储着密文的二进制数
	int K1[49],K2[49],K3[49],K4[49],K5[49],K6[49],K7[49],K8[49],K9[49],K10[49],K11[49],K12[49],K13[49],K14[49],K15[49],K16[49];
	int R0[33];
	int L0[33];
	CString MINGWEN,MIYAO,MEWEN,YUANWEN;
	CDesTest(CString m_key);
	~CDesTest(void);
	void jiqimaerjinzhi(CString m_str);
	void Mingwenerjinzhi();
	void MIYAOERJINZHI();
	void initial();
	void DESDIEDAI();
	void DESJIEMI();
	int miyao[64];
	int mingwen[64];
};

