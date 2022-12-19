#pragma once
#include <string>

using namespace std;

class User {
private:
	// Member variables
	string username;
	string password;

public:
	// Accessors
	string GetPassword() { return this->password; };
	string GetUsername() { return this->username; };
	void PrintUser();

	// Mutators
	void SetUsername(string t_username);
	void SetPassword(string t_password);

	// Constructors
	User();
	User(string t_username, string t_password);
	
};