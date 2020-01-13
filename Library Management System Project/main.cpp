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
void addUser(std::vector<User>& u, int id, std::string un, std::string fn, std::string ln, std::string pw, int bn, std::string ut);
void exportUserFile(std::vector<User>);
void importBook(std::vector<Book>&, int bookNo, std::string t, std::string a, std::string g, int c, int y, int nc, int p, std::string co);
void showHeading();
void addBook(std::vector<Book>&);
void exportBookFile(std::vector<Book>&);
void searchBook(std::vector<Book>&, bool, User user = User(300));
void viewBook(std::vector<Book>&, int, bool, User&);
void deleteBook(std::vector<Book>&, int, bool, User);
void optionChoice(int, std::vector<Book>&, int, bool, User&);
void showBookOptions(std::vector<Book>&, int, bool, User&);
void editBook(std::vector<Book>&, int, bool, User);
void borrowBook(std::vector<Book>&, int, bool, User&);
void returnBook(std::vector<Book>&, bool, User&);
void listBook(std::vector<Book>, int);
void browseBooks(std::vector<Book>& bookVect, bool loggedIn, User& user = User(300), int book = 0);
void viewProfile(std::vector<User>&, int, User&);
void editProfile(User& targetUser, User actingUser);

// Main Function
int main()
{
	std::vector<User> users;
	std::vector<Book> books;
	int index = -1;				
	bool loop = true;
	bool loggedIn = false;
	importFile(users, books);

	// Testing pointer to class
	/*
	Book sacredBook(1,"Bible", "Prophets", 486);
	Book* pSacredBook = &sacredBook;		// setting the memory address of secredBook to pSacredBook
	int Book::*memberPointer;
	//sacredBook.*memberPointer;

	*pSacredBook.*memberPointer;
	



	std::cout << sacredBook.getTitle() << " " << pSacredBook->getTitle() << std::endl;
	auto buck = 100;
	*/

	std::cout << "          Library Management System" << std::endl;
	do
	{
		loop = showMenu(users,books,loggedIn,index);
		exportUserFile(users);
		std::cout << "\n\n";
	} while (loop);
	return 0;
	
}

