#include "Book.h"
#include "Author.h"
#include <vector>
#include <fstream>					// This is to use User files and Book files
#include <sstream>
#include <iomanip>

bool showMainMenu(std::vector<User>&, std::vector<Book>&, std::vector<Author>, User *currentLoggedInUser, int&);
bool getChoice(int choice, std::vector<User>& userVect, std::vector<Book>& bookVect, std::vector<Author>& authorVect, User* currentLoggedInUser);
void importFiles(std::vector<User>&, std::vector<Book>&, std::vector<Author>&);
void exportUserFile(std::vector<User>);
void exportBookFile(std::vector<Book>&);

// User functions
void signIn(std::vector<User>&, /*int&,*/ User *currentLoggedInUser);
void signUp(std::vector<User>&);
void signOut(/*std::vector<User>&,*/ User *currentLoggedInUser);
void addUser(std::vector<User>& u, int id, std::string un, std::string fn, std::string ln, std::string pw, int bn, std::string ut);
//void viewProfile(std::vector<User>&, std::vector<Book>, int, User&);
void viewProfile(std::vector<User>& userVect, std::vector<Book> bookVect, int userID, User& user, User* currentLoggedInUser);
void editProfile(User& targetUser, User actingUser);
void browseUsers(std::vector<User>& userVect, User* currentLoggedInUser);

// Book functions
void importBook(std::vector<Book>&, int bookNo, std::string t, std::string a, std::string g, int c, int y, int nc, int p, std::string co, int authorID = 0000000);
void addBook(std::vector<Book>&, std::vector<Author>);
void searchBook(std::vector<Book>& bookVect, std::vector<Author>& authorVect, User* currentLoggedInUser);
void viewBook(std::vector<Book>&, std::vector<Author>&, int, User&);
void showBookHeading();
void bookOptionChoice(std::string, std::vector<Book>&, std::vector<Author>&, int, User&);
void showBookOptions(std::vector<Book>&, std::vector<Author>&, int, User&);
void editBook(std::vector<Book>&, std::vector<Author>&, int, User currentLoggedInUser, User);
void borrowBook(std::vector<Book>&, int, User&);
//void browseBooks(std::vector<Book>& bookVect, std::vector<Author>&, bool loggedIn, User& user = User("guest"), int book = 0);
void browseBooks(std::vector<Book>& bookVect, std::vector<Author>& authorVect, User* currentLoggedInUser);
void returnBook(std::vector<Book>& bookVect, User* currentLoggedInUser);
void listBook(std::vector<Book>, int);
void deleteBook(std::vector<Book>&, int, User);

// Author functions
void addAuthor(std::vector<Author> &);		// This function will add a new author to the
void importAuthor(std::vector<Author> &authorVect, int, std::string firstName, std::string lastName, std::string penName = " ");
void listAuthor(std::vector<Author> &authorVect, int index);
void browseAuthor(std::vector<Author>&);

// Operator overloads
// Operator<<

std::ostream& operator<<(std::ostream & out, Book book)
	{
		//out << bookObj.getTitle();
		out << std::setw(15) << std::left << book.getBookNo() << std::setw(43) << std::left << book.getTitle() << std::setw(23) << std::left << book.getAuthor() << std::setw(20) << std::left << book.getGenre() << std::setw(10) << book.getContent() << std::setw(10) << std::left << book.getYear() << book.getAuthorID() << std::setw(15) << std::endl;
		return out;
	}

std::ostream& operator<<(std::ostream& out, User user)
{
	out << user.getUserName();
	//out << std::setw(15) << std::left << bookVect[book].getBookNo() << std::setw(43) << std::left << bookVect[book].getTitle() << std::setw(23) << std::left << bookVect[book].getAuthor() << std::setw(20) << std::left << bookVect[book].getGenre() << std::setw(10) << bookVect[book].getContent() << std::setw(10) << std::left << bookVect[book].getYear() << bookVect[book].getAuthorID() << std::setw(15) << std::endl;
	return out;
}
/*
TODO
- Create a variable that stores the current logged in user
- Implemented the currentUser to essentially take the place of the loggedIn bool
*/


 //Main Function
