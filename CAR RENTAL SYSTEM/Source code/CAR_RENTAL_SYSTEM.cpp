#include "Pages.h"

bool STOP_APP = false;

void SetPage(Page page)
{
	// IF GIVEN PAGE IS ALREAD THE CURRENT PAGE: DO NOTHING
	if (CurrentPage == page) return;

	CurrentPage = page;
}

void SwitchPage()
{
	// SWITCHES FUNCTIONS DEPENDING ON THE CURRENT PAGE
	switch (CurrentPage)
	{
	case Page::HOMEPAGE:
		Homepage(STOP_APP);
		break;
	case Page::U_LOGIN_PAGE:
		LoginPage('U');
		break;
	case Page::A_LOGIN_PAGE:
		LoginPage('A');
		break;
	case Page::REGISTER_PAGE:
		RegisterPage();
		break;
	case Page::NORMALUSER_PAGE:
		NormalUserPage();
		break;
	case Page::ADMINISTRATOR_PAGE:
		AdministratorPage();
		break;
	case Page::PERSONALDETAILS_PAGE:
		PersonalDetailsPage();
		break;
	case Page::ATM_PAGE:
		ATMPage();
		break;
	case Page::U_CHANGEPASSWORD_PAGE:
		ChangePassword('U');
		break;
	case Page::A_CHANGEPASSWORD_PAGE:
		ChangePassword('A');
		break;
	case Page::U_SEND_RETURNSREQUEST_PAGE:
		ReturnRequestPage();
		break;
	case Page::U_SEND_REQUESTS_PAGE:
		UserRequestPage();
		break;
	case Page::APPROVEREQUEST_PAGE:
		ApproveRequest();
		break;
	case Page::U_LOGOUT_PAGE:
		LogOutPage('U');
		break;
	case Page::A_LOGOUT_PAGE:
		LogOutPage('A');
		break;
	default:
		std::cout << "Page Unavailable\n";
		break;
	}
}

int main()
{
	// INITIALIZING THE DATABASE
	Database::Initialize();

	// LOOP WILL RUN UNTIL THE APPLICATION IS EXITED
	while (!STOP_APP)
	{
		SwitchPage();
	}
	
	_NewLine(2);

	Utils::Wait();
}