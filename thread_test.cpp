//�̵߳Ĵ����͹ر�
#include"stdafx.h"
#include <iostream.h>
#include <wtypes.h>
HANDLE hThread1 = NULL; //�߳̾������Ϊȫ�ֱ���
DWORD ThreadID = NULL; //�߳�ID����Ϊȫ�ֱ���

void open()
{
	cout << "\nopen doning!"<<endl;
}

DWORD thread1()
{
	if (hThread1)
	{
		cout << "\n�߳�[ "<<ThreadID<<" ]�Ѿ�����!"<<endl;
	}
	else
	{
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)open, NULL, 0, &ThreadID);
		if (!hThread1)
		{
			cout<<"\n�̴߳���ʧ��!"<<endl;
		}
		else
		{
			cout << "\n�߳�[ "<<ThreadID<<" ]�Ѵ���!"<<endl;
		}
		int iR = SetThreadPriority(hThread1, THREAD_PRIORITY_NORMAL);
	}
	return ThreadID;
}

void close( HANDLE handle)
{
	if (handle) //����߳̾����Ϊ��
	{
		WaitForSingleObject((HANDLE)handle, INFINITE) ; //�ȴ��߳�handle�������
		CloseHandle((HANDLE)handle) ; //�ر��߳�
		cout << "\n�߳�[ "<<ThreadID<<" ]�ѹر�!"<<endl;
	}
	else
	{
		cout << "\n�̲߳�����!"<<endl;
	}
}


//������
void main()
{
	char ch;
	while(1)
	{
		cout<<"------Please choose your option:------\n1.�����߳�..\n2.�ر��߳�..\n3.�˳�����..\n";
		cin>>ch;
		switch (ch)
		{
		case '1':
			thread1();
			break;
		case '2':
			close(hThread1);
			hThread1 = NULL;
			ThreadID = NULL;
			break;
		case '3':
			exit(0);
			break;
		default:
			cout<<"\nwrong option"<<endl;
		}
	}
	return;
}