int main()
{
	User guestUser("guest");			// This is the default user when the program starts
	//std::cout << "guestUser address in main: " << &guestUser << std::endl;
	// The current user holds the state for the current user signedin.
	// I made it a pointer because it will be assigned the address of the current signedin user
	// It needs the address of the current user because th current user could be modified though this variable
	User *currentLoggedInUser = &guestUser;
	/*std::cout << "currentUser pointer in main: " << currentUser << std::endl;
	std::cout << "currentUser address in main: " << &currentUser << std::endl;*/
	std::vector<User> userVect;
	std::vector<Book> bookVect;
	std::vector<Author> authorVect;
	int index = -1;				
	bool loop = true;
	//bool loggedIn = false;
	importFiles(userVect, bookVect, authorVect);

	std::cout << "          Library Management System" << std::endl;
	do
	{
		if (currentLoggedInUser == nullptr)
		{
			currentLoggedInUser = &guestUser;
		}
		loop = showMainMenu(userVect,bookVect, authorVect, currentLoggedInUser, index);
		exportUserFile(userVect);
		std::cout << "\n\n";
	} while (loop);
	return 0;	
}

// Shows menu and gets a choice from the user
// Calls the get choice function
bool showMainMenu(std::vector<User>& userVect,std::vector<Book>& bookVect, std::vector<Author> authorVect, User *currentLoggedInUser, int& i)
{

	// Shows the main menu based on logged in state and the type of user. 
	// If the logged in state is false, the menu for Guest will be shown
	
	int choice;
	
	std::cout << "====================================" << std::endl;

	if ((*currentLoggedInUser).getUserType() == "admin")
	{
		std::cout << "Signed on as " << (*currentLoggedInUser).getUserName() << std::endl;
		std::cout << "                   1. Browse Library" << std::endl;
		std::cout << "                   2. Search Books" << std::endl;
		std::cout << "                   3. Add Book" << std::endl;
		std::cout << "                   4. View Users (Broken option)" << std::endl;
		std::cout << "                   5. Sign Out" << std::endl;
		std::cout << "                   6. View Profile (beta)" << std::endl;
		std::cout << "                   7. Browse Authors" << std::endl;
		std::cout << "                   8. Add Author" << std::endl;
	}
	else if ((*currentLoggedInUser).getUserType() == "student")
	{
		std::cout << "Signed on as " << (*currentLoggedInUser).getUserName() << std::endl;
		std::cout << "                   1. Browse Library" << std::endl;
		std::cout << "                   2. Search Books" << std::endl;
		std::cout << "                   3. Return Book" << std::endl;
		std::cout << "                   4. Sign Out" << std::endl;
		std::cout << "                   5. View Profile (beta)" << std::endl;
	}
	
	else if ((*currentLoggedInUser).getUserType() == "guest")
	{
		std::cout << "Signed on as guest" << std::endl;
		std::cout << "                   1. Browse Library" << std::endl;
		std::cout << "                   2. Search Books" << std::endl;
		std::cout << "                   3. Sign In" << std::endl;
		std::cout << "                   4. Sign Up" << std::endl;
		std::cout << "                   5. Browse Authors" << std::endl;
	}	
	else
	{
		std::cout << "Something went wrong. Please exit the program and open it again." << std::endl;
	}
	std::cout << "                   0. Exit" << std::endl;
	std::cout << "        Enter a choice: ";
	std::cin >> choice;
	
	return getChoice(choice, userVect, bookVect, authorVect, currentLoggedInUser);
}

bool getChoice(int choice, std::vector<User>& userVect, std::vector<Book>& bookVect, std::vector<Author>& authorVect, User *currentLoggedInUser)
{
	bool again = true;

	if ((*currentLoggedInUser).getUserType() == "admin")
	{
		switch (choice)
		{
		case 1: browseBooks(bookVect, authorVect, currentLoggedInUser);
			break;
		case 2: searchBook(bookVect, authorVect, currentLoggedInUser);
			break;
		case 3: addBook(bookVect, authorVect);
			break;
		case 4: browseUsers(userVect, currentLoggedInUser);
			break;
		case 5: signOut(currentLoggedInUser);
			break;
		case 6: viewProfile(userVect, bookVect, currentLoggedInUser.getUserID(), currentLoggedInUser, currentLoggedInUser);
			break;
		case 7: browseAuthor(authorVect);
			break;
		case 8: addAuthor(authorVect);
			break;
		case 0: again = false;
			break;
		}
	}
	if ((*currentLoggedInUser).getUserType() == "student")
	{
		switch (choice)
		{
		case 1: browseBooks(bookVect, authorVect, currentLoggedInUser);
			break;
		case 2: searchBook(bookVect, authorVect, currentLoggedInUser);;
			break;
		case 3: returnBook(bookVect, currentLoggedInUser);
			break;
		case 4: signOut(currentLoggedInUser);
			break;
		case 5: viewProfile(userVect, bookVect, currentLoggedInUser.getUserID(), currentLoggedInUser, currentLoggedInUser);
			break;
		case 0: again = false;
			break;
		}
	}
	
	else					// Guest
	{
		switch (choice)
		{
		case 1:browseBooks(bookVect, authorVect, currentLoggedInUser); 
			break;
		case 2:searchBook(bookVect, authorVect, currentLoggedInUser);
			break;
		case 3: signIn(userVect, /*userIndex,*/ currentLoggedInUser);			// Passes the User vector to the signIn() function
			break;
		case 4: signUp(userVect);			// Calls the signUp function. Passes the user vector to it
			break;
		case 5: browseAuthor(authorVect);
			break;
		case 0: again = false;
			break;			
		}
	}	
	return again;
}

