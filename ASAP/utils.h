#pragma once
// Standard header files.
#include <strsafe.h>






/*
// Need to re-define the names of the constants. All messages sent directly to the window procedure should be different from the one's sent to WM_COMMAND.

*/








// User defined header files.
#include "Console.h"
#include "TextBox.h"

// 0 means no debug mode.
#define DEBUGMODEON 0

// 0 means no thread is launched hence no watching directory.
#define MONITORMODE 0

#define FILEFOUND                   (WM_APP + 0x0001) // Sent when a file is found by directory monitor.
#define PRINTFILE                   (WM_APP + 0x0002) // Sent after the file is found and opened.

// SYSTEM TRAY ICON MENU COMMANDS.
#define SWM_SHOW                    (WM_APP + 0x0003) // Show application option
#define SWM_HIDE                    (WM_APP + 0x0004) // Hide application option
#define SWM_PAUSE                   (WM_APP + 0x0005) // Pause application option
#define SWM_RESUME                  (WM_APP + 0x0006) // Resume application option
#define SWM_RESTART                 (WM_APP + 0x0007) // Restart application option
#define SWM_EXIT                    (WM_APP + 0x0008) // Exit application option
#define SWM_SETTING                 (WM_APP + 0x0009) // Open setting option

#define CLOSESETTING                (WM_APP + 0x000A) // Sent when setting window is closed.

// Unique identifiers of the setting window's content, used to assign fonts and paint them.
#define IDC_SETTINGLABLE            (WM_APP + 0x000B) // Identifier for lables in the setting page. 
#define IDC_SETTINGEDITBOX          (WM_APP + 0x000C) // Identifier for edits in the setting page.

// Setting Window Button Commands. Identifier for buttons in the setting page.
#define SWM_CHANGEIN                 (WM_APP + 0x000E) // To change IN path.
#define SWM_CHANGEOUT                (WM_APP + 0x000F) // To change OUT path.
#define SWM_CHANGEERR                (WM_APP + 0x0010) // To change ERROR path.
#define SWM_CHANGEPRI                (WM_APP + 0x0011) // To change PRINTER.
#define SWM_CHANGEWT                 (WM_APP + 0x0012) // To change WAITING TIME.
#define SWM_APPLYSET                 (WM_APP + 0x0013) // To Apply the changes.
#define SWM_CANCLESET                (WM_APP + 0x0014) // To Cancle the changes.
#define SWM_SAVENEWSETTINGS          (WM_APP + 0x0015) // Save new settings when apply is clicked.

// Mask to change the bit to on if the corresponding setting value was changed.
#define MASK_INPUTFLAG               0b00000001 // Input setting value was changed.
#define MASK_OUTPUTFLAG              0b00000010 // Output setting value was changed.
#define MASK_ERRORFLAG               0b00000100 // Error setting value was changed.
#define MASK_PRINTERFLAG             0b00001000 // Printer setting value was changed.
#define MASK_WTIMEFLAG               0b00010000 // Waiting Time setting value was changed.

//=====================================> SOME GLOBAL CONSTANTS.
// Default config file, where application settings are stored.
#define SETTINGS_CONFIGFILEDIR L"C:\\Users\\HIRANI\\Desktop\\Project\\ASAP\\config.config"
// Number of positions stored in header line.
#define MAXHEADERVALUES 10

// Global and static variables.

extern Console console;
extern TextBox Logger;

// Used to deside whether to exit or restart.
extern DWORD Exit_Code;


// Structure to hold mounted printers fetched.
struct MountedPrinters
{
public:
	// Pointer to the array of printers mounted on the system.
	TCHAR** m_PrinterList = NULL;
	// Number of printers mounted on the system.
	DWORD m_Entries = 0ul;
};

// Structure to hold application settings.
struct AppSettings
{
	TCHAR input_directory[MAX_PATH] = { 0 };
	TCHAR output_directory[MAX_PATH] = { 0 };
	TCHAR error_directory[MAX_PATH] = { 0 };
	TCHAR current_printer[MAX_PATH] = { 0 };
	TCHAR waiting_time[7] = { 0 };
};

// Global functions.

void ErrorMessage(const wchar_t* lpszFunction);
void _Write(const char*);
void _Write(const char*, int);
void _Write(const char*, const char*);

