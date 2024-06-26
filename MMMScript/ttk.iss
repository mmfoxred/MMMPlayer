; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "�������"
#define MyAppVersion "2.4.0.0"
#define MyAppURL "http://download.csdn.net/album/detail/3094"
#define MyAppExeName "MMMMusicPlayer.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{B246DC4A-B67B-4D3D-901E-8CA1D829BF55}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DisableProgramGroupPage=yes
OutputDir=D:\Qt
OutputBaseFilename=v{#MyAppVersion}
SetupIconFile=D:\Qt\Workspace\MMMMusicplayer\MMMResource\lb_player_logo.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: checkedonce

[Files]
Source: "D:\Qt\MMMMusicPlayer\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\Qt\MMMMusicPlayer\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{sys}\cmd.exe"; Parameters:" /c takeown /f ""{app}"" /r /d y & icacls ""{app}"" /grant administrators:F /t"; Flags: runhidden waituntilterminated  shellexec  runascurrentuser
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

[PostCompile]
Name: "make_cert.bat";Parameters:"D:\Qt\v2.4.0.0.exe" ;Flags: cmdprompt redirectoutput
