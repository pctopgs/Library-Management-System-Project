#include "Book.h"
#include <vector>
#include <fstream>					// This is to use User files and Book files
#include <sstream>
#include <iomanip>

bool showMenu(std::vector<User>&, std::vector<Book>&, bool&, int&);
bool getChoice(int, std::vector<User>&, std::vector<Book>&, int&, bool&);		// The user needs to be passed by reference
void signIn(std::vector<User>&, int&, bool&);
void signUp(std::vector<User>&);
void signOut(std::vector<User>&, bool&);
void importFile(std::vector<User>&, std::vector<Book>&);
void addUser(std::vector<User>& u, int id, std::string un, std::string fn, std::string ln, std::string pw, std::string ut);
void exportUserFile(std::vector<User>);
void importBook(std::vector<Book>&, std::string bookNo, std::string t, std::string a, std::string g, int c, int y, int nc, int p, std::string co);
void listBooks(std::vector<Book>);
void addBook(std::vector<Book>&);
void exportBookFile(std::vector<Book>);
void searchBook(std::vector<Book>&, User, bool);
void viewBook(std::vector<Book>&, int, bool, User);
void deleteBook(std::vector<Book>&, int, bool, User);
void optionChoice(int, std::vector<Book>&, int, bool, User&);
void showOptions(std::vector<Book>&, int, bool, User&);
void editBook(std::vector<Book>&, int, bool, User);
void borrowBook(std::vector<Book>&, int, bool, User&);
void returnBook(std::vector<Book>&, int, bool, User&);

// Main Function
int main()
{
	std::vector<User> users;
	std::vector<Book> books;
	int index = -1;				
	bool loop = true;
	bool loggedIn = false;
	importFile(users, books);
	std::cout << "          Library Management System" << std::endl;
	do
	{
		loop = showMenu(users,books,loggedIn,index);
	} while (loop);
	return 0;
}

// Shows menu and gets a choice from the user
// Calls the get choice function
bool showMenu(std::vector<User>& userVect,std::vector<Book>& bookVect, bool& loggedIn, int& i)
{
	// Shows the main menu based on logged in state and the type of user. 
	// If the logged in state is false, the menu for Guest will be shown
	int choice;
	std::cout << "====================================" << std::endl;

	if (loggedIn)
	{
		std::cout << "Signed on as " << userVect[i].getUserName() << std::endl;
		if (userVect[i].getUserType() == "admin")
		{
			std::cout << "                   1. Browse Library" << std::endl;
			std::cout << "                   2. Search Books" << std::endl;
			std::cout << "                   3. Add Book" << std::endl;
			std::cout << "                   4. Add User" << std::endl;
			std::cout << "                   5. Sign Out" << std::endl;
			std::cout << "                   6. View Profile" << std::endl;
		}
		else if (userVect[i].getUserType() == "student")
		{
			std::cout << "                   1. Browse Library" << std::endl;
			std::cout << "                   2. Search Books" << std::endl;
			std::cout << "                   3. Checkout Book" << std::endl;
			std::cout << "                   4. Return Book" << std::endl;
			std::cout << "                   5. Edit Book" << std::endl;
			std::cout << "                   6. Sign Out" << std::endl;
			std::cout << "                   7. View Profile" << std::endl;
		}
	}
	else if (loggedIn == false)
	{
		std::cout << "Signed on as guest" << std::endl;
		std::cout << "                   1. Browse Library" << std::endl;
		std::cout << "                   2. Search Books" << std::endl;
		std::cout << "                   3. Sign In" << std::endl;
		std::cout << "                   4. Sign Up" << std::endl;
	}	
	else
	{
		std::cout << "Something went wrong. Please exit the program and open it again." << std::endl;
	}
	std::cout << "                   0. Exit" << std::endl;
	std::cout << "        Enter a choice: ";
	std::cin >> choice;

	return getChoice(choice, userVect, bookVect, i, loggedIn);
}

bool getChoice(int choice, std::vector<User>& u, std::vector<Book>& bookVect, int& i, bool& li)
{
	bool again = true;
	if (li)
	{
		if (u[i].getUserType() == "admin")
		{
			switch (choice)
			{
			case 1: listBooks(bookVect);
				break;
			case 2: searchBook(bookVect, u[i], li);
				break;
			case 3: addBook(bookVect);
				break;
			case 4:;
				break;
			case 5: signOut(u, li);
				break;
			case 6: signOut(u, li);
				break;
			case 0: exit(0);
				break;
			}
		}
		if (u[i].getUserType() == "student")
		{
			switch (choice)
			{
			case 1:listBooks(bookVect);
				break;
			case 2:;
				break;
			case 3:;
				break;
			case 4:;
				break;
			case 5:;
				break;
			case 6: signOut(u, li);
				break;
			case 0: exit(0);
				break;
			}
		}
	}
	
	else					// Guest
	{
		switch (choice)
		{
		case 1:listBooks(bookVect);
			break;
		case 2:searchBook(bookVect, u[i], li);
			break;
		case 3: signIn(u, i, li);			// Passes the User vector to the signIn() function
			break;
		case 4: signUp(u);			// Calls the signUp function. Passes the user vector to it
			break;
		case 5:;
			break;
		case 0: again = false; //exit(0);
			break;			
		}
	}	
	return again;
}

