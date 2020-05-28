#include "User.h"
#include "Author.h"
#include <vector>

class Book
{
	int bookNo;
    //std::string title;			
	std::vector<std::string> title;
    std::string genre;
    std::string content;
	std::string desc;			// A short description of the book (about 1 sentence for now)
    int year;
    int numChpt;
	int pages;
	static int numberOfBooks;
	bool checkedOut;			// Whether or not the book has been checked out	
    int authorID;

    public:
	// This contructor is called when importing books from the bookDB file
	Book(int bookNo, std::string, std::string, std::string, int, int, int, int, int, int);

	// Used in conjunction with addBook to add a new book
	// (all attributes will have default values except title, auther
	// and year)
	//Book::Book(int,std::string title, std::string author, int year, std::string genre = "", int content = 0, int numPages = 0, int numChpt = 0, int checkedOut = 0);
	//Book::Book(int, std::string title, int authID, int year, std::string genre = "", int content = 0, int numPages = 0, int numChpt = 0, int checkedOut = 0);
	Book(int numberOfBooks, std::string title, int authID, int year, int checkedOut = false);

	// Destructor
	~Book()
	{
		//std::cout << this->title << " was removed from the libary" << std::endl;
	}
    void setTitle(std::string);
	void Book::setTitleParsed(std::string aTitle);		// New
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
    
    //std::string getTitle();
	std::string getTitle();
    std::string getAuthor();
    std::string getGenre();
    std::string getContent();
    int getYear();
    int getPages();
	int getBookNo();
	
    int getChpt();
	std::string getDesc();
	void showThis();

	//bool operator <(Book book);

	int getAuthorID();

	// External functions

	friend std::ostream &operator<<(std::ostream& out, Book bookObjbookObj);
};
