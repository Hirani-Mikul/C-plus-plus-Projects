#pragma once

#include <Windows.h>
#include <iostream>

#define SERVICE_NAME TEXT("AUTO SCAN AND PRINT")

#define LOG_ERROR(message, error) std::cout << message << error << std::endl 
#define LOG_SUCCESS(message) std::cout << message << std::endl
#define LOG_WARNING(message) std::cout << message << std::endl
#define LOG_INFO(message) std::cout << message << std::endl

SERVICE_STATUS ServiceStatus = { 0 };
SERVICE_STATUS_HANDLE hServiceStatusHandle = NULL;
HANDLE hServiceEvent = NULL;


void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv);
void WINAPI ServiceControlHandler(DWORD dwControl);

void ServiceReportStatus(
	DWORD dwCurrentState,
	DWORD dwWin32ExitCode,
	DWORD dwWaitHint
);

void ServiceInit(DWORD dwArgc, LPTSTR* lpArgv);
void ServiceInstall(void);
void ServiceDelete(void);
void ServiceStart(void);
void ServiceStop(void);




int main(int argc, CHAR* argv[])
{
	std::cout << "In main function" << std::endl;

	BOOL bStServiceCtrlDispatcher = FALSE;


	if (lstrcmpA(argv[1], "install") == 0)
	{
		// Call Service Install

		ServiceInstall();

		std::cout << "Installation Success" << std::endl;
	}
	else if (lstrcmpA(argv[1], "start") == 0)
	{
		// Call Service Start

		ServiceStart();

		std::cout << "ServiceStart Success" << std::endl;
	}
	else if (lstrcmpA(argv[1], "end") == 0)
	{
		// Call Service Stop

		ServiceStop();

		std::cout << "ServiceStop Success" << std::endl;
	}
	else if (lstrcmpA(argv[1], "delete") == 0)
	{
		// Call Service Delete

		ServiceDelete();

		std::cout << "ServiceDelete Success" << std::endl;

	}
	else {
		// Fill the service table entry

		SERVICE_TABLE_ENTRY DispatchTable[] =
		{
			{(LPWSTR)SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION)ServiceMain},
			{NULL, NULL}
		};

		bStServiceCtrlDispatcher = StartServiceCtrlDispatcher(DispatchTable);


		// Start service control dispatcher

		if (FALSE == bStServiceCtrlDispatcher)
		{
			std::cout << "StartServiceCtrlDispatcher Failed" << GetLastError() << std::endl;
		}
		else
		{
			std::cout << "StartServiceCtrlDispatcher Success" << std::endl;
		}
	}

	std::cout << "In Main End" << std::endl;
}

void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv) {

	std::cout << "ServiceMain Start" << std::endl;

	BOOL bServiceStatus = FALSE;

	hServiceStatusHandle = RegisterServiceCtrlHandler(
		SERVICE_NAME,
		ServiceControlHandler
	);

	if (NULL == hServiceStatusHandle)
	{
		std::cout << "RegisterSericeCtrlHandler Failed " << GetLastError() << std::endl;
	}
	else {
		std::cout << "RegisterServiceCtrlHandler Success" << std::endl;

	}

	ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceReportStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

	bServiceStatus = SetServiceStatus(hServiceStatusHandle, &ServiceStatus);

	if (FALSE == bServiceStatus)
		std::cout << "Service Status Initial Setup FAILED = " << GetLastError() << std::endl;
	else std::cout << "Service Status Initial Setup SUCCESS" << std::endl;

	ServiceInit(dwArgc, lpArgv);

	std::cout << "ServiceMain End" << std::endl;

}

void WINAPI ServiceControlHandler(DWORD dwControl)
{
	std::cout << "ServiceControlHandler" << std::endl;

	switch (dwControl)
	{
	case SERVICE_CONTROL_STOP:
		std::cout << "SERVICE STOPPED" << std::endl;
		ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);

		break;

	default:
		break;
	}
}

void ServiceReportStatus(
	DWORD dwCurrentState,
	DWORD dwWin32ExitCode,
	DWORD dwWaitHint
) {
	std::cout << "ServiceReportStatus Start" << std::endl;

	static DWORD dwCheckPoint = 1;
	BOOL bSetServiceStatus = FALSE;

	ServiceStatus.dwCurrentState = dwCurrentState;
	ServiceStatus.dwWin32ExitCode = dwWin32ExitCode;
	ServiceStatus.dwWaitHint = dwWaitHint;


	if (dwCurrentState == SERVICE_START_PENDING)
	{
		// Service is about to start
		ServiceStatus.dwControlsAccepted = 0;
	}
	else ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;


	if ((dwCurrentState == SERVICE_RUNNING) || (dwCurrentState == SERVICE_STOPPED))
		ServiceStatus.dwCheckPoint = 0;
	else ServiceStatus.dwCheckPoint = dwCheckPoint++;

	bSetServiceStatus = SetServiceStatus(hServiceStatusHandle, &ServiceStatus);

	if (FALSE == bSetServiceStatus)
		std::cout << "Service Status FAILED" << GetLastError() << std::endl;
	else std::cout << "Service Status SUCCESS" << std::endl;

	
	std::cout << "ServiceReportStatus END" << std::endl;
	

}

