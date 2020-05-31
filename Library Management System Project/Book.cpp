#include "Book.h"
#include <sstream>

// This contructor is called when importing books from the bookDB file
Book::Book(int bookNo, std::string title, std::string author, std::string genre, int c, int y, int nc, int p, int co, int authID)
{
	setBookNo(bookNo);
	setTitle(title);
	setAuthor(author);
	setGenre(genre);
	setChpt(c);
	setYear(y);
	setChpt(nc);
	setPages(p);
	setCheckedOut(co);
	setAuthorID(authID);
}

// Used in conjunction with addBook() to add a new book
// (all attributes will have default values except title, author
// and year)
//Book::Book(int numBooks, std::string title, std::string author, int year, std::string genre, int content, int numPages, int numChpt, int checkedOut)
Book::Book(int numBooks, std::string title, int authID, int year, int checkedOut) :
	authorID(authID), year(year)
{
	setTitle(title);
	setNewBookNo(numBooks);
	setCheckedOut(checkedOut);
	std::cout << title << " was added to the library.\n";
}

void Book::setTitle(std::string aTitle)
{
	// Break the string in the parameter and put them in an array of strings. 
	// Ultimately making the title easier to search..
	std::string titleElement;
	std::vector<std::string> tempTitle;
	std::stringstream flow(aTitle);
	while (std::getline(flow, titleElement, ' '))
	{
		tempTitle.push_back(titleElement);
	}
	this->title = tempTitle;
}
void Book::setAuthor(std::string authName)
{
	authorName = authName;
}
//void Book::setAuthor(std::string aAuthor)
//{
//    author = aAuthor;
//}
void Book::setGenre(std::string aGenre)
{
    genre = aGenre;
}
void Book::setContent(std::string aContent)
{
    content = aContent;
}
void Book::setYear(int aYear)
{
    year = aYear;
}
void Book::setPages(int aPages)
{
    pages = aPages;
}
void Book::setChpt(int aChpt)
{
    numChpt = aChpt;
}
void Book::setCheckedOut(int co)
{
	checkedOut = co;
}
void Book::setBookNo(int num)
{
	bookNo = num;
}

// This function is simply the number books + 100
// may need to chnage this later because the number books can go down
void Book::setNewBookNo(int numBook)
{
	bookNo = numBook + 100;
}
void Book::setDesc(std::string aDesc)
{
	desc = aDesc;
}

void Book::setAuthorID(int authID)
{
	authorID = authID;
}

// Returns the title by converting the title vector into a single string
std::string Book::getTitle()
{
	std::string titleOutput;
	std::stringstream flow;
	for (int i = 0; i < title.size(); i++)
	{
		flow << title[i] << " ";
	}
	std::getline(flow, titleOutput);
	flow.str("");

	return titleOutput;
}

// TODO: Complete
std::string Book::getAuthorName(Author authObj)
{
	// Take the authorID and return the 
	return authObj.getFullName();
}

std::string Book::getAuthor()
{
	return authorName;
}

std::string Book::getContent()
{
	return content;
}
std::string Book::getGenre()
{
	return genre;
}
int Book::getYear()
{
	return year;
}
int Book::getPages()
{
	return pages;
}
int Book::getBookNo()
{
	return bookNo;
}

bool Book::getCheckedOut()
{
	return checkedOut;
}
int Book::getChpt()
{
	return numChpt;
}
std::string Book::getDesc()
{
	return desc;
}

void Book::showThis()
{
	std::cout << this << std::endl;
}

int Book::getAuthorID(){
	if (authorID)
		return authorID;
	else
		return 0;
}