#pragma once
#include <iostream>
#include "Schema.h"

// THIS HEADER FILE CREATES SOME GLOBAL VARIABLES

enum class Page : unsigned int
{
	HOMEPAGE = 0u,
	U_LOGIN_PAGE,
	A_LOGIN_PAGE,
	REGISTER_PAGE,

	NORMALUSER_PAGE,
	ADMINISTRATOR_PAGE,

	PERSONALDETAILS_PAGE,
	ATM_PAGE,
	U_CHANGEPASSWORD_PAGE,
	A_CHANGEPASSWORD_PAGE,

	U_SEND_RETURNSREQUEST_PAGE,
	U_SEND_REQUESTS_PAGE,

	APPROVEREQUEST_PAGE,

	U_LOGOUT_PAGE,
	A_LOGOUT_PAGE,
};

Page CurrentPage = Page::HOMEPAGE;

NormalUser* CurrentUser = nullptr;
AdminUser* CurrentAdminUser = nullptr;

