//线程的创建和关闭
#include"stdafx.h"
#include <iostream.h>
#include <wtypes.h>
HANDLE hThread1 = NULL; //线程句柄定义为全局变量
DWORD ThreadID = NULL; //线程ID定义为全局变量

void open()
{
	cout << "\nopen doning!"<<endl;
}

DWORD thread1()
{
	if (hThread1)
	{
		cout << "\n线程[ "<<ThreadID<<" ]已经存在!"<<endl;
	}
	else
	{
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)open, NULL, 0, &ThreadID);
		if (!hThread1)
		{
			cout<<"\n线程创建失败!"<<endl;
		}
		else
		{
			cout << "\n线程[ "<<ThreadID<<" ]已创建!"<<endl;
		}
		int iR = SetThreadPriority(hThread1, THREAD_PRIORITY_NORMAL);
	}
	return ThreadID;
}

void close( HANDLE handle)
{
	if (handle) //如果线程句柄不为空
	{
		WaitForSingleObject((HANDLE)handle, INFINITE) ; //等待线程handle处理完毕
		CloseHandle((HANDLE)handle) ; //关闭线程
		cout << "\n线程[ "<<ThreadID<<" ]已关闭!"<<endl;
	}
	else
	{
		cout << "\n线程不存在!"<<endl;
	}
}


//主函数
void main()
{
	char ch;
	while(1)
	{
		cout<<"------Please choose your option:------\n1.创建线程..\n2.关闭线程..\n3.退出程序..\n";
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
