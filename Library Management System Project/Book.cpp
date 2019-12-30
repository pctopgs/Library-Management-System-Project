#include "Book.h"

// This contructor is called when importing books from the bookDB file
Book::Book(int bookNo, std::string t, std::string a, std::string g, int c, int y, int nc, int p, std::string co)
{
	setBookNo(bookNo);
	setTitle(t);
	setAuthor(a);
	setGenre(g);
	setChpt(c);
	setYear(y);
	setChpt(nc);
	setPages(p);
	setCheckedOut(co);
}

// Used in conjunction with addBook to add a new book
// (all attributes will have default values except title, author
// and year)
Book::Book(int numBooks, std::string title, std::string author, int year, std::string genre, int content, int numPages, int numChpt, std::string checkedOut)
{
	setNewBookNo(numBooks);
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
std::string Book::getCheckedOut()
{
	std::string checkedOutValue;
	if (checkedOut)
	{
		checkedOutValue = "t";
	}
	else if (!checkedOut)
	{
		checkedOutValue = "f";
	}
	return checkedOutValue;
}
int Book::getChpt()
{
	return numChpt;
}
std::string Book::getDesc()
{
	return desc;
}