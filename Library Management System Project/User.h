#pragma once
#include <iostream>
#include <string>
class User
{
	std::string userName;
	std::string password;
	std::string userType;

public:
	User()
	{
		setUserName("Guest");
		setUserType("guest");
	}
	std::string getUserName()
	{
		return userName;
	}
	std::string getPassword()
	{
		return password;
	}
	std::string getUserType()
	{
		return userType;
	}

	void setUserName(std::string name)
	{
		userName = name;
	}
	void setPassword(std::string pass)
	{
		password = pass;
	}
	void setUserType(std::string type)
	{
		userType = type;
	}
};