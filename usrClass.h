// Created by Siddharth Parmar
// The user class header file
#include <iostream.h>
#include <string.h>
#include <conio.h>
#include <graphics.h>
#include <fstream.h>

// Function Prototypes
char *checkUser(char []);

//user class
class User {
	char username[40];
	char password[40];
	int age;
	char email[100];
	int pacmanHighScore;
	int pongHighScore;
	char isRegistered[7];
	//for security reasons, this is a private function
	void setPassword(char pwd[]) {
		strcpy(password, pwd);
	}
	public:
	//default constructor
	User() {
		pacmanHighScore = 0;
		pongHighScore = 0;
		strcpy(isRegistered, "False");
	}
	//getter and setter methods
	char *getUsername() {
		return username;
	}
	char *getEmail() {
		return email;
	}
	char *verifyPassword(char pwd[]) {
		if (strcmp(password, pwd) == 0)
			return "True";
		else
			return "False";
	}
	int getAge() {
		return age;
	}
	int getPacmanHighScore() {
		return pacmanHighScore;
	}
	int getPongHighScore() {
		return pongHighScore;
	}
	void setAge(int newAge) {
		age = newAge;
	}
	void setPacmanHighScore(int pacScore) {
		pacmanHighScore = pacScore;
	}
	void setPongHighScore(int score) {
		pongHighScore = score;
	}
	void setEmail(char usrEmail[]) {
		strcpy(email, usrEmail);
	}
	//Register function
	int regUser() {
		char usrname[40], pwd[40], pwdCh = '2';
		//User is already registered, show message and exit
		if (strcmp(isRegistered, "True") == 0) {
			cout<<"\nYou are already registered";
			return 0;
		}
		//Ask for user details
		cout<<"\nEnter username:";
		cin>>usrname;

		//Check file if user with same username  is registered
		char available[] = checkUser(usrname);
		if (strcmp(available, "False") == 0) {
			cout<<"Sorry! Username is taken";
			cout<<"\nType any character to try again";
			getch();
			clrscr();
			regUser();
		}
		
		// Password entry
		int i = 0;
		cout<<"Enter password(39 characters or below):";
		while(i < 39) {
			pwdCh = getch();
			if (pwdCh == 13)
				break;
			cout<<"*";
			pwd[i] = pwdCh;
			i++;
		}
		pwd[i] = '\0';
		//Set username and password
		strcpy(username, usrname);
		setPassword(pwd);
		// Age is set
		cout<<"Enter Age:";
		cin>>age;
		// User email id accepted
		cout<<"Enter email id:";
		cin>>email;
		//set isRegistered to True
		strcpy(isRegistered, "True");
	}
	//Change Password function:
	void changePassword(char existingPwd[]) {
		char newPwd[40], pwdCh;
		char isPwdCorrect = verifyPassword(pwd);
		if (strcmp(isPwdCorrect, "True")) {
			cout<<"\nEnter new password:";
			while(i < 39) {
				pwdCh = getch();
				if (pwdCh == 13)
					break;
				cout<<"*";
				newPwd[i] = pwdCh;
				i++;
			}
			newPwd[i] = '\0';
			setPassword(newPwd);
		}
		else {
			cout<<"\nWrong pa1ssword!";
		}
	}
};

// Function to check if username available, returns "False" if not available
char *checkUser(char usrname[]) {
	fstream user("userobj.txt", ios::in|ios::binary);
	User player;
	while (!user.read((char*)&player, sizeof(player))) {
		// Checks if username is taken
		if (strcmp(user.getUsername, usrname) == 0)
			return "False";
	}
	return "True"
}
