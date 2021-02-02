SET PATH=F:\KEIL5.31\ARM\ARMCC\Bin;F:\PADS9.5\9.5PADS\MGC_HOME.ixn\bin;F:\PADS9.5\9.5PADS\MGC_HOME.ixn\lib;C:\Program Files (x86)\STMicroelectronics\st_toolset\asm;C:\Program Files (x86)\Common Files\Oracle\Java\javapath;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Windows\System32\OpenSSH\;F:\MATLAB\runtime\win64;F:\MATLAB\bin;G:\chromedownload\mingw64\bin;F:\Lua\5.1\clibs;F:\Lua\5.1;C:\Program Files\Microsoft\Web Platform Installer\;C:\Program Files (x86)\Microsoft ASP.NET\ASP.NET Web Pages\v1.0\;C:\Program Files\Microsoft SQL Server\110\Tools\Binn\;C:\Program Files\Java\jdk1.8.0_211\bin;F:\python3.7\Scripts\;F:\python3.7\;C:\Users\dele\AppData\Local\Microsoft\WindowsApps;C:\Program Files\Bandizip\;G:\xtensa-lx106-elf\bin;G:\wkhtmltox\bin;F:\Nodejs\;E:\vim\Windows\gVimPortable_7.4\vim74;F:\Anaconda;F:\Anaconda\Scripts;C:\ProgramData\chocolatey\bin;C:\MinGW\bin;F:\gcc-arm-none-eabi-9-2020-q2-update-win32\bin;F:\cmake-3.17.3-win64-x64\bin;F:\VScode\Microsoft VS Code\bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files (x86)\Windows Kits\8.0\Windows Performance Toolkit\;F:\Git\Git\cmd;F:\ffmpeg-4.1-win64-static\bin;F:\Qt5.14\5.14.2\mingw73_64\bin;C:\MinGW\bin;C:\Program Files (x86)\dotnet\;F:\python3.6\Scripts\;F:\python3.6\;F:\python3.7\Scripts\;F:\python3.7\;C:\Users\dele\AppData\Local\Microsoft\WindowsApps;C:\Program Files\Bandizip\;F:\Pycharm\PyCharm Community Edition 2019.3.3\bin;C:\Users\dele\AppData\Roaming\npm;F:\MikTex\miktex\bin\x64\;F:\ffmpeg-4.1-win64-static\bin;F:\dvisvgm;F:\Pycharm Pro 2019\PyCharm 2019.2.6\bin;F:\Bandzip\;C:\Users\dele\AppData\Local\Microsoft\WindowsApps;C:\MinGW\bin;F:\CLion 2019.3.4\bin;;F:\Quartus13.1\modelsim_ase\win32aloem;F:\Pycharm\PyCharm2020.1\bin;
SET CPU_TYPE=STM32F407VE
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=STM32F407Libaray
SET CPU_CLOCK=0x017D7840
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\main.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f4xx_it.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\system_stm32f4xx.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\led.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\delay.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\sys.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\usart.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmAsm" --Via "..\obj\startup_stm32f40_41xxx._ia"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\misc.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f4xx_gpio.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f4xx_rcc.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f4xx_syscfg.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f4xx_usart.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\stm32f4xx_spi.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\lcd.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\lcdtest.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\gui.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmCC" --Via "..\obj\softspi.__i"
"F:\KEIL5.31\ARM\ARMCC\Bin\ArmLink" --Via "..\OBJ\LED.lnp"
"F:\KEIL5.31\ARM\ARMCC\Bin\fromelf.exe" "..\OBJ\LED.axf" --i32combined --output "..\OBJ\LED.hex"
