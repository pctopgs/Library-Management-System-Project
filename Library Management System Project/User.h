#pragma once
#include <iostream>
#include <string>

class User
{
	int userID;					// User ID
	int count = 0;
	std::string userName;		// Username
	std::string firstName;			// User first name
	std::string lastName;			// User last name
	std::string password;		// Password
	std::string userType;		// "admin, student, or guest"
	int bookNo;					// The book that the user has checked out represented by the book number
	// Book bookBorrowed;
	
public:
	User():
		userID(300), userName("Guest"), userType("guest"), firstName(" "), lastName(" "), password(" ")
	{
		;
	}
	
	User(std::string userType)
	{
		// This constructor is a modified test version to create temporary, on the fly users 
		// based on userType instead of userID in order to get a certain part of the program to work
		if (userType == "admin")
		{
			setUserID(500);
			setUserName("Administrator");
			setUserType(userType);
			setFirstN("");
			setLastN("");
			setPassword(".");
		}

		else if (userType == "guest")
		{
			setUserID(300);
			setUserName("Guest");
			setUserType(userType);
			setFirstN(" ");
			setLastN(" ");
			setPassword(" ");
		}
		else if (userType >= "user")
		{
			setUserID(1000);
			setUserName("Standard");
			setUserType(userType);
			setFirstN(" ");
			setLastN(" ");
			setPassword(" ");
		}

	}
	User(int id, std::string name, std::string pass)
	{
		// This constructor is used when creating a brand new user. The new user is automatically assigned "student" for its userType
		int idNum = id + 1000;
		setUserID(idNum);
		setUserName(name);
		setPassword(pass);
		setUserType("student");
		setBookNo(0);
		
		std::cout << "The user " << this->getUserName() << " was created" << std::endl;
	}
	User(int id, std::string un, std::string fn, std::string ln, std::string pw, int bn, std::string ut)
	{
		// This overloaded function is intended to load in User data from the file
		setUserID(id);
		setUserName(un);
		setFirstN(fn);
		setLastN(ln);
		setPassword(pw);
		setUserType(ut);
		setBookNo(bn);
	}
	int getUserID() const
	{
		return userID;
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
		return firstName;
	}
	std::string getLastN()
	{
		return lastName;
	}

	int getBookNo()
	{
		return bookNo;
	}
	
	void setUserID()
	{
		userID = count + 1000;
	}
	void setUserID(int id)			// Overloaded setUID function
	{
		userID = id;
	}
	void setUserName(std::string name)
	{
		userName = name;
	}
	void setFirstN(std::string fn)
	{
		firstName = fn;
	}
	void setLastN(std::string ln)
	{
		lastName = ln;
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