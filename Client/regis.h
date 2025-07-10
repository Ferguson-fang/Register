#ifndef REGIS_H
#define REGIS_H
#include "stdafx.h"
#include<iostream>
#include <string>
using namespace std;
//CString getSerialNO(int number);
std::pair<CString, string> getSerialNO(int&type);
bool isRegisSuccess(CString registernum, CString md5Str1);
#endif