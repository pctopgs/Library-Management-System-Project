#include "Book.h"

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