void ServiceInit(DWORD dwArgc, LPTSTR* lpArgv) {

	std::cout << "ServiceInit Start" << std::endl;

	hServiceEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		NULL
	);

	if (NULL == hServiceEvent)
	{

		ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
	}
	else {

		ServiceReportStatus(SERVICE_RUNNING, NO_ERROR, 0);
	}

	while (1)
	{
		WaitForSingleObject(hServiceEvent, INFINITE);
		ServiceReportStatus(SERVICE_STOPPED, NO_ERROR, 0);
	}

	std::cout << "ServiceInit End" << std::endl;
}

void ServiceInstall(void) {

	std::cout << "ServiceInstall Start" << std::endl;

	SC_HANDLE hScOpenSCManager = NULL;
	SC_HANDLE hScCreateService = NULL;
	DWORD dwGetModuleFileName = 0;
	TCHAR szPath[MAX_PATH];


	dwGetModuleFileName = GetModuleFileName(NULL, szPath, MAX_PATH);

	if (0 == dwGetModuleFileName)
	{
		std::cout << "Service Installation Failed = " << GetLastError() << std::endl;
	}
	else {
		std::cout << "Successfully install the File" << std::endl;
	}

	hScOpenSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS
	);

	if (NULL == hScOpenSCManager) std::cout << "OpenSCManager Failed = " << GetLastError() << std::endl;
	else std::cout << "OpenSCManager Success" << std::endl;


	hScCreateService = CreateService(
		hScOpenSCManager,
		SERVICE_NAME,
		SERVICE_NAME,
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		szPath,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	);

	if (NULL == hScCreateService)
	{
		std::cout << "CreateService Failed = " << GetLastError() << std::endl;
		CloseServiceHandle(hScOpenSCManager);
	}
	else std::cout << "CreateService Success" << std::endl;

	CloseServiceHandle(hScCreateService);
	CloseServiceHandle(hScOpenSCManager);

	std::cout << "ServiceInstall End" << std::endl;
}




void ServiceDelete(void) {

	std::cout << "ServiceDelete Start" << std::endl;

	SC_HANDLE hScOpenSCManager = NULL;
	SC_HANDLE hScOpenService = NULL;
	BOOL bDeleteService = FALSE;

	hScOpenSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS
	);

	if (NULL == hScOpenSCManager)
		std::cout << "OpenScManager Failed = " << GetLastError << std::endl;
	else
		std::cout << "OpenScManager Success" << std::endl;

	hScOpenService = OpenService(
		hScOpenSCManager,
		SERVICE_NAME,
		SERVICE_ALL_ACCESS
	);

	if (NULL == hScOpenService)
		std::cout << "OpenService Failed = " << GetLastError() << std::endl;
	else
		std::cout << "OpenService Success" << std::endl;

	bDeleteService = DeleteService(hScOpenService);

	if (FALSE == bDeleteService)
		std::cout << "Delete Service Failed = " << GetLastError() << std::endl;
	else std::cout << "Delete Service Success" << std::endl;

	CloseServiceHandle(hScOpenService);
	CloseServiceHandle(hScOpenSCManager);

	std::cout << "ServiceDelete End" << std::endl;
}