// This function takes the reference of user vector (userVect) and a pointer (currentLoggedInUser)
// The function asks the user to sign in. If it finds a match, then the pointer will be given the memory address of
// The match and then return
void signIn(std::vector<User>& userVect/*, int& index*/, User *currentLoggedInUser)
{
	std::string userNameSearchKey;
	std::string pass;
	int signInRetry = 0;
	bool userFound = false;
	
	while (!userFound && signInRetry < 3 && userNameSearchKey != "b")
	{
		if (signInRetry >= 3)
		{
			throw 2;
		}
		std::cout << "\nEnter a username, or 'b' to go back" << std::endl;
		std::cout << "Username: ";
		std::cin >> userNameSearchKey;
		if (userNameSearchKey == "b")
		{
			break;
		}
		std::cout << "Password: ";
		std::cin >> pass;
		for (int i = 0; i < userVect.size(); i++)
		{
			if (userNameSearchKey == userVect[i].getUserName() && pass == userVect[i].getPassword())
			{
				userFound = true;
				std::cout << "\nWelcome " << userVect[i].getUserName();		// Welcomes the user
				//index = i;			// When this function ends
				currentLoggedInUser = &userVect[i];
				break;
			}
			else
			{
				std::cout << "\nError: Incorrect username or password." << std::endl;
				signInRetry++;
				if (signInRetry >= 3)
				{
					std::cout << "Too many incorrect attempts. Going back to the main menu." << std::endl;
				}
				break;
			}					
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
	//bool keepSearching = true;
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
			User tempU(static_cast<int>(u.size()), name, password);
			u.push_back(tempU);
			exportUserFile(u);
			passwordsMatch = true;
		}				
	}
}

void importFiles(std::vector<User>& userVect, std::vector<Book>& bookVect, std::vector<Author>& authorVect)
{
	std::string tempLine;
	std::string parseLine;
	std::vector<std::string> attribute;
	std::ifstream inFile("userDB.tsv");				// imports the user file
	if (!inFile)									// If unable to import the user file, create a new user file and add the administrator as the first user
	{
		userVect.push_back(User{"admin"});
		std::cout << "No User data base file found" << std::endl;
		std::cout << "Creating a new user data base file.\n\n" << std::endl;
		std::ofstream tempOut("userDB.txt");
		tempOut.close();
		exportUserFile(userVect);
	}
	// Parsing the file and adding it to the User vector
	while (std::getline(inFile, tempLine))		// Get the line
	{
		std::stringstream streamLine(tempLine);
		while (std::getline(streamLine, parseLine, '\t'))	// Get a string from the line separated by tabs
		{
			attribute.push_back(parseLine);			// Add the parsed line to a string vector
		}
		addUser(userVect, stoi(attribute[0]), attribute[1], attribute[2], attribute[3], attribute[4], stoi(attribute[5]), attribute[6]);
		attribute.clear();
	}
	inFile.close();

	// Getting the books database file
	inFile.open("bookDB.tsv");
	if (!inFile)
	{
		std::cout << "No book data base found" << std::endl;
		std::cout << "Creating an empty book data base.\n\n" << std::endl;
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
		//std::cout << attribute.size() << std::endl;

		if (attribute.size() == 9)
		{
			importBook(bookVect, stoi(attribute[0]), attribute[1], attribute[2], attribute[3], stoi(attribute[4]), stoi(attribute[5]), stoi(attribute[6]), stoi(attribute[7]), attribute[8]);
		}
		else if (attribute.size() == 10)
		{
			importBook(bookVect, stoi(attribute[0]), attribute[1], attribute[2], attribute[3], stoi(attribute[4]), stoi(attribute[5]), stoi(attribute[6]), stoi(attribute[7]), attribute[8], stoi(attribute[9]));
		}
		attribute.clear();
	}
	inFile.close();

	// Import the author data base file
	inFile.open("authorDB.tsv");
	if (!inFile)
	{
		std::cout << "Unable to load the author database." << std::endl;
		std::cout << "Creating an empty author database file.\n\n" << std::endl;
		std::ofstream tempOut("authorDB.tsv");
	}
	// Parse the authors from the fil into the program
	while (std::getline(inFile, tempLine))
	{
		std::stringstream streamLine(tempLine);
		while (std::getline(streamLine, parseLine, '\t'))
		{
			attribute.push_back(parseLine);
		}
		if (attribute.size() == 3)
		{
			importAuthor(authorVect, stoi(attribute[0]), attribute[1], attribute[2]);
		}
		else
		{
			importAuthor(authorVect, stoi(attribute[0]), attribute[1], attribute[2], attribute[3]);  // TODO: implement an importAuthor() function
		}
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
		outFile << userVect[i].getUserID() << "\t" << userVect[i].getUserName() << "\t" << userVect[i].getFirstN() << "\t" << userVect[i].getLastN() << "\t" << userVect[i].getPassword() << "\t" << userVect[i].getBookNo() << "\t" << userVect[i].getUserType() << std::endl;
	}
	outFile.close();
}