// This function takes the reference of user vectors and the reference of index
// And then changes the values if 
void signIn(std::vector<User>&u, int& index, bool& li)
{
	std::string name;
	std::string pass;
	int i = 0;
	bool keepSearching = true;
	bool found = false;
	bool signedIn = true;
	std::cout << "Username: ";
	std::cin >> name;
	if (keepSearching || !found)
	{
		for (i; i < u.size(); i++)
		{
			if (name == u[i].getUserName())
			{
				std::cout << "Password: ";
				std::cin >> pass;
				if (pass == u[i].getPassword())
				{
					std::cout << "\n\nWelcome " << u[i].getUserName() << std::endl;		// Welcomes the user
					index = i;			// When this function ends
					li = true;
				}
				found = true;
			}
		}
		keepSearching = false;
	}
	if (!keepSearching && !found)
	{
		std::cout << "\nUser not found: ";
		std::cout << std::endl;
	}
}

// This function will take the User vector as an argument
// It asks the user to enter a username
// If the username in the vector, 
// the function will tell the user that the username is already
// taken. Otherwise the function will ask the user
// for a password. Then the function will create a User object 
// with the username and password as parameters
void signUp(std::vector<User>& u)
{
	std::string name;
	std::string pass;
	int i = 0;
	bool keepSearching = true;
	bool found = false;
	std::cout << "New Username: ";
	std::cin >> name;
	if (keepSearching || !found)
	{
		for (i; i < u.size(); i++)
		{
			if (name == u[i].getUserName())
			{
				std::cout << "\nThat username already exists." << std::endl;
				found = true;
			}
		}
		keepSearching = false;
	}
	if (!keepSearching && !found)
	{
		std::cout << "\nCreate a password: ";
		std::cin >> pass;
		std::cout << std::endl;
		User tempU(u.size(),name, pass);
		u.push_back(tempU);
		exportUserFile(u);
	}
}

void importFile(std::vector<User>& u, std::vector<Book>& b)
{
	std::string tempLine;
	std::string parseLine;
	std::vector<std::string> attribute;
	std::ifstream inFile("userDB.txt");				// imports the user file
	if (!inFile)
	{
		u.push_back(User{500});
		std::cout << "No User data found" << std::endl;
		std::cout << "Creating new user data base.\n\n" << std::endl;
		std::ofstream tempOut("userDB.txt");
		tempOut.close();
		exportUserFile(u);
	}
	// Parsing the file and adding it to the User vector
	while (std::getline(inFile, tempLine))		// Get the line
	{
		std::stringstream streamLine(tempLine);		
		while(std::getline(streamLine, parseLine, ','))	// Get a string from the line separated by commas
		{
			attribute.push_back(parseLine);			// Add the parsed line to a string vector
		}
		addUser(u, stoi(attribute[0]), attribute[1], attribute[2], attribute[3], attribute[4], attribute[5]);
		attribute.clear();
	}
	inFile.close();
	// Getting the books data base file
	inFile.open("bookDB.txt");
	if (!inFile)
	{
		std::cout << "No book data base found" << std::endl;
		std::cout << "Creating new user data base.\n\n" << std::endl;
		std::ofstream tempOut("bookDB.txt");
	}
	// Parse the books file into the program
	while (std::getline(inFile, tempLine))
	{
		std::stringstream streamLine(tempLine);
		while (std::getline(streamLine, parseLine, ','))
		{
			attribute.push_back(parseLine);
		}
		//addBook(stoi(attribute[0]), attribute[1], attribute[2], attribute[3], attribute[4], attribute[5], attribute[6], attribute[7], attribute[8], attribute[9);
		importBook(b, attribute[0], attribute[1], attribute[2], attribute[3], stoi(attribute[4]), stoi(attribute[5]), stoi(attribute[6]), stoi(attribute[7]), attribute[8]);
		attribute.clear();
	}
}

