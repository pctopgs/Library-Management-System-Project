#pragma once
#include <iostream>
#include <string>

class User
{
	int uid;					// User ID
	int count = 0;
	std::string userName;		// Username
	std::string firstN;			// User first name
	std::string lastN;			// User last name
	std::string password;		// Password
	std::string userType;		// "admin, student, or guest"
	int bookNo;					// The book that the user has checked out represented by the book number
	// Book bookBorrowed;
	
public:
	User()
	{
		setUID(300);
		setUserName("Guest");
		setUserType("guest");
		setFirstN(" ");
		setLastN(" ");
		setPassword(" ");
	}
	User(int id)
	{
		// This constructor is normally used to create temporary, on the fly users in order to get a certain part of the program to work
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
	User(int id, std::string name, std::string pass)
	{
		// This constructor is used when creating a brand new user. The new user is automatically assigned "student" for its userType
		int idNum = id + 1000;
		setUID(idNum);
		setUserName(name);
		setPassword(pass);
		setUserType("student");
		setBookNo(0);
		
		std::cout << this->getUserName() << " was created" << std::endl;
	}
	User(int id, std::string un, std::string fn, std::string ln, std::string pw, int bn, std::string ut)
	{
		// This overloaded function is intended to load in User data from the file
		setUID(id);
		setUserName(un);
		setFirstN(fn);
		setLastN(ln);
		setPassword(pw);
		setUserType(ut);
		setBookNo(bn);
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

	int getBookNo()
	{
		return bookNo;
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

	void setBookNo(int num)
	{
		bookNo = num;
	}
};