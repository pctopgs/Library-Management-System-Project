#include "User.h"

class Book
{
	std::string bookNo;
    std::string title;
    std::string author;
    std::string genre;
    std::string content;
	std::string desc;			// A short description of the book (about 1 sentence for now)
    int year;
    int numChpt;
	int pages;
	bool checkedOut;

    public:
	Book(std::string bookNo, std::string t, std::string a, std::string g, int c, int y, int nc, int p, std::string co);
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
	void setBookNo(std::string);				// Used for if the book is being imported from file
	void setNewBookNo(std::string, std::string, int);
	void setDesc(std::string);
    
    std::string getTitle();
    std::string getAuthor();
    std::string getGenre();
    std::string getContent();
    int getYear();
    int getPages();
	std::string getBookNo();
	bool getCheckedOut();
    int getChpt();
	std::string getDesc();
};