void exportUserFile(std::vector<User> userVect)
{
	std::ofstream outFile;
	outFile.open("userDB.txt");
	for (int i = 0; i <userVect.size(); i++)
	{
		outFile << userVect[i].getUID() << "," << userVect[i].getUserName() << "," << userVect[i].getFirstN() << "," << userVect[i].getLastN() << "," << userVect[i].getPassword() << "," << userVect[i].getUserType() << std::endl;
	}
	outFile.close();
}

// This is used with importFiles() to append members to the User vector at the beginning of the program
void addUser(std::vector<User>& u, int id, std::string un, std::string fn, std::string ln, std::string pw, std::string ut)
{
	User tempU(id, un, fn, ln, pw, ut);
	u.push_back(tempU);
}

// This will simply change the bool li to false so 
// when the emain functions do/while loop calls the showMenu function, 
// The li will be false and show the menu for Guest
void signOut(std::vector<User>& u, bool& li)
{
	li = false;			
}

void listBooks(std::vector<Book> b)
{
	if (b.size() == 0)
	{
		std::cout << "There are no books to display." << std::endl;
	}
	else
	{
		// Display the Headings
		std::cout << "\nBook Number " << " Title" << " Author" << " Genre" << " Content" << " Year" << std::endl;
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		for (int i = 0; i < b.size(); i++)
		{
			std::cout << b[i].getTitle() << " " << b[i].getAuthor() << " " << b[i].getYear() << " " << std::endl;
		}
	}
}

// This is an admin only function that is used to add books to the data base
// The minimum amount of infomration needed is title, the rest of the info can
// be added/modified with editBook(). The book number and checked out info will be automatically generated.
// maybe hold the information for the required data in an array, and 
void addBook(std::vector<Book>&bookVect)
{	
	// declare the variables (title, author, year, genre)
	std::string title;
	std::string author;
	int year;
	
	// Get a title (std::string). if the string is empty, tell the user that a title is required
	//std::getline(std::cin, catcher);
	std::cout << "new Title: ";
	std::getline(std::cin, title);
	std::getline(std::cin, title);
	// Get an Author (std::string). if the string is empty, tell the user that an author is required
	std::cout << "Author name: ";
	std::getline(std::cin, author);
	
	// Get a year (int). if the int is empty, tell the user that a year is required
	std::cout << "Year published: ";
	std::cin >> year;

	Book tempBook(title, author, year);
	bookVect.push_back(tempBook);
	exportBookFile(bookVect);
}

// This function will take the value of the book vector and 
// export it to the bookDB.txt file.

void exportBookFile(std::vector<Book> bookVect)
{
	std::ofstream outFile("bookDB.txt");

	for (int i = 0; i < bookVect.size(); i++)
	{
		outFile << bookVect[i].getBookNo() << "," << bookVect[i].getTitle() << "," << bookVect[i].getAuthor() << "," << bookVect[i].getGenre() << "," << bookVect[i].getChpt() << "," << bookVect[i].getYear() << "," << bookVect[i].getPages() << "," << bookVect[i].getChpt() << "," << bookVect[i].getCheckedOut() << std::endl;
	}
}

// This function is used to add books from the CSV file
void importBook(std::vector<Book>& bookVect, std::string bookNo, std::string title, std::string author, std::string genre, int c, int y, int nc, int p, std::string co)
{
	Book tempB(bookNo, title, author, genre, c, y, nc, p, co);
	bookVect.push_back(tempB);
}

