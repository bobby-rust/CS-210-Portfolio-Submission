#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "User.h"

using namespace std;

// Length of the strings "username: " and "password: " 
const int WORD_LEN_USER_PASS = 10;

/**
 * Position of the word "username" in the string of data representing a user
 * a string of data representing a user looks like "username: example password: example"
*/
const int USERNAME_POS = 0;

unordered_map<string, string> ExtractUserInfo(string data)
{
	/**
	 * Extracts usernameand password from a single line of text
	 * Ex. ExtractUsernamePassword("username: hello password: world");
	 * Returns { "hello", "world" }
	 * string data must be formatted properly as in the example
	*/
	
	// Declare vars
	unordered_map<string, string> userInfo;
	string username;
	string password;
	char SPACE = ' ';
	int username_len = 0;

	// Extract username
	for (unsigned int i = WORD_LEN_USER_PASS; data[i] != SPACE; i++)
	{
		username += data[i];
		username_len++;
	}

	/**
	 * Extract password -
	 * The length of "username: " and "password: " is 20 i.e. (WORD_LEN_USER_PASS * 2), 
	 * plus the length of the username plus one unaccounted for space
	 * is the starting index of the password
	*/
	for (unsigned int j = ((WORD_LEN_USER_PASS * 2) + username_len + 1); j < data.length(); j++)
	{
		password += data[j];
	}

	// Insert user into map
	userInfo.insert({ username, password });

	return userInfo; // Return the map containing the user
}

vector<User> InitializeUsers()
{
	/**
	 * To initialize users,
	 * this function opens the data file,
	 * finds the users, and returns a 
	 * vector of all users in the data file
	*/

	// Declare vars
	vector<User> users;
	string currUserInfo;
	ifstream dataTestIn("data.txt");
	string currUsername;
	string currPassword;

	// While not eof
	while (getline(dataTestIn, currUserInfo))
	{
		// If line is empty
		if (currUserInfo == "") { break; }
		
		// Create map of username and password
		unordered_map<string, string> currUserMap = ExtractUserInfo(currUserInfo);
		// Set current username and password from map
		for (const auto& user : currUserMap)
		{
			currUsername = user.first;
			currPassword = user.second;
		}
		// Create user with current username and password
		User currUser = User(currUsername, currPassword);
		// Add user to vector
		users.push_back(currUser);
	}
	// Close file
	dataTestIn.close();

	return users;
}

void PrintMenu()
{
	// Prints the user menu
	cout << "1. Login" << endl;
	cout << "2. Register an account" << endl;
	cout << "3. Exit" << endl;
}


string GetUserInput(string prompt) {
	// Declare var
	string input;

	while (true) { // Loop forever until user enters good input
		try {
			cout << prompt;
			getline(cin, input);
			if (input.find(" ") == string::npos)
			{
				return input; // Return user input
			}
			cout << "Spaces are not allowed. Please try again." << endl;
		}
		catch (...) { // Catch any error
			cout << "Invalid input. Please try again." << endl; // Notify user of bad input
			// Reset input buffer
			cin.clear();
			cin.ignore(250, '\n');
		}
	}
}

int Login(vector<User> users)
{
	/** 
	 * Logging in will find the user matching the information entered
	 * and return the index of the user
	 * The caller will need to set the current user
	*/

	// Get user info
	string username = GetUserInput("Enter your username: ");
	string password = GetUserInput("Enter your password: ");

	// Find user
	string currUsername;
	string currPassword;
	for (int i = 0; i < users.size(); i++)
	{
		currUsername = users[i].GetUsername();
		currPassword = users[i].GetPassword();

		if (username.compare(currUsername) == 0 && password.compare(currPassword) == 0)
		{
			// User was found
			return i;
		}
	}
	// User was not found
	cout << "Invalid account credentials. Try again." << endl;
	return -1;
}

void CreateUser(User user)
{
	// Create file handler
	ofstream data;

	// Open file in append mode
	data.open("data.txt", ios::app);
	// Append data
	data << "\nusername: " << user.GetUsername() << " password: " << user.GetPassword();
	// Close file
	data.close();
	InitializeUsers(); // Reinitialize users after modification
}

bool CheckValidUserInfo(string username, string password, vector<User> users)
{
	// checks if the user info provided is already a user
	for (auto user : users)
	{
		if (username == user.GetUsername() || password == user.GetPassword())
		{
			cout << "Username or password unavailable." << endl;
			return false;
		}
	}
	return true;
}

void Register(vector<User>& users)
{
	// Get new user info
	string username = GetUserInput("Enter your username: ");
	string password = GetUserInput("Enter your password: ");

	// Check if user already exists
	if (CheckValidUserInfo(username, password, users))
	{
		// Create user
		User user = User(username, password);
		CreateUser(user);
	}
}

void DisplayUserMenu(User currUser)
{
	// Greet user
	cout << "Hello, " << currUser.GetUsername() <<  "!" << endl;
}

int main()
{
	// Declare / Initialize vars
	User currUser;
	int currUserLoc = -1;
	string userInput;
	vector<User> users = InitializeUsers();
	bool isUserDone = false;

	// Uncomment this loop to print all users in the data file
	/*
	for (int i = 0; i < users.size(); i++)
	{
		users[i].PrintUser();
		cout << endl;
	}
	*/

	while (!isUserDone)
	{
		// Print menu and get user selection
		PrintMenu();
		userInput = GetUserInput("Enter your selection as a number 1, 2, or 3.\n");

		// If user did not enter a valid selection
		if (!((userInput == "1") || (userInput == "2") || (userInput == "3")))
		{
			cout << "Invalid selection. Please try again." << endl;
			continue;
		}

		// Cast to int and switch
		switch (stoi(userInput))
		{
			case 1:
				// Log out user if anyone was logged in
				currUserLoc = -1;

				// Log in user
				currUserLoc = Login(users); 

				// If user was found
				if (currUserLoc != -1) 
				{
					// Set current user and greet user
					currUser = users[currUserLoc];
					DisplayUserMenu(currUser);
				}
				break;
			case 2:
				// Register a new user
				Register(users);
				break;
			case 3:
				// End program execution
				isUserDone = true;
				break;
			default:
				cout << "Invalid selection" << endl;
		}
	}

	return 1;
}