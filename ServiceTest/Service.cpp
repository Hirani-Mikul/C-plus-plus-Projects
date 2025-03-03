#pragma once

#include <Windows.h>
#include <iostream>

#define SERVICE_NAME TEXT("AUTO SCAN AND PRINT")

#define LOG_ERROR(message, error) \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); \
	std::cout << message << " -> " << error << std::endl; \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15) 


#define LOG_SUCCESS(message) \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); \
	std::cout << message << std::endl; \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15) 


#define LOG_WARNING(message) \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); \
	std::cout << message << std::endl; \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)

	

#define LOG_INFO(message) \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); \
	std::cout << message << std::endl; \
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15) 


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
	//std::cout << "In main function" << std::endl;

	BOOL bStServiceCtrlDispatcher = FALSE;


	if (lstrcmpA(argv[1], "install") == 0)
	{
		// Call Service Install

		ServiceInstall();
		LOG_SUCCESS("Main: Installed Successfully.");
	}
	else if (lstrcmpA(argv[1], "start") == 0)
	{
		// Call Service Start

		ServiceStart();
		
		LOG_SUCCESS("Main: Service Started Successfully.");

	}
	else if (lstrcmpA(argv[1], "stop") == 0)
	{
		// Call Service Stop

		ServiceStop();

		LOG_SUCCESS("Main: Service Stopped Successfully.");
	}
	else if (lstrcmpA(argv[1], "delete") == 0)
	{
		// Call Service Delete

		ServiceDelete();

		LOG_SUCCESS("Main: Service Deleted Successfully.");
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
			LOG_ERROR("Main: StartServiceCtrlDispatcher Failed", GetLastError());
		}
		else
		{
			LOG_SUCCESS("Main: StartServiceCtrlDispatcher Success.");
		}
	}

	//std::cout << "In Main End" << std::endl;
}

void WINAPI ServiceMain(DWORD dwArgc, LPTSTR *lpArgv) {

	//std::cout << "ServiceMain Start" << std::endl;

	BOOL bServiceStatus = FALSE;

	hServiceStatusHandle = RegisterServiceCtrlHandler(
		SERVICE_NAME,
		ServiceControlHandler
	);

	if (NULL == hServiceStatusHandle)
	{
		LOG_ERROR("ServiceMain: RegisterSericeCtrlHandler Failed.", GetLastError());
	}
	else {
		LOG_SUCCESS("ServiceMain: RegisterServiceCtrlHandler Success.");

	}

	ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceReportStatus(SERVICE_START_PENDING, NO_ERROR, 3000);

	bServiceStatus = SetServiceStatus(hServiceStatusHandle, &ServiceStatus);

	if (FALSE == bServiceStatus)
	{
		LOG_ERROR("ServiceMain: Service Status Initial Setup FAILED", GetLastError());
	}
	else
		LOG_SUCCESS("ServiceMain: Service Status Initial Setup SUCCESS.");

	ServiceInit(dwArgc, lpArgv);

	//std::cout << "ServiceMain End" << std::endl;

}

