//����(CreateProcess)������(TerminateProcess)һ��д�ְ�Ľ���
#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <cstdio>
#include "Tlhelp32.h"
using namespace std;

TCHAR proPath[] = TEXT("NOTEPAD");
PROCESS_INFORMATION pi;

//�����߳�
void open()
{
	cout<<"Process create successfully!"<<endl;
	STARTUPINFO si = { sizeof(si) };
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;
	BOOL bRet = CreateProcess(NULL, proPath, NULL,NULL,FALSE, CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi);
	// ��ʾ����λ��
	cout << "Process ID: " << GetCurrentProcessId() << endl;
	return;
}

//��ֹ��ǰ�߳�
void close()
{
	BOOL bEndOK = TerminateProcess(pi.hProcess,0) ;
	if(bEndOK)
		cout<<"Process exit successfully!"<<endl;
	//����Ž�����Ϣ�͵��ó�Ա���������Ϣ������ Process32Firstָ���һ��������Ϣ������������Ϣ��ȡ��PROCESSENTRY32��
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
	//���ݽ���ID���ض�����
	hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,pe.th32ProcessID); 
	//���ݶ�������������
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
		cout<<"------Please choose your option------\n1.��������..\n2.�رս���..\n3.�˳�����..\n";
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
			cout<<"Error��wrong input��"<<endl;
		}
	}
	return 0;
}