// Shows menu and gets a choice from the user
// Calls the get choice function
bool showMenu(std::vector<User>& userVect,std::vector<Book>& bookVect, bool& loggedIn, int& i)
{
	// Shows the main menu based on logged in state and the type of user. 
	// If the logged in state is false, the menu for Guest will be shown
	//std::string choice;
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
			std::cout << "                   4. View Users" << std::endl;
			std::cout << "                   5. Sign Out" << std::endl;
			std::cout << "                   6. View Profile (beta)" << std::endl;
		}
		else if (userVect[i].getUserType() == "student")
		{
			std::cout << "                   1. Browse Library" << std::endl;
			std::cout << "                   2. Search Books" << std::endl;
			std::cout << "                   3. Return Book" << std::endl;
			std::cout << "                   4. Sign Out" << std::endl;
			std::cout << "                   5. View Profile (beta)" << std::endl;
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

bool getChoice(int choice, std::vector<User>& userVect, std::vector<Book>& bookVect, int& userIndex, bool& li)
{
	bool again = true;
	if (li)
	{
		if (userVect[userIndex].getUserType() == "admin")
		{
			switch (choice)
			{
			case 1: browseBooks(bookVect, li, userVect[userIndex]);
				break;
			case 2: searchBook(bookVect, li, userVect[userIndex]);
				break;
			case 3: addBook(bookVect);
				break;
			case 4: signOut(userVect, li);
				break;
			case 5: viewProfile(userVect, userVect[userIndex].getUID(), userVect[userIndex]);
			case 0: again = false;
				break;
			}
		}
		if (userVect[userIndex].getUserType() == "student")
		{
			switch (choice)
			{
			case 1: browseBooks(bookVect, li, userVect[userIndex]);
				break;
			case 2: searchBook(bookVect, li, userVect[userIndex]);;
				break;
			case 3: returnBook(bookVect, li, userVect[userIndex]);
				break;
			case 4: signOut(userVect, li);
				break;
			case 5: viewProfile(userVect, userVect[userIndex].getUID(), userVect[userIndex]);
				break;
			case 0: again = false;
				break;
			}
		}
	}
	
	else					// Guest
	{
		switch (choice)
		{
		case 1:browseBooks(bookVect, li); 
			break;
		case 2:searchBook(bookVect, li);
			break;
		case 3: signIn(userVect, userIndex, li);			// Passes the User vector to the signIn() function
			break;
		case 4: signUp(userVect);			// Calls the signUp function. Passes the user vector to it
			break;
		case 0: again = false;
			break;			
		}
	}	
	return again;
}

// This function takes the reference of user vectors and the reference of index
// And then changes the values if 
void signIn(std::vector<User>& userVect, int& index, bool& isLoggedIn)
{
	std::string userNameSearchKey;
	std::string pass;
	int i = 0;
	int passwordRetry = 0;
	int userRetry = 0;
	bool keepSearching = true;
	bool userFound = false;
	
	while (!userFound && userRetry < 3 && userNameSearchKey != "b")
	{
		std::cout << "\nEnter a username, or 'b' to go back" << std::endl;
		std::cout << "Username: ";
		std::cin >> userNameSearchKey;
		for (i; i < userVect.size(); i++)
		{
			if (userNameSearchKey == userVect[i].getUserName())
			{
				userFound = true;
				while (!isLoggedIn && passwordRetry < 3)
				{
					std::cout << "Password: ";
					std::cin >> pass;
					if (pass == userVect[i].getPassword())
					{
						std::cout << "\nWelcome " << userVect[i].getUserName() << std::endl;		// Welcomes the user
						index = i;			// When this function ends
						isLoggedIn = true;
					}
					else
					{
						std::cout << "\nIncorrect password. Try again.\n";
						passwordRetry++;			// Increment the number of retries the user has done
					}
				}			
			}
		}

		if (!userFound && userNameSearchKey != "b")
		{
			std::cout << "\nUser not found.\n";
			userRetry++;
		}
		if (userRetry >= 3)
		{
			std::cout << "Too many incorrect attempts." << std::endl;
		}
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
	std::string password;
	std::string confirmPassword;
	int passwordRetry = 0;
	int i = 0;
	bool passwordsMatch = false;	
	bool keepSearching = true;
	bool userFound = false;

	std::cout << "New Username: ";
	std::cin >> name;

	// TODO: Implement a general search function for the program
	for (i; i < u.size() && !userFound; i++)
	{
		if (name == u[i].getUserName())
		{
			std::cout << "\nThat username already exists." << std::endl;
			userFound = true;
		}
	}

	while (!userFound && passwordRetry <= 2 && !passwordsMatch)
	{
		std::cout << std::endl;
		std::cout << "Create a password: ";
		std::cin >> password;
		std::cout << "\nConfirm password: ";
		std::cin >> confirmPassword;
		if (password != confirmPassword)
		{
			std::cout << "\nPasswords do not match. Enter your password again." << std::endl;
			passwordRetry++;
		}
		else
		{
			User tempU(u.size(), name, password);
			u.push_back(tempU);
			exportUserFile(u);
			passwordsMatch = true;
		}				
	}
}

void importFile(std::vector<User>& u, std::vector<Book>& b)
{
	std::string tempLine;
	std::string parseLine;
	std::vector<std::string> attribute;
	std::ifstream inFile("userDB.tsv");				// imports the user file
	if (!inFile)
	{
		u.push_back(User{500});
		std::cout << "No User data base file found" << std::endl;
		std::cout << "Creating a new user data base file.\n\n" << std::endl;
		std::ofstream tempOut("userDB.txt");
		tempOut.close();
		exportUserFile(u);
	}
	// Parsing the file and adding it to the User vector
	while (std::getline(inFile, tempLine))		// Get the line
	{
		std::stringstream streamLine(tempLine);
		//while(std::getline(streamLine, parseLine, ','))	// Get a string from the line separated by commas
		while (std::getline(streamLine, parseLine, '\t'))	// Get a string from the line separated by tabs
		{
			attribute.push_back(parseLine);			// Add the parsed line to a string vector
			//std::cout << parseLine << std::endl;
		}
		addUser(u, stoi(attribute[0]), attribute[1], attribute[2], attribute[3], attribute[4], stoi(attribute[5]), attribute[6]);
		attribute.clear();
	}
	inFile.close();
	// Getting the books data base file
	inFile.open("bookDB.tsv");
	if (!inFile)
	{
		std::cout << "No book data base found" << std::endl;
		std::cout << "Creating new user data base.\n\n" << std::endl;
		std::ofstream tempOut("bookDB.tsv");
	}
	// Parse the books file into the program
	while (std::getline(inFile, tempLine))
	{
		std::stringstream streamLine(tempLine);
		while (std::getline(streamLine, parseLine, '\t'))
		{
			attribute.push_back(parseLine);
		}
		importBook(b, stoi(attribute[0]), attribute[1], attribute[2], attribute[3], stoi(attribute[4]), stoi(attribute[5]), stoi(attribute[6]), stoi(attribute[7]), attribute[8]);
		attribute.clear();
	}
}

// This is used with importFiles() to append members to the User vector at the beginning of the program
void addUser(std::vector<User>& u, int id, std::string un, std::string fn, std::string ln, std::string pw, int bn, std::string ut)
{
	User tempU(id, un, fn, ln, pw, bn, ut);
	u.push_back(tempU);
}

void exportUserFile(std::vector<User> userVect)
{
	std::ofstream outFile;
	outFile.open("userDB.tsv");
	for (int i = 0; i <userVect.size(); i++)
	{
		outFile << userVect[i].getUID() << "\t" << userVect[i].getUserName() << "\t" << userVect[i].getFirstN() << "\t" << userVect[i].getLastN() << "\t" << userVect[i].getPassword() << "\t" << userVect[i].getBookNo() << "\t" << userVect[i].getUserType() << std::endl;
	}
	outFile.close();
}


// This will simply change the bool li to false so 
// when the emain functions do/while loop calls the showMenu function, 
// The li will be false and show the menu for Guest
void signOut(std::vector<User>& u, bool& li)
{
	li = false;			
}

void showHeading()
{	
	std::cout << "\n" << std::setw(15) << std::left << "Book Number" << std::setw(43) << std::left << "Title" << std::setw(23) << std::left << "Author" << std::setw(20) << std::left << "Genre" << std::setw(10) << std::left << "Content" << std::setw(10) << std::left << "Year" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
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

	Book tempBook(bookVect.size(),title, author, year);
	bookVect.push_back(tempBook);
	exportBookFile(bookVect);
}

// This function will take the value of the book vector and 
// export it to the bookDB.txt file.
void exportBookFile(std::vector<Book>& bookVect)
{
	std::ofstream outFile("bookDB.tsv");

	for (int i = 0; i < bookVect.size(); i++)
	{
		outFile << bookVect[i].getBookNo() << "\t" << bookVect[i].getTitle() << "\t" << bookVect[i].getAuthor() << "\t" << bookVect[i].getGenre() << "\t" << bookVect[i].getChpt() << "\t" << bookVect[i].getYear() << "\t" << bookVect[i].getPages() << "\t" << bookVect[i].getChpt() << "\t" << bookVect[i].getCheckedOut() << std::endl;
	}
}

// This function is used to add books from the CSV file
void importBook(std::vector<Book>& bookVect, int bookNo, std::string title, std::string author, std::string genre, int c, int y, int nc, int p, std::string co)
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
	// list the options that can be changed
	std::cout << "             BOOK EDITOR {BETA}" << std::endl;
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



// This function will allow a user to borrow a book
// only if loggedIn is true, user type is 'student'
// user does not already have a book checked out,
// and book is not already checked out
void borrowBook(std::vector<Book>& bookVect, int book, bool loggedIn, User& user)
{
	// Borrow book works for now
	if (user.getBookNo() == 0)		// Checks to see if user already has a book checked out
	{
		// Will need to optimize this better to combine the two if conditions in one line
		std::cout << "\n\nCOOL!!\n\n";
		std::cout << bookVect[book].getCheckedOut() << std::endl;
		if (bookVect[book].getCheckedOut() == "f")
		{
			user.setBookNo(bookVect[book].getBookNo());
			bookVect[book].setCheckedOut("t");
			std::cout << "\nYou borrowed \"" << bookVect[book].getTitle() << "\". Happy reading!\n";
			exportBookFile(bookVect);
		}
	}
}

void returnBook(std::vector<Book>& bookVect, bool loggedIn, User& user)
{
	// if the bookNo in the user matches book in bookVect
	// Then change the checkedOut variable in the book to f
	// change the bookNo in the the user to 0
	int beginning = 0;
	int end = bookVect.size() - 1;
	bool found = false;

	// TODO: COMPLETE BINARY SEARCH
	while(beginning < end && found == false)
	{
		if (user.getBookNo() == bookVect[end / 2].getBookNo())
		{
			found = true;
			bookVect[end / 2].setCheckedOut("f");
			user.setBookNo(0);
			exportBookFile(bookVect);
			std::cout << "\nYou returned \"" << bookVect[end / 2].getTitle() << "\"" << std::endl;
			std::cout << "Thank you!" << std::endl;
		}
		else if (user.getBookNo() < bookVect[end / 2].getBookNo())
		{
			end = end / 2;
		}
		else if (user.getBookNo() > bookVect[end / 2].getBookNo())
		{
			beginning = end / 2;
		}
	}
}

// This is an entirly new menu that shows the options a user can do with a book
// it lists out the options and then calls another function to handle the choice
// made by the user.
void showBookOptions(std::vector<Book>& bookVect, int book, bool loggedIn, User& user)
{
	int choice;
	std::string choiceStr;
	std::cout << "1. Borrow         2. Return         3. Edit        4. Delete";
	std::cout << "\n5. Go Back\n";
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
	case 2: returnBook(bookVect, loggedIn, user);
		break;
	case 3: editBook(bookVect, book, loggedIn, user);
		break;
	case 4: deleteBook(bookVect, book, loggedIn, user);
		break;
	case 5:;		// Go back
		break;
	}
}

void deleteBook(std::vector<Book>& bookVect, int book, bool loggedIn, User user)
{
	std::cout << "Can't quite delete books yet....." << std::endl;
	// TODO
}

void browseBooks(std::vector<Book>& bookVect, bool loggedIn, User& user, int book)
{
	std::string searchKey;
	std::getline(std::cin, searchKey);
	do
	{		
		bool bookFound = false;
		//std::string searchKey;
		book = 0;
		std::cout << "\nEnter the book number of the book you'd like to view, or 'b' to go back to the main menu\n";
		showHeading();
		for (int i = 0; i < bookVect.size(); i++)
		{
			listBook(bookVect, i);
		}
		std::cout << "\nBook Number: ";
		std::getline(std::cin, searchKey);
		//std::getline(std::cin, searchKey);
		if (searchKey != "b")
		{
			for (int i = 0; i < bookVect.size() && !bookFound; i++)
			{
				if (stoi(searchKey) == bookVect[i].getBookNo())
				{
					viewBook(bookVect, i, loggedIn, user);
					bookFound = true;
				}
			}
		}		
	} while (searchKey != "b");
}

void searchBook(std::vector<Book>& bookVect, bool loggedIn, User user)
{
	std::string searchTerm;
	std::string getChoice;
	bool found = false;	
	std::cout << "\nThis feature is in beta right now...." << std::endl;
	std::cout << "Enter a book name: ";
	std::getline(std::cin, searchTerm);
	std::getline(std::cin, searchTerm);

	do
	{
		bool bookFound = false;
		showHeading();
		for (int book = 0; book < bookVect.size(); book++)
		{
			if (searchTerm == bookVect[book].getTitle())
			{
				found = true;
				listBook(bookVect, book);  // List each book 
			}
		}

		std::cout << "Enter the book number of the book you'd like to view ('b' to go back to the main menu): ";
		std::getline(std::cin, getChoice);
		if (getChoice != "b")
		{
			for (int book = 0; book < bookVect.size() && !bookFound; book++)
			{
				if (stoi(getChoice) == bookVect[book].getBookNo())
				{
					viewBook(bookVect, book, loggedIn, user);
					bookFound = true;
				}
			}
		}		
	} while (getChoice != "b");			// This is to go back to the search results after the user has viewed a book 	
}

void listBook(std::vector<Book> bookVect, int book)
{
	std::cout << std::setw(15) << std::left << bookVect[book].getBookNo() << std::setw(43) << std::left << bookVect[book].getTitle() << std::setw(23) << std::left << bookVect[book].getAuthor() << std::setw(20) << std::left << bookVect[book].getGenre() << std::setw(10) << bookVect[book].getContent() << std::setw(10) << std::left << bookVect[book].getYear() << std::setw(15) << std::endl;
}

// This function will show information about the book
// title heading, Short desrcription, and some menu options at the bottom depending on the userType:
// Borrow, Edit, Main Menu
void viewBook(std::vector<Book>& bookVect, int book, bool loggedIn, User& user)
{
	std::cout << "--This feature is still in beta--\n";
	std::cout << "\n\n           " << bookVect[book].getTitle() << std::endl;
	std::cout << bookVect[book].getAuthor() << "               " << bookVect[book].getYear() << std::endl;
	std::cout << "-------------------------------" << std::endl;
	std::cout << bookVect[book].getDesc() << std::endl;
	showBookOptions(bookVect, book, loggedIn, user);
}

// This function will allow the user to view and edit his/her profile. Similar to the view book function
void viewProfile(std::vector<User>& userVect, int userID, User& user)
{
	std::cout << "\n\n--This feature is still in beta--" << std::endl;
	int userIndex;
	userIndex = 0;
	bool stop = false;
	for (userIndex; userIndex < userVect.size() || stop == false; userIndex++)
	{
		if (userID == userVect[userIndex].getUID())
		{
			std::cout << "Index      : " << userIndex << std::endl;
			std::cout << "ID         : " << userVect[userIndex].getUID() << std::endl;
			std::cout << "Username   : " << userVect[userIndex].getUserName() << std::endl;
			std::cout << "First Name : " << userVect[userIndex].getFirstN() << std::endl;
			std::cout << "Last Name  : " << userVect[userIndex].getLastN() << std::endl;
			std::cout << "userType   : " << userVect[userIndex].getUserType() << std::endl;
			std::cout << "Book       : " << userVect[userIndex].getBookNo() << std::endl;
			stop = true;
		}
	}
	
	int choice;
	std::cout << "\n1. Edit Profile" << std::endl;
	std::cout << "2. Go Back" << std::endl;
	std::cout << "-Enter a choice-\n" << std::endl;
	std::cin >> choice;
	// TODO: Implement the menu for the profile
	switch (choice)
	{
	case 1: editProfile(userVect[userIndex], user);
		break;
	case 2:;
		break;
	}
}

void editProfile(User& targetUser, User actingUser)
{
	// targetUser is the user that will be edited, while actingUser is the user that is doing the editing
	std::cout << "\n_-Edit Profile is in beta-_\n" << std::endl;
	std::cout << "1. First Name : " << targetUser.getFirstN() << std::endl;
	std::cout << "2. Last Name  : " << targetUser.getLastN() << std::endl;
	std::cout << "3. User Type  : " << targetUser.getUserType() << std::endl;
}