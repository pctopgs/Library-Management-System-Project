#include "Book.h"
#include <vector>
#include <fstream>
void showMenu(std::vector<User>, int);
void getChoice(int, std::vector<User>, int);
void signIn(std::vector<User>);
//void signUp();

// Main Function
int main()
{
	std::vector<User> users;
	int index = 0;				// 
	users.push_back(User{});
	std::vector<Book> book;
	std::cout << "          Library Management" << std::endl;
	showMenu(users, index);
	return 0;
}

// Shows menu and gets a choice from the user
// Calls the get choice function
void showMenu(std::vector<User> u, int i)
{
	// Shows the main menu based on the type of user:
	// Guest
	// Student
	// Admin
	// I may have to create a user class that holds 'alias'
	bool loggedIn;
	int choice;
	std::cout << "====================================" << std::endl;
	std::cout << "Signed on as " << u[i].getUserName() << std::endl;
	if (u[i].getUserType() == "admin")
		{
			std::cout << "               1. View Books" << std::endl;
			std::cout << "               2. Search Books" << std::endl;
			std::cout << "               3. Add Book" << std::endl;
			std::cout << "               4. Remove Book" << std::endl;
			std::cout << "               5. Edit Book" << std::endl;
			std::cout << "               6. Sign Out" << std::endl;
		}
	else if (u[i].getUserType() == "student")
		{
			std::cout << "               1. View Books" << std::endl;
			std::cout << "               2. Search Books" << std::endl;
			std::cout << "               3. Checkout Book" << std::endl;
			std::cout << "               4. Return Book" << std::endl;
			std::cout << "               5. Edit Book" << std::endl;
			std::cout << "               6. Sign Out" << std::endl;
		}
	else if (u[i].getUserType() == "guest")		// The user is a guest and can only view and search books
	{
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
	getChoice(choice, u, i);
}

void getChoice(int choice, std::vector<User> u, int i)
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
		case 0:;
			break;
		}
	}
	if (u[i].getUserType() == "guest")
	{
		switch (choice)
		{
		case 1:;
			break;
		case 2:;
			break;
		case 3: signIn(u);			// Passes the User vector to the signIn() function
			break;
		case 4:;
			break;
		case 5:;
			break;
		case 0:;
			break;
		}
	}
}

void signIn(std::vector<User>u)
{
	int tries = 0;
	std::string user;
	std::string password;
	std::cout << "Username: ";
	std::cin >> user;
	for (int i = 0; i < u.size(); i++)
	{
		if (user == u[i].getUserName())
		{
			std::cout << "Password: ";		// TODO: Write code for the logged in state
			getline(std::cin, password);
			if (password == u[i].getPassword())
			{
				std::cout << "Welcome " << u[i].getUserName() << std::endl;		// Welcomes the user
				showMenu(u, i);			// Call the showMenu function with the user as the argument
			}
		}
		else
		{
			while (tries <= 3)
			{
				std::cout << "That user is not in our system" << std::endl;
				std::cout << "Try again." << std::endl;
			}

		}
	}
}