void ServiceStart(void) {
	std::cout << "Inside ServiceStart" << std::endl;
	
	BOOL bStartService = FALSE;
	SERVICE_STATUS_PROCESS SvcStatusProcess;
	SC_HANDLE hOpenSCManager = NULL;
	SC_HANDLE hOpenService = NULL;
	BOOL bQueryServiceStatus = FALSE;
	DWORD dwBytesNeeded;

	hOpenSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS
	);

	if (NULL == hOpenSCManager) std::cout << "hOpenSCManager Failed = " << GetLastError() << std::endl;
	else std::cout << "hOpenSCManager Success" << std::endl;

	hOpenService = OpenService(
		hOpenSCManager,
		SERVICE_NAME,
		SC_MANAGER_ALL_ACCESS
	);

	if (NULL == hOpenSCManager)
	{
		std::cout << "hOpenService Failed = " << GetLastError() << std::endl;
		CloseServiceHandle(hOpenSCManager);
	}
	else std::cout << "hOpenService Success" << std::endl;

	bQueryServiceStatus = QueryServiceStatusEx(
		hOpenService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&SvcStatusProcess,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded
	);

	if (FALSE == bQueryServiceStatus)
		std::cout << "QueryService Failed = " << GetLastError() << std::endl;
	else
		std::cout << "QueryService Success" << std::endl;


	if ((SvcStatusProcess.dwCurrentState != SERVICE_STOPPED) && 
		(SvcStatusProcess.dwCurrentState != SERVICE_STOP_PENDING))
		std::cout << "Service is already running" << std::endl;
	else
		std::cout << "Service is already stopped" << std::endl;

	while (SvcStatusProcess.dwCurrentState == SERVICE_STOP_PENDING)
	{
		bQueryServiceStatus = QueryServiceStatusEx(
			hOpenService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&SvcStatusProcess,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded
		);

		if (FALSE == bQueryServiceStatus)
		{
			std::cout << "QueryService Failed = " << GetLastError() << std::endl;
			CloseServiceHandle(hOpenService);
			CloseServiceHandle(hOpenSCManager);
		}
		else
			std::cout << "QueryService Success" << std::endl;
	}

	bStartService = StartService(
		hOpenService,
		NULL,
		NULL
	);

	if (FALSE == bStartService) {
		std::cout << "StartService Failed = " << GetLastError() << std::endl;
		CloseServiceHandle(hOpenService);
		CloseServiceHandle(hOpenSCManager);
	}
	else {
		std::cout << "StartService Success" << std::endl;
	}

	bQueryServiceStatus = QueryServiceStatusEx(
		hOpenService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&SvcStatusProcess,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded
	);

	if (FALSE == bQueryServiceStatus)
	{
		std::cout << "QueryService Failed = " << GetLastError() << std::endl;
		CloseServiceHandle(hOpenService);
		CloseServiceHandle(hOpenSCManager);
	}
	else
		std::cout << "QueryService Success" << std::endl;

	if (SvcStatusProcess.dwCurrentState == SERVICE_RUNNING) {
		std::cout << "Service Started Running..." << std::endl;
	}
	else {
		std::cout << "Service Running Failed = " << GetLastError() << std::endl;
		CloseServiceHandle(hOpenService);
		CloseServiceHandle(hOpenSCManager);
	}

	CloseServiceHandle(hOpenService);
	CloseServiceHandle(hOpenSCManager);

	std::cout << "Inside ServiceStart END" << std::endl;

}
/************************************************************************************************
*************************************************************************************************
*************************************************************************************************/

void ServiceStop(void) {

	std::cout << "Inside ServiceStop" << std::endl;

	SERVICE_STATUS_PROCESS SvcStatusProcess;
	SC_HANDLE hScOpenSCManager = NULL;
	SC_HANDLE hScOpenService = NULL;
	BOOL bQueryServiceStatus = TRUE;
	BOOL bControlService = TRUE;
	DWORD dwBytesNeeded;

	hScOpenSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS
	);

	if (NULL == hScOpenSCManager) std::cout << "hOpenSCManager Failed = " << GetLastError() << std::endl;
	else std::cout << "hOpenSCManager Success" << std::endl;

	hScOpenService = OpenService(
		hScOpenSCManager,
		SERVICE_NAME,
		SC_MANAGER_ALL_ACCESS
	);

	if (NULL == hScOpenSCManager)
	{
		std::cout << "hOpenService Failed = " << GetLastError() << std::endl;
		CloseServiceHandle(hScOpenSCManager);
	}
	else std::cout << "hOpenService Success" << std::endl;

	bQueryServiceStatus = QueryServiceStatusEx(
		hScOpenService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&SvcStatusProcess,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded
	);

	if (FALSE == bQueryServiceStatus)
	{
		std::cout << "QueryService Failed = " << GetLastError() << std::endl;
		CloseServiceHandle(hScOpenService);
		CloseServiceHandle(hScOpenSCManager);
	}
	else
		std::cout << "QueryService Success" << std::endl;

	bControlService = ControlService(
		hScOpenService,
		SERVICE_CONTROL_STOP,
		(LPSERVICE_STATUS)&SvcStatusProcess
	);

	if (TRUE == bControlService) std::cout << "Control Service Success" << std::endl;
	else {
		std::cout << "Control Service Failed = " << GetLastError() << std::endl;
		CloseServiceHandle(hScOpenService);
		CloseServiceHandle(hScOpenSCManager);
	}


	while (SvcStatusProcess.dwCurrentState == SERVICE_STOPPED)
	{
		bQueryServiceStatus = QueryServiceStatusEx(
			hScOpenService,
			SC_STATUS_PROCESS_INFO,
			(LPBYTE)&SvcStatusProcess,
			sizeof(SERVICE_STATUS_PROCESS),
			&dwBytesNeeded
		);

		if (FALSE == bQueryServiceStatus)
		{
			std::cout << "QueryService Failed = " << GetLastError() << std::endl;
			CloseServiceHandle(hScOpenService);
			CloseServiceHandle(hScOpenSCManager);
		}
		else
			std::cout << "QueryService Success" << std::endl;

		if (SvcStatusProcess.dwCurrentState == SERVICE_STOPPED)
		{
			std::cout << "Service Stopped Successfully" << std::endl;
			break;
		}
		else {
			std::cout << "Service Stopped FAILED" << GetLastError() << std::endl;

		}
	}

	CloseServiceHandle(hScOpenService);
	CloseServiceHandle(hScOpenSCManager);

	std::cout << "Inside ServiceStop END" << std::endl;
}