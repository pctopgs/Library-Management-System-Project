#include "Book.h"
#include <vector>
#include <fstream>					// This is to use User files and Book files
#include <sstream>
bool showMenu(std::vector<User>&, std::vector<Book>&, bool&, int&);
bool getChoice(int, std::vector<User>&, std::vector<Book>&, int&, bool&);		// The user needs to be passed by reference
void signIn(std::vector<User>&, int&, bool&);
void signUp(std::vector<User>&);
void signOut(std::vector<User>&, bool&);
void importFile(std::vector<User>&, std::vector<Book>&);
void addUser(std::vector<User>& u, int id, std::string un, std::string fn, std::string ln, std::string pw, std::string ut);
void importBook(std::vector<Book>& b, int bn, std::string t, std::string a, std::string g, int c, int y, int np, int nc, int p, std::string co);
void exportFile(std::vector<User>);
void importBook(std::vector<Book>& bookVect, int bn, std::string t, std::string a, std::string g, int c, int y, int np, int nc, int p, std::string co);
void listBooks(std::vector<Book> b);
void addBook(std::vector<Book>&);

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
	// Guest
	// Student
	// Admin
	int choice;
	std::cout << "====================================" << std::endl;

	if (loggedIn)
	{
		std::cout << "Signed on as " << userVect[i].getUserName() << std::endl;
		if (userVect[i].getUserType() == "admin")
		{
			std::cout << "                   1. View Books" << std::endl;
			std::cout << "                   2. Search Books" << std::endl;
			std::cout << "                   3. Add Book" << std::endl;
			std::cout << "                   4. Remove Book" << std::endl;
			std::cout << "                   5. Edit Book" << std::endl;
			std::cout << "                   6. Add User" << std::endl;
			std::cout << "                   7. Sign Out" << std::endl;
			std::cout << "                   8. View Profile" << std::endl;
		}
		else if (userVect[i].getUserType() == "student")
		{
			std::cout << "                   1. View Books" << std::endl;
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
		std::cout << "                   1. View Books" << std::endl;
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
			case 2:;
				break;
			case 3: addBook(bookVect);
				break;
			case 4:;
				break;
			case 5:;
				break;
			case 6:;
				break;
			case 7: signOut(u, li);
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
		case 2:;
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
				//std::cout << "\nThat username already exists." << std::endl;
				std::cout << "Password: ";
				std::cin >> pass;
				if (pass == u[i].getPassword())
				{
					std::cout << "\n\nWelcome " << u[i].getUserName() << std::endl;		// Welcomes the user
					//showMenu(u, signedIn, i);			// Call the showMenu function with the user as the argument
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
		//std::cin >> pass;
		std::cout << std::endl;
		//User tempU(name, pass);
		//u.push_back(tempU);
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
		exportFile(u);
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
		exportFile(u);
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
		importBook(b, stoi(attribute[0]), attribute[1], attribute[2], attribute[3], stoi(attribute[4]), stoi(attribute[5]), stoi(attribute[6]), stoi(attribute[7]), stoi(attribute[8]), attribute[9]);
		attribute.clear();
	}
}

void exportFile(std::vector<User> u)
{
	std::ofstream outFile;
	outFile.open("userDB.txt");
	for (int i = 0; i <u.size(); i++)
	{
		outFile << u[i].getUID() << "," << u[i].getUserName() << "," << u[i].getFirstN() << "," << u[i].getLastN() << "," << u[i].getPassword() << "," << u[i].getUserType() << std::endl;
	}
	outFile.close();
}

// This is used with importFiles() to append members to the User vector at the beginning of the program
void addUser(std::vector<User>& u, int id, std::string un, std::string fn, std::string ln, std::string pw, std::string ut)
{
	User tempU(id, un, fn, ln, pw, ut);
	u.push_back(tempU);
}


// This function is used to add books from the CSV
void importBook(std::vector<Book>& bookVect, int bn, std::string t, std::string a, std::string g, int c, int y, int np, int nc, int p, std::string co)
{
	Book tempB(bn, t, a, g, c, y, np, nc, p, co);	
	bookVect.push_back(tempB);
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
		std::cout << "There are now books to display." << std::endl;
	}
	else
	{
		// Display the Headings
		std::cout << "\nBook Number" << "Title" << "Author" << "Genre" << "Content" << "Year" << std::endl;
		for (int i = 0; i < b.size(); i++)
		{
			std::cout << b[i].getTitle() << b[i].getAuthor() << b[i].getYear() << std::endl;
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
	std::string catcher;		// Used to catch any residual data int he input stream buffer

	// Get a title (std::string). if the string is empty, tell the user that a title is required
	//std::cin.ignore(INT_MAX);
	//std::cin.clear();
	std::getline(std::cin, catcher);
	std::cout << "new Title: ";
	std::getline(std::cin, title);
	// Get an Author (std::string). if the string is empty, tell the user that an author is required
	std::cout << "\nAuthor name: ";
	std::getline(std::cin, author);
	
	// Get a year (int). if the int is empty, tell the user that a year is required
	std::cout << "\nYear published: ";
	std::cin >> year;

	Book tempBook(title, author, year);
	bookVect.push_back(tempBook);
}