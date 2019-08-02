// Created by Siddharth Parmar
// The user class header file
#include <iostream.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <fstream.h>

// Function Prototypes
char *checkUser(char []);
char *acceptPassword();

//linked list for chat identifiers
struct ChatIdentifier{
	char identifier[8];
	ChatIdentifier *node;
};

//user class
class User {
	char username[40];
	char password[40];
	int age;
	char email[100];
	int pacmanHighScore;
	int pongHighScore;
	char isRegistered[7];
	ChatIdentifier *top;
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
		top = NULL;
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
	//pop and push into groups
	void push(int a){
		ChatIdentifier *ptr = new ChatIdentifier;
		strcpy(ptr->identifier,itoa(a));
		if (top == NULL){
			top = ptr;
			top->node = NULL;
		}
		else{
			ptr->node = top;
			top = ptr;
		}
	}
	void pop(int a){
		ChatIdentifier *ptr = top,*ptr1 = top;
		char iden[] = itoa(a);
		while(strcmp(ptr->identifier,iden)!=0){
			ptr = ptr->node;
		}
		while(ptr1->node != ptr){
			ptr1 = ptr1->node;
		}
		ptr1->node = ptr->node;
		delete ptr;
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
		char available[7];
		strcpy(available, checkUser(usrname));
		if (strcmp(available, "False") == 0) {
			cout<<"Sorry! Username is taken";
			cout<<"\nType any character to try again";
			getch();
			clrscr();
			regUser();
		}
		else{
			// Password entry
			int i = 0;
			cout<<"Enter password(39 characters or below):";
			strcpy(pwd, acceptPassword());
			//Set username and password
			strcpy(username, usrname);
			setPassword(pwd);
			// Age is set
			cout<<"\nEnter Age:";
			cin>>age;
			// User email id accepted
			cout<<"Enter email id:";
			cin>>email;
			//set isRegistered to True
			strcpy(isRegistered, "True");
		}
	}

	//Changes the password if correct existing password is entered
	void changePassword() {
		char existingPwd[40], newPwd[40], pwdCh;
		clrscr();
		cout<<"\nYou have chosen to change your password";
		cout<<"\nEnter your existing password: ";
		strcpy(existingPwd, acceptPassword());
		char isPwdCorrect[7];
		strcpy(isPwdCorrect, verifyPassword(existingPwd));
		if (strcmp(isPwdCorrect, "True") == 0) {
			cout<<"\nEnter new password:";
			strcpy(newPwd, acceptPassword());
			setPassword(newPwd);
		}
		else {
			cout<<"\nWrong password!";
		}
	}

	//Public set password function for forgotPassword fn. Only works for the code that was emailed
	void setPassword(int code) {
		if (code == 4872) {
			char pwd[40];
			cout<<"Enter new password: ";
			strcpy(pwd, acceptPassword());
			strcpy(password, pwd);
		}
	}
};

// Function to check if username available, returns "False" if not available
char *checkUser(char usrname[]) {
	fstream user("userobj.txt", ios::in|ios::binary);
	User player;
	while (user.read((char*)&player, sizeof(player))) {
		// Checks if username is taken
		if (strcmp(player.getUsername(), usrname) == 0)
			return "False";
	}
	return "True";
}

// Function to accept a password, returns the pwd string
char *acceptPassword() {
	char pwd[40], pwdCh;
	int i = 0;
	while(i < 39) {
		pwdCh = getch();
		if (pwdCh == 13)
			break;
		cout<<"*";
		pwd[i] = pwdCh;
		i++;
	}
	pwd[i] = '\0';

	return pwd;
}

// returns 0 if all correct, else returns 1
int forgotPassword(User player) {
	cout<<"\nYou have forgetten your password.";
	char usrname[40];
	cout<<"\nEnter your username: ";
	cin>>usrname;

	if (strcmp(player.getUsername(),usrname) != 0) {
		cout<<"\nUsername not found";
		return 1;
	}

	char email[100];
	cout<<"Enter your email id: ";
	cin>>email;

	if (strcmp(email, player.getEmail()) == 0) {
		player.setPassword(4872);
		return 0;
	}
	else {
		cout<<"Wrong email id";
		return 1;
	}

}

//Function to find next chat identifier
int