// This will simply change the bool li to false so 
// when the emain functions do/while loop calls the showMenu function, 
// The li will be false and show the menu for Guest

// This function will take the pointer to a user (licurrentLoggedInUser)
// and assign it to null pointer
// back in the main function, the do/while loop will see that licurrentLoggedInUser is null and then assign it to the address of the guest user
void signOut(User *licurrentLoggedInUser)
{
	licurrentLoggedInUser = nullptr;			
}

void showBookHeading()
{	
	std::cout << "\n" << std::setw(15) << std::left << "Book Number" << std::setw(43) << std::left << "Title" << std::setw(23) << std::left << "Author" << std::setw(20) << std::left << "Genre" << std::setw(10) << std::left << "Content" << std::setw(10) << std::left << "Year"  << "Author ID" << std::endl;
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

// This is an admin only function that is used to add books to the data base
// The minimum amount of infomration needed is title, the rest of the info can
// be added/modified with editBook(). The book number and checked out info will be automatically generated.
// maybe hold the information for the required data in an array, and 
void addBook(std::vector<Book>&bookVect, std::vector<Author> authorVect)
{	
	// declare the variables (title, author, year, genre)
	std::string title;
	std::string author;
	int year;
	std::string authorID;
	
	// Get a title (std::string). if the string is empty, tell the user that a title is required
	//std::getline(std::cin, catcher);
	std::cout << "new Title: ";
	std::getline(std::cin, title);
	std::getline(std::cin, title);
	// Get an Author (std::string). if the string is empty, tell the user that an author is required
	std::cout << "Author name: ";
	std::getline(std::cin, author);

	// The the list of available authors to the users and prompt him to choose one
	std::cout << "Choose an author" << std::endl;
	for (int i = 0; i < authorVect.size(); i++)
	{
		listAuthor(authorVect, i);
	}

	//browseAuthor(authorVect);

	std::cout << "Author Not Listed" << std::endl;
	std::cout << "Choice: " << std::endl;
	std::getline(std::cin, authorID);

	for (int i = 0; i < authorVect.size(); i++)
	{
		if (stoi(authorID) == authorVect[i].getAuthorID())
		{
			std::cout << "Added " << authorVect[i].getFName() << " " << authorVect[i].getLName() << std::endl;
		}
	}	
	
	// Get a year (int). if the int is empty, tell the user that a year is required
	std::cout << "Year published: ";
	std::cin >> year;

	//Book tempBook(bookVect.size(),title, author, year);
	Book tempBook(static_cast<int>(bookVect.size()), title, stoi(authorID), year);
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
		outFile << bookVect[i].getBookNo() << "\t" << bookVect[i].getTitle() << "\t" << bookVect[i].getAuthor() << "\t" << bookVect[i].getGenre() << "\t" << bookVect[i].getChpt() << "\t" << bookVect[i].getYear() << "\t" << bookVect[i].getPages() << "\t" << bookVect[i].getChpt() << "\t" << bookVect[i].getCheckedOut() << "\t" << bookVect[i].getAuthorID() << std::endl;
	}
}

