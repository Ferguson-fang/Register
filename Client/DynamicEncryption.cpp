// DynamicEncryption.cpp: implementation of the CDynamicEncryption class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DynamicEncryption.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static const int code1[10][10] = { 
	{13,1,5,24,11,16,0,17,25,22},
	{25,7,22,8,10,12,19,1,18,5},
	{19,25,3,16,2,4,14,0,24,20},
	{17,14,18,9,5,12,0,19,11,24},
	{8,23,13,3,11,18,10,7,17,12}, 
	{7,17,6,0,21,2,20,13,5,18},
	{22,21,24,7,15,0,1,12,19,6},
	{2,24,0,7,5,22,23,3,17,1},
	{3,6,24,8,5,23,22,13,0,15},
	{24,11,10,20,8,5,18,7,14,16} };
static const int code2[26] = {2,17,12,23,25,11,6,0,7,3,24,15,4,9,19,13,10,22,14,1,21,5,16,18,8,20};
static const int MappingChar[26] = {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90};
static const int code1_row = 10;
static const int code1_col = 10;
static const int code2_len = 26;
static const int MappingChar_len = 26;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDynamicEncryption::CDynamicEncryption()
{

}

CDynamicEncryption::~CDynamicEncryption()
{
	
}	

void CDynamicEncryption::EncryptFunc1(CString InputNum,CString &ciphertext1)
{
	srand((int)time(0));
	int iRow = rand()%9;

	ciphertext1 = InputNum;

	for(int i=0;i<ciphertext1.GetLength();i++)
		ciphertext1.SetAt(i, MappingChar[ code1[iRow][ciphertext1.GetAt(i)-48] ] );

	ciphertext1+=(char)(iRow+65);
}

void CDynamicEncryption::EncryptFunc2(CString ciphertext1,CString &ciphertext2)
{
	CString ciphertext2_temp;
	ciphertext2_temp = ciphertext1;
	int *iIndexTemp = new int[ciphertext2_temp.GetLength()];
	int i=0;
	int j=0;

	for(i=0;i<MappingChar_len;i++)
		for(j=0;j<ciphertext2_temp.GetLength();j++)
			if( ciphertext1.GetAt(j) == MappingChar[i] )
				iIndexTemp[j] = i;

	for(i=0;i<ciphertext1.GetLength();i++)
		ciphertext2_temp.SetAt(i,MappingChar[ code2[ iIndexTemp[i] ] ] );

	ciphertext2 = ciphertext2_temp;
	delete iIndexTemp;
}

void CDynamicEncryption::DecodeFunc1(CString ciphertext1,CString &OutputNum)
{
	CString Outputtemp;
	int ciphertext1_len = ciphertext1.GetLength();
	int *iIndexTemp = new int[ciphertext1_len];
	int iRow = ciphertext1.GetAt(ciphertext1_len-1) - 65;
	int i=0,j=0;
	
	ciphertext1.Delete(ciphertext1_len-1);
	ciphertext1_len--;
	
	for(i=0;i<MappingChar_len;i++)
	{
		for(j=0;j<ciphertext1_len;j++)
			if(ciphertext1.GetAt(j) == MappingChar[i])
				iIndexTemp[j] = i;
	}

	Outputtemp = ciphertext1;
	for(i=0;i<code1_col;i++)
		for(j=0;j<ciphertext1_len;j++)
			if( iIndexTemp[j] == code1[iRow][i] )
				Outputtemp.SetAt(j, i + 48);

	OutputNum = Outputtemp;
}

void  CDynamicEncryption::DecodeFunc2(CString ciphertext2,CString &ciphertext1)
{
	CString ciphertext1_temp;
	int ciphertext2_len = ciphertext2.GetLength();
	int i=0,j=0;
	int *iIndexTemp = new int[ciphertext2_len];

	ciphertext1_temp = ciphertext2;

	for(i=0;i<code2_len;i++)
	{
		for(j=0;j<ciphertext2_len;j++)
			if( ciphertext2.GetAt(j) == MappingChar[ code2[i] ] )
			{
				iIndexTemp[j] = i;
			}
	}
	
	for(i=0;i<ciphertext2_len;i++)
		ciphertext1_temp.SetAt( i, MappingChar[iIndexTemp[i]] );

	ciphertext1 = ciphertext1_temp;
	delete iIndexTemp;
}