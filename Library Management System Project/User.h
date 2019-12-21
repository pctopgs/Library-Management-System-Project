#pragma once
#include <iostream>
#include <string>

class User
{
	int uid;					// User ID
	//static int countStat;
	int count = 0;
	std::string userName;		// Username
	std::string firstN;			// User first name
	std::string lastN;			// User last name
	std::string password;		// Password
	std::string userType;		// "admin, student, or guest"
	
public:
	User(int id)
	{
		if (id == 500)
		{
			setUID(id);
			setUserName("Administrator");
			setUserType("admin");
			setFirstN("");
			setLastN("");
			setPassword(".");
		}
		else if (id == 300)
		{
			setUID(id);
			setUserName("Guest");
			setUserType("guest");
			setFirstN(" ");
			setLastN(" ");
			setPassword(" ");
		}
		else if (id >= 1000)
		{
			setUID(id);
			setUserName("Guest");
			setUserType("guest");
			setFirstN(" ");
			setLastN(" ");
			setPassword(" ");
		}
		
	}
	User(int id, std::string name, std::string pass/*, std::string type = "student"*/)
	{
		int idNum = id + 1000;
		setUID(idNum);
		setUserName(name);
		setPassword(pass);
		setUserType("student");
		
		std::cout << this->getUserName() << " was created" << std::endl;
	}
	User(int id, std::string un, std::string fn, std::string ln, std::string pw, std::string ut)
	{
		// This overloaded function is intended to load in User data from the file
		setUID(id);
		setUserName(un);
		setFirstN(fn);
		setLastN(ln);
		setPassword(pw);
		setUserType(ut);
	}
	int getUID()
	{
		return uid;
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
	std::string getFirstN()
	{
		return firstN;
	}
	std::string getLastN()
	{
		return lastN;
	}
	
	void setUID()
	{
		uid = count + 1000;
	}
	void setUID(int id)			// Overloaded setUID function
	{
		uid = id;
	}
	void setUserName(std::string name)
	{
		userName = name;
	}
	void setFirstN(std::string fn)
	{
		firstN = fn;
	}
	void setLastN(std::string ln)
	{
		lastN = ln;
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