// This function is used to add books from the TSV file WITH the Author ID
void importBook(std::vector<Book>& bookVect, int bookNo, std::string title, std::string author, std::string genre, int c, int y, int nc, int p, std::string co, int authorID)
{
	Book tempB(bookNo, title, author, genre, c, y, nc, p, stoi(co), authorID);

	bookVect.push_back(tempB);
	//std::cout << "Number of books: " << bookVect.size() << std::endl;
}


// This function will list the attributes for the book and asks the user
// to enter a number that corresponds to the attribute they want to edit
void editBook(std::vector<Book>& bookVect, std::vector<Author>& authorVect, int book, User user)
{
	int choice;
	std::string choiceStr;
	std::string newEntry;
	// list the options that can be changed
	std::cout << "\n             BOOK EDITOR {BETA}" << std::endl;
	std::cout << "Select an attribute to change:" << std::endl;
	std::cout << "1. Title     \n2. Author     \n3. Year Published";
	std::cout << "\n4. Genre     \n5. Content    \n6. Description";
	std::cout << "\n7. Author ID";
	std::cout << "\n0. Cancel" << std::endl;
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
	else if (choice == 7)
	{
		std::string authorNum;
		do
		{
			browseAuthor(authorVect);
			std::cout << "0 - Author Not Listed" << std::endl;
			std::cout << "b - Go Back" << std::endl;
			//std::string authorNum;
			std::cout << "\nSelect the author: ";
			std::getline(std::cin,authorNum);
			if (authorNum == "b")
			{
				;
			}
			else if (stoi(authorNum) == 0)
			{
				addAuthor(authorVect);
			}
			else if (stoi(authorNum) > 0)
			{
				for (int i = 0; i < authorVect.size(); i++)
				{
					if (stoi(authorNum) == authorVect[i].getAuthorID())
					{
						// std::cout << "before" << std::endl;
						bookVect[book].setAuthorID(stoi(authorNum));
						// std::cout << "after" << std::endl;
						std::cout << "The authorID for " << bookVect[book].getTitle() << " was changed to " << bookVect[book].getAuthorID() << std::endl;
						exportBookFile(bookVect);
					}
				}
			}
			else
			{
				std::cout << "Invalid input" << std::endl;
			}
		} while (authorNum != "b" && stoi(authorNum) >= 0);	
	}
}

// This function will allow a user to borrow a book
// only if loggedIn is true, user type is 'student'
// user does not already have a book checked out,
// and book is not already checked out
void borrowBook(std::vector<Book>& bookVect, int book , User& user)
{
	// Borrow book works for now
	if (user.getBookNo() == 0)		// Checks to see if user already has a book checked out
	{
		// Will need to optimize this better to combine the two if conditions in one line
		//std::cout << bookVect[book].getCheckedOut() << std::endl;
		if (bookVect[book].getCheckedOut() == false)	// Checks to see if the book is not checked out...
		{
			user.setBookNo(bookVect[book].getBookNo());
			bookVect[book].setCheckedOut(true);
			std::cout << "\nYou borrowed \"" << bookVect[book].getTitle() << "\". Happy reading!\n";
			exportBookFile(bookVect);
		}
		else
		{
			std::cout << "\nThis book is already checked out and must be returned before it can be returned again.\n";
		}
	}
	else
	{
		std::cout << "\nYou have already borrowed a book. You must return the book you borrowed before borrowing ab it.\n";
	}
}

