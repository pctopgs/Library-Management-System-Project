#include "Book.h"

Book::Book(int bn, std::string t, std::string a, std::string g, int c, int y, int np, int nc, int p, std::string co)
{
	setTitle(t);
	setAuthor(a);
	setGenre(g);
	setChpt(c);
	setYear(y);
	setPages(np);
	setChpt(nc);
	setPages(p);
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
    ;
}
void Book::setContent(std::string aContent)
{
    ;
}
void Book::setYear(int aYear)
{
    ;
}
void Book::setPages(int aPages)
{
    ;
}
void Book::setChpt(int aChpt)
{
    ;
}
void Book::setCheckedOut(std::string co)
{
	if (co == "t")
	{
		checkedOut = true;
	}
	if (co == "f")
	{
		checkedOut = false;
	}
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