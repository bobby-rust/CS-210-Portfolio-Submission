#include <string>
#include "User.h"
#include <iostream>

using namespace std;

// Username mutator
void User::SetUsername(string t_username) 
{
	username = t_username;
}

// Password mutator
void User::SetPassword(string t_password)
{
	password = t_password;
}

void User::PrintUser()
{
	// Prints info about the user
	cout << "Username: " << this->username << ", Password: " << this->password << endl;
}

// Default constructor
User::User()
{
	username = "";
	password = "";
}

// Parameterized constructor
User::User(string username, string password)
{
	this->username = username;
	this->password = password;
}