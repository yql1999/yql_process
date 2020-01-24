// Linux�µĵ���fork()��������

#include "stdafx.h"
#include<unisted.h>
#include<stdio.h>

int main()
{
	pid_t pid; 
    pid = fork();   //��fork���óɹ����ӽ��̿�ʼ��fork��ʼִ��
	
    //��������ʧ��
    if(-1 == pid){
        perror("fork failed");
        return -1;
		
		//������
    }else if(pid > 0){
		//pid���ڽ��յ�ǰ����id�� ppid���ڽ��ո�����id
		printf("parent : pid = %d , ppid = %d\n", getpid(), getppid());
		sleep(1);
		
		//�ӽ���
    }else if(pid == 0){
		printf("child: pid = %d, ppid = %d\n", getpid(), getppid());
		sleep(1);
    }
	return 0;
}
