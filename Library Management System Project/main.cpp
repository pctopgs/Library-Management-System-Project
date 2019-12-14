#include "Book.h"
#include <vector>
#include <fstream>					// This is to use User files and Book files
#include <sstream>
bool showMenu(std::vector<User>&, bool&, int);
bool getChoice(int, std::vector<User>&, int, bool&);		// The user needs to be passed by reference
void signIn(std::vector<User>&);
void signUp(std::vector<User>&);
void signOut(std::vector<User>&, bool&);
void importFile(std::vector<User>&);
void addUser(std::vector<User>& u, int id, std::string un, std::string fn, std::string ln, std::string pw, std::string ut);
void exportFile(std::vector<User>);

// Main Function
int main()
{
	std::vector<User> users;

	int index = 0;				
	bool loop = true;
	bool loggedIn = false;
	importFile(users);
	std::vector<Book> book;

	std::cout << "          Library System" << std::endl;
	do
	{
		loop = showMenu(users,loggedIn,index);
	} while (loop);
	return 0;
}

// Shows menu and gets a choice from the user
// Calls the get choice function
bool showMenu(std::vector<User>& u, bool& li, int i = -1)
{
	// Shows the main menu based on logged in state and the type of user. 
	// If the logged in state is false, the menu for Guest will be shown
	// Guest
	// Student
	// Admin


	int choice;
	std::cout << "====================================" << std::endl;

	if (li)
	{
		std::cout << "Signed on as " << u[i].getUserName() << std::endl;
		if (u[i].getUserType() == "admin")
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
		else if (u[i].getUserType() == "student")
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
	else if (li == false)
	{
		std::cout << "Signed on as Guest" << std::endl;
		//std::cout << "Signed on as " << u[i].getUserName() << std::endl;
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

	return getChoice(choice, u, i, li);
}

bool getChoice(int choice, std::vector<User>& u, int i, bool& li)
{
	bool again = true;
	if (li)
	{
		if (u[i].getUserType() == "admin")
		{
			switch (choice)
			{
			case 1:;
				break;
			case 2:;
				break;
			case 3:;
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
			case 1:;
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
		case 1:;
			break;
		case 2:;
			break;
		case 3: signIn(u);			// Passes the User vector to the signIn() function
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

void signIn(std::vector<User>&u)
{
	std::string name;
	std::string pass;
	int i = 0;
	bool keepSearching = true;
	bool found = false;
	bool signedIn = true;
	std::cout << "Current users: " << u.size() << std::endl;
	for (int i = 0; i < u.size(); i++)
	{
		std::cout << u[i].getUserName() << std::endl;
	}
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
					showMenu(u, signedIn, i);			// Call the showMenu function with the user as the argument
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
			std::cout << i << std::endl;
			std::cout << u.size() << std::endl;
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

void importFile(std::vector<User>& u)
{
	std::string tempLine;
	std::string parseLine;
	std::stringstream streamLine;
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
	while (getline(inFile, tempLine))		// Get the line
	{
		streamLine << tempLine;				
		while(getline(streamLine, parseLine, ','))	// Get a string from the line separated by commas
		{
			attribute.push_back(parseLine);			// Add the parsed line to a string vector
		}
		addUser(u, stoi(attribute[0]), attribute[1], attribute[2], attribute[3], attribute[4], attribute[5]);
		attribute.clear();
	}
	inFile.close();
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

// This will simply change the bool li to false so 
// when the emain functions do/while loop calls the showMenu function, 
// The li will be false and show the menu for Guest
void signOut(std::vector<User>& u, bool& li)
{
	li = false;			
}