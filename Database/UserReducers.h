#pragma once
#include "UserConstants.h"

void GetUserRequests( UserConstant type )
{
	switch (type)
	{
	case UserConstant::GetRequests:
		break;
	case UserConstant::GetPendingRequests:
		break;
	case UserConstant::GetReturnsRequests:
		break;
	case UserConstant::ChangePassword:
		break;
	default:
		break;
	}
}
