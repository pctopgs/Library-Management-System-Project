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
	User(std::string name, std::string pass, std::string type = "student")
	{
		setUserName(name);
		setPassword(pass);
		setUserType(type);
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