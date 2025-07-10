// DynamicEncryption.h: interface for the CDynamicEncryption class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNAMICENCRYPTION_H__77BEC380_60C4_48B7_811F_51460A59A7AD__INCLUDED_)
#define AFX_DYNAMICENCRYPTION_H__77BEC380_60C4_48B7_811F_51460A59A7AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDynamicEncryption  
{
public:
	CDynamicEncryption();
	virtual ~CDynamicEncryption();

//private:
//	static const int code1[10][10];
//	static const int code2[62];
//	static const int MappingChar[62];
//	static const int code1_row;
//	static const int code1_col;
//	static const int code2_len;
//	static const int MappingChar_len;


public:
	void EncryptFunc1(CString InputNum,CString &ciphertext1);
	void EncryptFunc2(CString ciphertext1,CString &ciphertext2);
	void DecodeFunc1(CString ciphertext1,CString &OutputNum);
	void DecodeFunc2(CString ciphertext2,CString &ciphertext1);

};



#endif // !defined(AFX_DYNAMICENCRYPTION_H__77BEC380_60C4_48B7_811F_51460A59A7AD__INCLUDED_)
