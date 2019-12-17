#include "User.h"

class Book
{
	int bookNo;
    std::string title;
    std::string author;
    std::string genre;
    std::string content;
    int year;
    int numPages;
    int numChpt;
	int pages;
	bool checkedOut;

    public:
	Book(int bn, std::string t, std::string a, std::string g, int c, int y, int np, int nc, int p, std::string co);
	// Used in conjunction with addBook to add a new book
	// (all attributes will have default values except title, auther
	// and year)
	Book::Book(std::string title, std::string author, int year, std::string genre = "", int content = 0, int numPages = 0, int numChpt = 0, std::string checkedOut = "f");
    void setTitle(std::string);
    void setAuthor(std::string);
    void setGenre(std::string);
    void setContent(std::string);
    void setYear(int);
    void setPages(int);
    void setChpt(int);
	void setCheckedOut(std::string);
    
    std::string getTitle();
    std::string getAuthor();
    std::string getGenre();
    std::string getContent();
    int getYear();
    int getPages();
    //int getChpt();
};