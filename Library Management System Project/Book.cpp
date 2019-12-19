#include "Book.h"

Book::Book(std::string bookNo, std::string t, std::string a, std::string g, int c, int y, int nc, int p, std::string co)
{
	setBookNo(bookNo);
	setTitle(t);
	setAuthor(a);
	setGenre(g);
	setChpt(c);
	setYear(y);
	setChpt(nc);
	setPages(p);
}

// Used in conjunction with addBook to add a new book
// (all attributes will have default values except title, auther
// and year)
Book::Book(std::string title, std::string author, int year, std::string genre, int content, int numPages, int numChpt, std::string checkedOut)
{
	setNewBookNo(title, author, year);
	setTitle(title);
	setAuthor(author);
	setGenre(genre);
	setChpt(content);
	setYear(year);
	setPages(numPages);
	setChpt(numChpt);
	setCheckedOut(checkedOut);
}
void Book::setTitle(std::string aTitle)
{
    title = aTitle;
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
void Book::setCheckedOut(std::string co)
{
	if (co == "t")
	{
		checkedOut = true;
	}
	else if (co == "f")
	{
		checkedOut = false;
	}
	else
		std::cout << "There is an issue with checkedOut info" << std::endl;
}
void Book::setBookNo(std::string num)
{
	bookNo = num;
}

// This function will take the first too characters from the title
// the last two characters from the author 
// and the year
// and create a new int  concantonated based on the following format:
// LAST2AUTHOR + YEAR + FIRST2TITLE
void Book::setNewBookNo(std::string title, std::string author, int year)
{
	std::string yearString = std::to_string(year);		// creates a string version of the year
	std::string authorLastTwo = author.substr(author.length() - 2);
	std::string titleFirstTwo = title.substr(0,1);
	bookNo = authorLastTwo + yearString + titleFirstTwo;
}
void Book::setDesc(std::string aDesc)
{
	desc = aDesc;
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
std::string Book::getBookNo()
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