void WINAPI ServiceControlHandler(DWORD dwControl)
{
	//std::cout << "ServiceControlHandler" << std::endl;

	switch (dwControl)
	{
	case SERVICE_CONTROL_STOP:
		LOG_INFO("ServiceControlHandler: Service Stopped.");
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
	//std::cout << "ServiceReportStatus Start" << std::endl;

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
	{
		LOG_ERROR("ServiceReportStatus: Service Status Failed", GetLastError());
	}
	else
		LOG_SUCCESS("ServiceReportStatus: Service Status SUCCESS");

	
	//std::cout << "ServiceReportStatus END" << std::endl;
	

}

void ServiceInit(DWORD dwArgc, LPTSTR* lpArgv) {

	//std::cout << "ServiceInit Start" << std::endl;

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

	//std::cout << "ServiceInit End" << std::endl;
}

void ServiceInstall(void) {

	//std::cout << "ServiceInstall Start" << std::endl;

	SC_HANDLE hScOpenSCManager = NULL;
	SC_HANDLE hScCreateService = NULL;
	DWORD dwGetModuleFileName = 0;
	TCHAR szPath[MAX_PATH];


	dwGetModuleFileName = GetModuleFileName(NULL, szPath, MAX_PATH);

	if (0 == dwGetModuleFileName)
	{
		LOG_ERROR("ServiceInstall: Service Installation Failed", GetLastError());
	}
	else {
		LOG_SUCCESS("ServiceInstall: Successfully Installed The File.");
	}

	hScOpenSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS
	);

	if (NULL == hScOpenSCManager) {

		LOG_ERROR("ServiceInstall: OpenSCManager Failed", GetLastError());
	}
	else
		LOG_SUCCESS("ServiceInstall: OpenSCManager Success.");


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
		LOG_ERROR("ServiceInstall: CreateService Failed", GetLastError());
		CloseServiceHandle(hScOpenSCManager);
	}
	else
		LOG_SUCCESS("ServiceInstall: CreateService Success.");

	CloseServiceHandle(hScCreateService);
	CloseServiceHandle(hScOpenSCManager);

	//std::cout << "ServiceInstall End" << std::endl;
}




void ServiceDelete(void) {

	//std::cout << "ServiceDelete Start" << std::endl;

	SC_HANDLE hScOpenSCManager = NULL;
	SC_HANDLE hScOpenService = NULL;
	BOOL bDeleteService = FALSE;

	hScOpenSCManager = OpenSCManager(
		NULL,
		NULL,
		SC_MANAGER_ALL_ACCESS
	);

	if (NULL == hScOpenSCManager)
	{
		LOG_ERROR("ServiceDelete: OpenScManager Failed", GetLastError());
	}
	else
		LOG_SUCCESS("ServiceDelete: OpenScManager Success.");

	hScOpenService = OpenService(
		hScOpenSCManager,
		SERVICE_NAME,
		SERVICE_ALL_ACCESS
	);

	if (NULL == hScOpenService)
	{
		LOG_ERROR("ServiceDelete: OpenService Failed", GetLastError());
	}
	else
		LOG_SUCCESS("ServiceDelete: OpenService Success.");

	bDeleteService = DeleteService(hScOpenService);

	if (FALSE == bDeleteService)
	{
		LOG_ERROR("ServiceDelete: Delete Service Failed", GetLastError());
	}
	else
		LOG_SUCCESS("ServiceDelete: Delete Service Success.");

	CloseServiceHandle(hScOpenService);
	CloseServiceHandle(hScOpenSCManager);

	//std::cout << "ServiceDelete End" << std::endl;
}


