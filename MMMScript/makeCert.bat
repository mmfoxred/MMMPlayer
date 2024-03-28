@echo off
if "%1" == "" echo "plz input a file path" && exit
if not exist %1 echo "%1 not exist" && exit

set base=C:\Program Files (x86)\Microsoft SDKs\Windows\v7.1A\bin
"%base%\cert2spc.exe" %temp%\CbipSetupKey.cer %temp%\CbipSetupKey.spc
"%base%\pvk2pfx.exe" -pvk %temp%\CbipSetupKey.pvk -spc %temp%\CbipSetupKey.spc -f -pfx %userprofile%\Desktop\MMMMusicplayer.pfx
"%base%\signtool.exe" sign /f %userprofile%\Desktop\MMMMusicplayer.pfx  /t "http://timestamp.verisign.com/scripts/timstamp.dll" /d "MMMMusicplayer" %1
del %temp%\CbipSetupKey.* >nul 2>nul
del %userprofile%\Desktop\MMMMusicplayer.pfx >nul 2>nul
