#include "Book.h"

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
	title(title), authorID(authID), year(year)
{
	setNewBookNo(numBooks);
	setCheckedOut(checkedOut);
	std::cout << title << " was added to the library.\n";
}
//void Book::setTitle(std::string aTitle)
//{
//    title = aTitle;
//}


void Book::setTitle(std::string aTitle)
{
	// Trying to change the set title function to break the string in  the parameter and put
	// them in an array of strings. The ultimate goal is to make the title easier to search..
	title = aTitle;
	//std::vector<std::string> titles;
}
void Book::setAuthor(std::string aAuthor)
{
    author = aAuthor;
}
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

// This function will take the first too characters from the title
// the last two characters from the author 
// and the year
// and create a new int  concantonated based on the following format:
// LAST2AUTHOR + YEAR + FIRST2TITLE
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

std::string Book::getTitle()
{
    return title;
}
std::string Book::getAuthor()
{
	return author;
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
//std::string Book::getCheckedOut()
bool Book::getCheckedOut()
{
	/*std::string checkedOutValue;
	if (checkedOut)
	{
		checkedOutValue = "t";
	}
	else if (!checkedOut)
	{
		checkedOutValue = "f";
	}
	return checkedOutValue;
	*/
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