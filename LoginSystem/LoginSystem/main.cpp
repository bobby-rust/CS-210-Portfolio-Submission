#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

// Bank account registration system.
// User logs in, can view their balance,
// deposit into or withdraw from their balance

const int WORD_LEN_USER_PASS = 10; // Length of the strings "username: " and "password: " 
const int USERNAME_POS = 0; // position of the word "username" in the string of data representing a user

void print_map(unordered_map<string, string> myMap)
{
	for (const auto& elem : myMap)
	{
		std::cout << elem.first << ", " << elem.second << "\n";
	}
}

unordered_map<string, string> ExtractUserInfo(string data)
{
	// Extracts username and password from a single line of text
	// Ex. ExtractUsernamePassword("username: hello password: world");
	// Returns { "hello", "world" }
	unordered_map<string, string> userInfo;
	string username;
	string password;
	char SPACE = ' ';
	int username_len = 0;

	for (unsigned int i = WORD_LEN_USER_PASS; data[i] != SPACE; i++)
	{
		username_len++;
		username += data[i];
	}
	for (unsigned int j = ((WORD_LEN_USER_PASS * 2) + username_len + 1); j < data.length(); j++)
	{
		password += data[j];
	}

	userInfo.insert({ username, password });

	return userInfo;
}
// fstream& data, string& username, string& password
unordered_map<string, string> GetUser()
{
	// this function opens the data file,
	// finds the user, and returns a 
	// pointer to an unordered map,
	// which should only contain one object, 
	// that is the user's info that was passed
	// if the user was not found, returns null or whatever you do in C++
	unordered_map<string, string> user({});

	ofstream dataTestOut("dataTest.txt");
	dataTestOut << "username bobby " << endl;
	dataTestOut << "password opensesame" << endl;
	dataTestOut.close();

	string userInfo;
	ifstream dataTestIn("dataTest.txt");
	while (getline(dataTestIn, userInfo))
	{
		string userName;
		getline(dataTestIn, userName);
		string passWord;
		getline(dataTestIn, passWord);
		user.insert({ userName, passWord });
	}
	dataTestIn.close();

	return user;
}

void PrintMenu()
{
	cout << "1. Login" << endl;
	cout << "2. Register an account" << endl;
	cout << "3. Exit" << endl;
}

void Login()
{
	string username;
	string password;

	while (1)
	{
		cout << "Enter your username: ";
		cin >> username;

	}
}

int main()
{
	//string userInput;

	//while (1)
	//{
	//	PrintMenu();
	//	cin >> userInput;
	//	if (userInput == "3")
	//	{
	//		break;
	//	}
	//}
	//unordered_map<string, string> userMap = GetUser();
	//
	//print_map(userMap);

	unordered_map<string, string> userInfo = ExtractUserInfo("username: bobby password: opensesame");

	print_map(userInfo);

	return 1;
}