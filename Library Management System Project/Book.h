#include "User.h"
#include "Author.h"

class Book
{
	int bookNo;
    std::string title;			
    std::string author;
    std::string genre;
    std::string content;
	std::string desc;			
    int year;
    int numChpt;
	int pages;
	static int numBooks;
	bool checkedOut;			// Whether or not the book has been checked out	
    int authorID;

    public:
	// This contructor is called when importing books from the bookDB file
	Book(int bookNo, std::string, std::string, std::string, int, int, int, int, int, int);

	// Used in conjunction with addBook to add a new book
	// (all attributes will have default values except title, auther
	// and year)
	Book::Book(int numBooks, std::string title, int authID, int year, int checkedOut = false);
    void setTitle(std::string);
    void setAuthor(std::string);
    void setGenre(std::string);
    void setContent(std::string);
	bool getCheckedOut();
    void setYear(int);
    void setPages(int);
    void setChpt(int);
	void setCheckedOut(int);
	void setBookNo(int);				// Used for if the book is being imported from file
	void setNewBookNo(int);
	void setDesc(std::string);
	void setAuthorID(int);
    
    std::string getTitle();
    std::string getAuthor();
    std::string getGenre();
    std::string getContent();
	std::string getDesc();
    int getYear();
    int getPages();
	int getBookNo();
	int getAuthorID();	
    int getChpt();

	bool operator <(Book book);


};