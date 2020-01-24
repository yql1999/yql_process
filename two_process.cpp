#include <iostream>   
#include <windows.h>   
using namespace std;
 
DWORD WINAPI Fun(LPVOID lpParamter){
    cout << " sub process b " ;
    return 0L;
}

DWORD WINAPI Fun_2(LPVOID lpParamter){
    cout << " sub process c " ;
    return 0L;
}
 
int main(){
	cout<<"Test the execution sequence of main process a, sub process b and sub process c:"<<endl; 
    HANDLE hThread = CreateThread(NULL, 0, Fun, NULL, 0, NULL);
    HANDLE hThread_2 = CreateThread(NULL, 0, Fun_2, NULL, 0, NULL);
    CloseHandle(hThread);
    CloseHandle(hThread_2);
	cout<<" main process a " ;
	Sleep(500); 
    return 0;
}
