#pragma once
// The Author class
#include <string>

class Author
{
private:
	static int numOfAuthors ;
	int authorID;
	std::string fName;
	std::string lName;
	std::string pName;
	//std::string nationality;
	//std::vector<std::string> genres;
	//int booksPublished;

	
public:
	// This function is used with the importAuthor function to import an Author from the author file
	// The parameters is takes are for numOfAuthors, authorID, fName, lName, and pName
	Author(int uniqueID, std::string firstName, std::string lastName, std::string penName)
	{
		//numOfAuthors = numberOfAuthors;
		authorID = uniqueID;
		fName = firstName;
		lName = lastName;
		pName = penName;
	}

	// This overloaded constructor is used with the importAuthor function to import an Author from the author file
	// The parameters is takes are for numOfAuthors, authorID, fName, lName
	Author(int uniqueID, std::string firstName, std::string lastName)
	{
		//numOfAuthors = numberOfAuthors;
		authorID = uniqueID;
		fName = firstName;
		lName = lastName;
		//pName = penName;
	}

	// This function is used with the addAuthor function to add a new author to the vector. 
	// A unique Author ID is created with this author
	Author(std::string firstName, std::string lastName, std::string penName, int numAuth)
	{
		//numOfAuthors++;
		//authorID = numOfAuthors;
		fName = firstName;
		lName = lastName;
		pName = penName;
		authorID = numAuth + 97;

		//this->nationality = nationality;
	}

	std::string getFName()
	{
		return fName;
	}

	std::string getLName() const
	{
		return lName;
	}

	std::string getPName() const
	{
		return pName;
	}

	int getAuthorID() const
	{
		return authorID;
	}

	std::string getFullName()
	{
		return this->fName + " " + this->lName;
	}

	//std::string getAuthorName(int authID)
	//{

	//	return 
	//}
	//std::string getAuthorName();
};