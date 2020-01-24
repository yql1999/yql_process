//创建(CreateProcess)并销毁(TerminateProcess)一个写字板的进程
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <cstdio>
#include "Tlhelp32.h"
using namespace std;

TCHAR proPath[] = TEXT("NOTEPAD");
PROCESS_INFORMATION pi;

//创建线程
void open()
{
	cout<<"Process create successfully!"<<endl;
	STARTUPINFO si = { sizeof(si) };
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;
	BOOL bRet = CreateProcess(NULL, proPath, NULL,NULL,FALSE, CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi);
	// 显示进程位置
	cout << "Process ID: " << GetCurrentProcessId() << endl;
	return;
}

//终止当前线程
void close()
{
	BOOL bEndOK = TerminateProcess(pi.hProcess,0) ;
	if(bEndOK)
		cout<<"Process exit successfully!"<<endl;
	//（存放进程信息和调用成员输出进程信息）用来 Process32First指向第一个进程信息，并将进程信息抽取到PROCESSENTRY32中
	PROCESSENTRY32 pe;
	HANDLE hProcess;
	pe.dwSize = sizeof (PROCESSENTRY32);
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	Process32First(hSnapshot,& pe);
	do
	{
		/*
		if ( ! _tcsicmp(pe.szExeFile,_T("wordpad.exe")))
		{
			break;
		}
		*/
		pe.dwSize = sizeof(PROCESSENTRY32);
	} while(Process32Next(hSnapshot, & pe));
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;
	//根据进程ID返回对象句柄
	hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,pe.th32ProcessID); 
	//根据对象句柄结束进程
	TerminateProcess(hProcess,0); 
	CloseHandle(hSnapshot);
	CloseHandle(hProcess);
	return;
}


int main()
{
	char ch;
	while(TRUE)
	{
		cout<<"------Please choose your option------\n1.创建进程..\n2.关闭进程..\n3.退出程序..\n";
		cin>>ch;
		switch (ch)
		{
		case '1':
			open();
			break;
		case '2':
			close();
			break;
		case '3':
			exit(0);
			break;
		default:
			cout<<"Error：wrong input！"<<endl;
		}
	}
	return 0;
}