// This function will list the attributes for the book and asks the user
// to enter a number that corresponds to the attribute they want to edit
void editBook(std::vector<Book>& bookVect, int book, bool loggedIn, User user)
{
	int choice;
	std::string choiceStr;
	std::string newEntry;
	std::cout << "\nUnable to edit books right now. This feature isn't ready\n\n";
	// list the options that can be changed
	std::cout << "             BOOK EDITOR" << std::endl;
	std::cout << "Select an attribute to change:" << std::endl;
	std::cout << "1. Title     2. Author     3. Year Published" << std::endl;
	std::cout << "4. Genre     5. Content    6. Description" << std::endl;
	std::cout << "0. Cancel" << std::endl;
	std::cout << "\nOption: ";
	std::getline(std::cin, choiceStr);
	choice = stoi(choiceStr);

	// Handle the choice made by user
	if (choice == 1)
	{
		// Edit Title
		std::cout << "The current title is: " << bookVect[book].getTitle();
		std::cout << "\nEnter a new title: ";
		std::getline(std::cin, newEntry);
		bookVect[book].setTitle(newEntry);
		exportBookFile(bookVect);
	}
	else if (choice == 2)
	{
		// Edit Author
		std::cout << "The current author for " << bookVect[book].getTitle() << " is: " << bookVect[book].getAuthor();
		std::cout << "\nEnter a new author: ";
		std::getline(std::cin, newEntry);
		bookVect[book].setAuthor(newEntry);
		exportBookFile(bookVect);
	}
	else if (choice == 3)
	{
		// Edit Year
		std::cout << "The current year published for " << bookVect[book].getTitle() << " is: " << bookVect[book].getYear();
		std::cout << "\nEnter a new year: ";
		std::getline(std::cin, newEntry);
		int numEntry = stoi(newEntry);
		bookVect[book].setYear(numEntry);
		exportBookFile(bookVect);
	}
	else if (choice == 4)
	{
		// Edit Genre
		std::cout << "The current genre for " << bookVect[book].getTitle() << " is: " << bookVect[book].getGenre();
		std::cout << "\nEnter a new genre: ";
		std::getline(std::cin, newEntry);
		bookVect[book].setGenre(newEntry);
		exportBookFile(bookVect);
	}
	else if (choice == 5)
	{
		// Edit Content
		std::cout << "The current content for " << bookVect[book].getTitle() << " is: " << bookVect[book].getContent();
		std::cout << "\nEnter a new type of content: ";
		std::getline(std::cin, newEntry);
		bookVect[book].setContent(newEntry);
		exportBookFile(bookVect);
	}
	else if (choice == 6)
	{
		// Edit Description
		std::cout << "The current description for " << bookVect[book].getTitle() << " is: " << bookVect[book].getDesc();
		std::cout << "\nEnter a different description for this book: ";
		std::getline(std::cin, newEntry);
		bookVect[book].setDesc(newEntry);
		exportBookFile(bookVect);
	}
}

void searchBook(std::vector<Book>& bookVect, User user, bool loggedIn)
{
	std::string searchName;
	//int searchCount;			// Keeps track of the number of 
	std::cout << "\nThis feature is in beta right now...." << std::endl;
	std::cout << "Enter a book name: ";
	//std::cin >> searchName;
	std::getline(std::cin, searchName);
	std::getline(std::cin, searchName);

	for (int i = 0; i < bookVect.size(); i++)
	{
		if (searchName == bookVect[i].getTitle())
		{
			viewBook(bookVect, i, loggedIn, user);		// TODO
		}
	}
}

// This function will show information about the book
// title heading, Short desrcription, and some menu options at the bottom depending on the userType:
// Borrow, Edit, Main Menu
void viewBook(std::vector<Book>& bookVect, int book, bool loggedIn, User user)
{
	// TODO
	std::cout << "--This feature is still in beta--\n";
	std::cout << "\n\n           " << bookVect[book].getTitle() << std::endl;
	std::cout << bookVect[book].getAuthor() << "               " << bookVect[book].getYear() << std::endl;
	std::cout << "-------------------------------" << std::endl;
	std::cout << bookVect[book].getDesc() << std::endl;
	showOptions(bookVect, book, loggedIn, user);  // TODO
}

// This function will allow a user to borrow a book
// only if loggedIn is true, user type is 'student'
// user does not already have a book checked out,
// and book is not already checked out
void borrowBook(std::vector<Book>& bookVect, int book, bool loggedIn, User& user)
{
	// TODO
	std::cout << "Can't borrow books yet. This feature isn't ready.\n\n" << std::endl;
}

void returnBook(std::vector<Book>& bookVect, int book, bool loggedIn, User& user)
{
	;
}

// This is an entirly new menu that shows the options a user can do with a book
// it lists out the options and then calls another function to handle the choice
// made by the user.
void showOptions(std::vector<Book>& bookVect, int book, bool loggedIn, User& user)
{
	int choice;
	std::string choiceStr;
	//std::cout << "No options yet\n\n";
	// Options depending on userType: borrow, return, delete, edit, back
	std::cout << "1. Borrow         2. Return         3. Edit        4. Delete\n\n";
	std::cout << "Enter a choice: ";
	std::getline(std::cin, choiceStr);
	choice = stoi(choiceStr);
	optionChoice(choice, bookVect, book, loggedIn, user);		// TODO:
}

// This function will take the choice, the book, the logged in state, and the user and call other functions based on the choice
void optionChoice(int choice, std::vector<Book>& bookVect, int book, bool loggedIn, User& user)
{
	switch (choice)
	{
	case 1: borrowBook(bookVect, book, loggedIn, user);
		break;
	case 2: returnBook(bookVect, book, loggedIn, user);
		break;
	case 3: editBook(bookVect, book, loggedIn, user);
		break;
	case 4: deleteBook(bookVect, book, loggedIn, user);
		break;
	}
}

void deleteBook(std::vector<Book>& bookVect, int book, bool loggedIn, User user)
{
	std::cout << "Can't quite delete books yet....." << std::endl;
	// TODO
}