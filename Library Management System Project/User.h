#pragma once
#include <iostream>
#include <string>
class User
{
	int uid;					// User ID
	std::string userName;		// Username
	std::string firstN;			// User first name
	std::string lastN;			// User last name
	std::string password;		// Password
	std::string userType;		// "admin, student, or guest"

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
		std::cout << this->getUserName() << " was created" << std::endl;
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
	int getUID()
	{
		return uid;
	}
	std::string getFirstN()
	{
		return firstN;
	}
	std::string getLastN()
	{
		return lastN;
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