#include "User.h"

class Book
{
    std::string title;
    std::string author;
    std::string genre;
    std::string content;
    int year;
    int numPages;
    int numChpt;
	int pages;
	int bookNo;

    public:
    void setTitle(std::string);
    void setAuthor(std::string);
    void setGenre(std::string);
    void setContent(std::string);
    void setYear(int);
    void setPages(int);
    void setChpt(int);
    
    std::string getTitle();
    std::string getAuthor();
    std::string getGenre();
    std::string getContent();
    int getYear();
    int getPages();
    int getChpt();
};