void returnBook(std::vector<Book>& bookVect, User *currentLoggedInUser)
{
	// if the bookNo in the user matches book in bookVect
	// Then change the checkedOut variable in the book to f
	// change the bookNo in the the user to 0
	int beginning = 0;
	int end = static_cast<int>(bookVect.size()) - 1;
	bool found = false;

	// TODO: COMPLETE BINARY SEARCH
	while(beginning < end || found == false)
	{
		if (user.getBookNo() == bookVect[end / 2].getBookNo())
		{
			found = true;
			bookVect[end / 2].setCheckedOut(false);
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


void deleteBook(std::vector<Book>& bookVect, int book, User user)
{
	if (user.getUserType() != "admin")
	{
		printf("Invalid Input");
		return;
	}

	std::string choice;
	std::cout << "\n~Book removal is in beta~" << std::endl;
	// TODO
	std::cout << "\nAre you sure you want to delete this book?" << std::endl;
	std::cout << "This action cannot be undone" << std::endl;
	std::cout << "Enter y to continue or n to cancel: ";
	//std::cin >> choice;
	std::getline(std::cin, choice);

	if (choice == "y")
	{
		std::cout << "Cool!" << std::endl;
		std::cout << bookVect[book].getTitle() << " was removed from the libary" << std::endl;
		bookVect.erase(bookVect.begin() + book);
	}
}

/*
void browseBooks(std::vector<Book>& bookVect, std::vector<Author>& authorVect, bool loggedIn, User& user, int book)
{
	/// This function takes the the book vector, the author Vector, the user, and 
	std::string searchKey;
	std::getline(std::cin, searchKey);
	do
	{		
		bool bookFound = false;
		//std::string searchKey;
		book = 0;
		
		// Show the table heading
		showBookHeading();
		std::cout <<"Number of books" << bookVect.size() << std::endl;
		for (int i = 0; i < bookVect.size(); i++)
		{
			listBook(bookVect, i);
			//std::cout << "Here" << std::endl;
		}
		std::cout << "\nEnter the book number of the book you'd like to view, or 'b' to go back to the main menu\n";
		std::cout << "\nBook Number: ";
		std::getline(std::cin, searchKey);
		//std::getline(std::cin, searchKey);
		if (searchKey != "b")
		{
			for (int i = 0; i < bookVect.size() && !bookFound; i++)
			{
				if (stoi(searchKey) == bookVect[i].getBookNo())
				{
					viewBook(bookVect, authorVect, i, loggedIn, user);
					bookFound = true;
				}
			}
		}		
	} while (searchKey != "b");
}
*/
void browseBooks(std::vector<Book>& bookVect, std::vector<Author>& authorVect, User *currentLoggedInUser)
{
	/// This function takes the the book vector, the author Vector, the user, and 
	std::string searchKey;
	std::getline(std::cin, searchKey);
	int book;
	do
	{		
		bool bookFound = false;
		//std::string searchKey;
		book = 0;
		
		// Show the table heading
		showBookHeading();
		std::cout <<"Number of books" << bookVect.size() << std::endl;
		for (int i = 0; i < bookVect.size(); i++)
		{
			listBook(bookVect, i);
			//std::cout << "Here" << std::endl;
		}
		std::cout << "\nEnter the book number of the book you'd like to view, or 'b' to go back to the main menu\n";
		std::cout << "\nBook Number: ";
		std::getline(std::cin, searchKey);
		//std::getline(std::cin, searchKey);
		if (searchKey != "b")
		{
			for (int i = 0; i < bookVect.size() && !bookFound; i++)
			{
				if (stoi(searchKey) == bookVect[i].getBookNo())
				{
					viewBook(bookVect, authorVect, i, user);
					bookFound = true;
				}
			}
		}		
	} while (searchKey != "b");
}
/*
void searchBook(std::vector<Book>& bookVect, bool loggedIn, User user) // NEW/UNTESTED
{
	// This book search function is different from the original because it accumulates the search results
	// in a list and then presents the results. 
	std::string searchTerm;
	std::string getChoice;
	bool found = false;
	std::cout << "\nThis feature is in beta right now...." << std::endl;	
	//User enters a term
	std::cout << "Enter a book name: ";
	std::getline(std::cin, searchTerm);
	std::getline(std::cin, searchTerm);
	//create a vector to hold the search results
	std::vector<Book> searchResults;

	//search the term
	for (int bookIndex = 0; bookIndex < bookVect.size(); bookIndex++)
	{
		if (searchTerm == bookVect[bookIndex].getTitle())
		{
			searchResults.push_back(bookVect[bookIndex]);
		}
	}

	if (searchResults.size() == 0)
	{
		std::cout << "No results found" << std::endl;
	}
	else
	{
		showHeading();
		for (int i = 0; i < searchResults.size(); i++)
		{
			listBook(searchResults, i);
		}
	}

	std::cout << "Enter the book number of the book you would like to view";

	//if a book is found and its book number isn't already on the list
		//add that book book number to the list
		//repeat until all the books have been searched
	//Show the results of the search by listing out the books
	
}
*/

void searchBook(std::vector<Book>& bookVect, std::vector<Author>& authorVect, User *currentLoggedInUser)
{
	/*
		User enters a term
		search the term
		create a list
		if a book is found and its book number isn't already on the list
			add that book book number to the list
			repeat until all the books have been searched
		Show the results of the search by listing out the books
	*/
	std::string searchTerm;
	std::string getChoice;
	bool found = false;
	std::vector<int> results;
	std::cout << "\nThis feature is in beta right now...." << std::endl;
	std::cout << "Enter a book name: ";
	std::getline(std::cin, searchTerm);
	std::getline(std::cin, searchTerm);

	do
	{
		bool bookFound = false;
		showBookHeading();
		for (int book = 0; book < bookVect.size(); book++)
		{
			if (searchTerm == bookVect[book].getTitle())
			{
				found = true;
				listBook(bookVect, book);  // List each book
				results.push_back(bookVect[book].getBookNo());
			}
		}

		std::cout << "Enter the book number of the book you'd like to view ('b' to go back to the main menu): ";
		std::getline(std::cin, getChoice);
		if (getChoice != "b")
		{
			//for (int i = 0; i < results.size() && !bookFound; i++)
			for (int book = 0; book < bookVect.size() && !bookFound; book++)
			{
				if (stoi(getChoice) == bookVect[book].getBookNo())
				//if (stoi(getChoice) == bookVect[book].getBookNo())
				{
					viewBook(bookVect, authorVect, book, user);
					bookFound = true;
				}				
			}
		}		
	} while (getChoice != "b");			// This is to go back to the search results after the user has viewed a book 	
}

void listBook(std::vector<Book> bookVect, int book)
{
	//std::cout << std::setw(15) << std::left << bookVect[book].getBookNo() << std::setw(43) << std::left << bookVect[book].getTitle() << std::setw(23) << std::left << bookVect[book].getAuthor() << std::setw(20) << std::left << bookVect[book].getGenre() << std::setw(10) << bookVect[book].getContent() << std::setw(10) << std::left << bookVect[book].getYear() << bookVect[book].getAuthorID() << std::setw(15) << std::endl;
	std::cout << bookVect[book] << std::endl;
}

// This function will show information about the book
// title heading, Short desrcription, and some menu options at the bottom depending on the userType.
// It takes the user vector, book vector, author vector, an int that represents the book index, and the user
// Borrow, Edit, Main Menu
void viewBook(std::vector<Book>& bookVect, std::vector<Author>& authorVect, int book, User& user)
{
	std::cout << "--View Book {Beta}--\n";
	std::cout << "\n\n           " << bookVect[book].getTitle() << std::endl;
	std::cout << bookVect[book].getAuthor() << "               " << bookVect[book].getYear() << std::endl;
	std::cout << "-------------------------------" << std::endl;
	std::cout << "Author ID: " << bookVect[book].getAuthorID() << std::endl; // This is temporary
	std::cout << bookVect[book].getDesc() << std::endl;
	showBookOptions(bookVect, authorVect, book, user);
}

// This is an entirly new menu that shows the options a user can do with a book
// it lists out the options and then calls another function to handle the choice
// made by the user.
void showBookOptions(std::vector<Book>& bookVect, std::vector<Author>& authorVect, int book, User& user)
{
	//int choice;
	std::string choice;
	std::string choiceStr;
	std::cout << "1. Borrow         \n2. Return         \n3. Edit";
	if (user.getUserType() == "admin")
	{
		std::cout << "\n4. Delete";
	}
	std::cout << "\nb. Go Back\n";
	std::cout << "Enter a choice: ";
	std::getline(std::cin, choice);
	//choice = stoi(choiceStr);
	bookOptionChoice(choice, bookVect, authorVect, book, user);		// TODO:
}

// This function will take the choice, the book, the logged in state, and the user and call other functions based on the choice
void bookOptionChoice(std::string choice, std::vector<Book>& bookVect, std::vector<Author>& authorVect, int book, User& user)
{
	if (choice == "b")
	{
		;
	}
	else if (stoi(choice) == 1)
	{
		borrowBook(bookVect, book, user);
	}
	else if (stoi(choice) == 2)
	{
		returnBook(bookVect, user);
	}
	else if (stoi(choice) == 3)
	{
		editBook(bookVect, authorVect, book, user);
	}
	else if (stoi(choice) == 4)
	{
		deleteBook(bookVect, book, user);
	}
	else
	{
		std::cout << "That's not a valid choice." << std::endl;
	}
}

// This function will allow the user to view and edit his/her profile. Similar to the view book function
// The vector to be searched examined, the book vector, the user that is viewing the profile, and the user to be viewed
// This function is meant for the user to see his own profile and the profile of others. If the user is viewing his own 
// profile, then he will have options to change password, 
void viewProfile(std::vector<User>& userVect, std::vector<Book> bookVect, int userID, User& user, User* currentLoggedInUser)
{
	std::cout << "\n\n--View profile {Beta}--" << std::endl;
	int userIndex;
	userIndex = 0;
	bool userFound = false;
	bool bookFound;
	for (userIndex; userIndex < userVect.size() || userFound == false; userIndex++)
	{
		if (userID == userVect[userIndex].getUserID())
		{
			std::cout << "Index      : " << userIndex << std::endl;
			std::cout << "ID         : " << userVect[userIndex].getUserID() << std::endl;
			std::cout << "Username   : " << userVect[userIndex].getUserName() << std::endl;
			std::cout << "First Name : " << userVect[userIndex].getFirstN() << std::endl;
			std::cout << "Last Name  : " << userVect[userIndex].getLastN() << std::endl;
			std::cout << "userType   : " << userVect[userIndex].getUserType() << std::endl;
			std::cout << "Book       : ";
			userFound = true;

			if (userVect[userIndex].getBookNo() == 0)
			{
				std::cout << "None" << std::endl;
			}
			else
			{
				for (int i = 0; i < bookVect.size() || bookFound == false; i++)
				{
					if (userVect[userIndex].getBookNo() == bookVect[i].getBookNo())
					{
						std::cout << bookVect[i].getTitle() << std::endl;
						bookFound = true;
					}
				}
			}			
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

void importAuthor(std::vector<Author> &authorVect,int authID, std::string firstName, std::string lastName, std::string penName)
{	
	if (penName == " ")
	{
		Author tempAuthor(authID, firstName, lastName);
		authorVect.push_back(tempAuthor);
	}
	else
	{
		Author tempAuthor(authID, firstName, lastName, penName);
		authorVect.push_back(tempAuthor);
	}	
}

void exportAuthorFile(std::vector<Author> authorVect)
{
	std::ofstream outFile;
	outFile.open("authorDB.tsv");
	for (int i = 0; i < authorVect.size(); i++)
	{
		outFile << authorVect[i].getAuthorID() << "\t" << authorVect[i].getFName() << "\t" << authorVect[i].getLName() << "\t" << authorVect[i].getPName() << std::endl;
	}
	outFile.close();
}

void addAuthor(std::vector<Author> &authorVect)
{
	std::string firstName, lastName, penName;
	std::cout << "Add New Author {Beta}" << std::endl;
	std::cout << "Author First Name: ";
	std::cin >> firstName;
	std::cout << "Author Last Name:  ";
	//std::getline(std::cin, lastName);
	std::cin >> lastName;
	//std::getline(std::cin, lastName);
	std::cout << "Author Pen Name:   ";
	std::getline(std::cin, penName);
	std::getline(std::cin, penName);

	Author tempAuthor(firstName, lastName, penName, static_cast<int>(authorVect.size()));
	authorVect.push_back(tempAuthor);
	exportAuthorFile(authorVect);
}

void listAuthor(std::vector<Author> &authorVect, int index)
{
	std::cout << std::setw(15) << std::left << authorVect[index].getAuthorID() << std::setw(20) << std::left << authorVect[index].getFName() << std::setw(20) << std::left << authorVect[index].getLName() << authorVect[index].getPName();
}

void listUser(std::vector<User>& userVect, int index)
{
	std::cout << std::setw(15) << std::left << userVect[index].getUserID() << std::setw(20) << std::left << userVect[index].getFirstN() << std::setw(20) << std::left << userVect[index].getLastN() << userVect[index].getUserType();
}

void browseAuthor(std::vector<Author> &authorVect)
{
	//showAuthorheading();
	std::cout << std::setw(15) << std::left <<  "Author ID" << std::setw(20) << std::left << "First Name" << std::setw(20) << std::left << "Last Name" << "Pen Name" << std::endl;
	std::cout << "===========================================================================" << std::endl;
	for (int i = 0; i < authorVect.size(); i++)
	{
		listAuthor(authorVect, i);
		std::cout << std::endl;
	}
}

void browseUsers(std::vector<User>& userVect, User *currentLoggedInUser)
{
	// TODO: Modify this function to operate based on the userType in the second parameter
	std::cout << std::setw(15) << std::left << "User ID" << std::setw(20) << std::left << "First Name" << std::setw(20) << std::left << "Last Name" << "User Type" << std::endl;
	std::cout << "===========================================================================" << std::endl;
	for (int i = 0; i < userVect.size(); i++)
	{
		listUser(userVect, i);
		std::cout << std::endl;
	}
}