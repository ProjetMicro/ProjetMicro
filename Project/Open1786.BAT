SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\Program Files\Intel\iCLS Client\;C:\ProgramData\Oracle\Java\javapath;C:\windows\system32;C:\windows;C:\windows\System32\Wbem;C:\windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\MiKTeX 2.9\miktex\bin\;C:\Program Files\TortoiseGit\bin;C:\Program Files\TortoiseSVN\bin;C:\Program Files\PuTTY\;C:\Program Files\QuickTime\QTSystem\;C:\Cadence\SPB_16.6\tools\pcb\bin;C:\Cadence\SPB_16.6\tools\bin;C:\Cadence\SPB_16.6\tools\libutil\bin;C:\Cadence\SPB_16.6\tools\fet\bin;C:\Cadence\SPB_16.6\tools\specctra\bin;C:\Cadence\SPB_16.6\tools\pspice;C:\Cadence\SPB_16.6\tools\capture;C:\Cadence\SPB_16.6\openaccess\bin\win32\opt;C:\Program Files\Microsoft Windows Performance Toolkit\;C:\Program Files\Optiwave Software\OptiSystem 6\bin\win32;C:\Program Files\MATLAB\R2012b\bin;C:\Program Files\BaseX\bin;C:\Program Files\IVI Foundation\VISA\WinNT\Bin\;C:\Program Files\IVI Foundation\VISA\WinNT\Bin;C:\Program Files\National Instruments\Motion Assistant\bin\mxwplugins;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\IPT
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=Open1786
SET CPU_CLOCK=0x00B71B00
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\output\startup_lpc17xx._ia"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\system_lpc17xx.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\core_cm3.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\lpc17xx_clkpwr.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\lpc17xx_gpio.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\lpc17xx_pinsel.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\lpc17xx_timer.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\lpc17xx_exti.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\lpc17xx_nvic.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\lpc17xx_ssp.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\lpc17xx_i2c.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\main.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\ili_lcd_general.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\lcd_api.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\english_16x8.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\affichagelcd.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\touch_panel.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\buzzer.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\lcd.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\output\memory.__i"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\Output\Project.lnp"
C:\Keil\ARM\ARMCC\bin\fromelf.exe ".\Output\Project.axf" --i32combined --output ".\Output\Project.hex"
