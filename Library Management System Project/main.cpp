#include "Book.h"
#include <vector>
void showMenu(User);
void getChoice(int, std::string);
void signIn();
void signUp();

// Main Function
int main()
{
	std::vector<User> users;
	users.push_back(User{});
	std::vector<Book> book;
	std::cout << "Library Management" << std::endl;
	showMenu(users[0]);
	return 0;
}

// Shows menu and gets a choice from the user
// Calls the get choice function
void showMenu(User )
{
	// Shows the main menu based on the type of user:
	// Guest
	// Student
	// Admin
	// I may have to create a user class that holds 'alias'
	bool loggedIn;
	int choice;
	std::string alias = "guest";
	if (alias == "admin")
		{
			std::cout << "====================================" << std::endl;
			std::cout << "          1. View Books" << std::endl;
			std::cout << "          2. Search Books" << std::endl;
			std::cout << "          3. Add Book" << std::endl;
			std::cout << "          4. Remove Book" << std::endl;
			std::cout << "          5. Edit Book" << std::endl;
			std::cout << "          6. Sign Out" << std::endl;
		}
	else if (alias == "student")
		{
			std::cout << "====================================" << std::endl;
			std::cout << "          1. View Books" << std::endl;
			std::cout << "          2. Search Books" << std::endl;
			std::cout << "          3. Checkout Book" << std::endl;
			std::cout << "          4. Return Book" << std::endl;
			std::cout << "          5. Edit Book" << std::endl;
			std::cout << "          6. Sign Out" << std::endl;
		}
	else		// The user is a guest and can only view and search books
	{
		std::cout << "====================================" << std::endl;
		std::cout << "          1. View Books" << std::endl;
		std::cout << "          2. Search Books" << std::endl;
		std::cout << "          3. Sign Out" << std::endl;
	}
	std::cout << "            0. Exit" << std::endl;
	std::cout << "   Enter a choice: ";
	std::cin >> choice;
	getChoice(choice, alias);
}

void getChoice(int choice, std::string alias)
{
	if (alias == "admin")
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
	if (alias == "student")
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
	if (alias == "guest")
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
}

void signIn()
{
	std::string user;
	std::string password;
	std::cout << "Enter a username:" << std::endl;
	std::cin >> user;
	//for (int i = 0;)
}