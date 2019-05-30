//AUTHOR : #Captain_Nemo

#ifndef MINGW_DLL_H__
#define MINGW_DLL_H__
#define CONNIP "192.168.225.197"
#define CONNPORT 8080
#pragma comment(lib, "Ws2_32.lib")
#define DEF_BUFF 2048

struct STRUCT_DLL {
     SOCKET Winsock;
};

//void reverse(char* server, int Port);

#endif