void ServiceStart(void) {
	//std::cout << "Inside ServiceStart" << std::endl;
	
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

	if (NULL == hOpenSCManager)
	{
		LOG_ERROR("ServiceStart: hOpenSCManager Failed", GetLastError());
	}
	else
		LOG_SUCCESS("ServiceStart: hOpenSCManager Success.");

	hOpenService = OpenService(
		hOpenSCManager,
		SERVICE_NAME,
		SC_MANAGER_ALL_ACCESS
	);

	if (NULL == hOpenSCManager)
	{
		LOG_ERROR("ServiceStart: hOpenService Failed", GetLastError());
		CloseServiceHandle(hOpenSCManager);
	}
	else
		LOG_SUCCESS("ServiceStart: hOpenService Success.");

	bQueryServiceStatus = QueryServiceStatusEx(
		hOpenService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&SvcStatusProcess,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded
	);

	if (FALSE == bQueryServiceStatus)
	{
		LOG_ERROR("ServiceStart: QueryService Failed", GetLastError());
	}
	else
		LOG_SUCCESS("ServiceStart: QueryService Success.");


	if ((SvcStatusProcess.dwCurrentState != SERVICE_STOPPED) &&
		(SvcStatusProcess.dwCurrentState != SERVICE_STOP_PENDING))
	{
		LOG_INFO("ServiceStart: Service Is Already Running.");
	}
	else
	{
		LOG_INFO("ServiceStart: Service Is Already Stopped.");
	}

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
			LOG_ERROR("ServiceStart: QueryService Failed", GetLastError());
			CloseServiceHandle(hOpenService);
			CloseServiceHandle(hOpenSCManager);
		}
		else
			LOG_SUCCESS("ServiceStart: QueryService Success.");
	}

	bStartService = StartService(
		hOpenService,
		NULL,
		NULL
	);

	if (FALSE == bStartService) {
		LOG_ERROR("ServiceStart: StartService Failed", GetLastError());
		CloseServiceHandle(hOpenService);
		CloseServiceHandle(hOpenSCManager);
	}
	else {
		LOG_SUCCESS("ServiceStart: StartService Success.");
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
		LOG_ERROR("ServiceStart: QueryService Failed", GetLastError());
		CloseServiceHandle(hOpenService);
		CloseServiceHandle(hOpenSCManager);
	}
	else
		LOG_INFO("ServiceStart: QueryService Success.");

	if (SvcStatusProcess.dwCurrentState == SERVICE_RUNNING) {

		LOG_INFO("ServiceStart: Service Started Running...");
		std::cout << "Service Started Running..." << std::endl;
	}
	else {
		LOG_ERROR("ServiceStart: Service Running Failed", GetLastError());
		CloseServiceHandle(hOpenService);
		CloseServiceHandle(hOpenSCManager);
	}

	CloseServiceHandle(hOpenService);
	CloseServiceHandle(hOpenSCManager);

	//std::cout << "Inside ServiceStart END" << std::endl;

}
/************************************************************************************************
*************************************************************************************************
*************************************************************************************************/

void ServiceStop(void) {

	//std::cout << "Inside ServiceStop" << std::endl;

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

	if (NULL == hScOpenSCManager) {
		LOG_ERROR("ServiceStop: hOpenSCManager Failed", GetLastError());
	}
	else
		LOG_SUCCESS("ServiceStop: hOpenSCManager Success.");

	hScOpenService = OpenService(
		hScOpenSCManager,
		SERVICE_NAME,
		SC_MANAGER_ALL_ACCESS
	);

	if (NULL == hScOpenSCManager)
	{
		LOG_ERROR("ServiceStop: hOpenService Failed", GetLastError());
		CloseServiceHandle(hScOpenSCManager);
	}
	else 
		LOG_SUCCESS("ServiceStop: hOpenService Success.");

	bQueryServiceStatus = QueryServiceStatusEx(
		hScOpenService,
		SC_STATUS_PROCESS_INFO,
		(LPBYTE)&SvcStatusProcess,
		sizeof(SERVICE_STATUS_PROCESS),
		&dwBytesNeeded
	);

	if (FALSE == bQueryServiceStatus)
	{
		LOG_ERROR("ServiceStop: QueryService Failed", GetLastError());
		CloseServiceHandle(hScOpenService);
		CloseServiceHandle(hScOpenSCManager);
	}
	else
		LOG_SUCCESS("ServiceStop: QueryService Success.");

	bControlService = ControlService(
		hScOpenService,
		SERVICE_CONTROL_STOP,
		(LPSERVICE_STATUS)&SvcStatusProcess
	);

	if (TRUE == bControlService) {

		LOG_SUCCESS("ServiceStop: Control Service Success.");
	}
	else {
		LOG_ERROR("ServiceStop: Control Service Failed", GetLastError());
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
			LOG_ERROR("ServiceStop: QueryService Failed", GetLastError());
			CloseServiceHandle(hScOpenService);
			CloseServiceHandle(hScOpenSCManager);
		}
		else
			LOG_SUCCESS("ServiceStop: QueryService Success.");

		if (SvcStatusProcess.dwCurrentState == SERVICE_STOPPED)
		{
			LOG_SUCCESS("ServiceStop: Stopped Successfully.");
			break;
		}
		else {
			LOG_ERROR("ServiceStop: Service Stop Failed", GetLastError());

		}
	}

	CloseServiceHandle(hScOpenService);
	CloseServiceHandle(hScOpenSCManager);

	//std::cout << "Inside ServiceStop END" << std::endl;
}