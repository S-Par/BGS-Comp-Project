// Created by Siddharth Parmar
// The user class header file
// Email functionality using smtp, smtp functionality from Microsoft ATL server (atlsmtpconnection.h)
#include <iostream.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <fstream.h>
#include "atlsmtpconnection.h"

// Function Prototypes
char *checkUser(char []);
char *acceptPassword();
int forgotPassword();

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
		strcpy(pwd, acceptPassword());
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

	//Changes the password if correct existing password is entered
	void changePassword(char existingPwd[]) {
		char existingPwd[40], newPwd[40], pwdCh;
		cout<<"\nEnter your existing password";
		strcpy(existingPwd, acceptPassword());
		char isPwdCorrect = verifyPassword(existingPwd);
		if (strcmp(isPwdCorrect, "True")) {
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
	while (!user.read((char*)&player, sizeof(player))) {
		// Checks if username is taken
		if (strcmp(user.getUsername, usrname) == 0)
			return "False";
	}
	return "True"
}

// Function to accept a password, returns the pwd string
char *acceptPassword() {
	char pwd[40], pwdCh;
	while(i < 39) {
		pwdCh = getch();
		if (pwdCh == 13)
			break;
		cout<<"*";
		pwd[i] = pwdCh;
		i++;
	}
	pwd[i] = '\0';

	return pwd
}

//forgotPassword function to reset password using an email to the user
// returns 0 if all correct, else returns 1
int forgotPassword() {
	cout<<"\nYou have forgetten your password.";
	char usrname[40];
	cout<<"\nEnter your username: ";
	cin>>usrname;
	int flag = 0;

	fstream fin("userobj.txt", ios::in|ios::binary);
	User player;
	while (!fin.read((char *)&player, sizeof(player))) {
		if (strcmp(usrname, player.getUsername()) == 0) {
			flag++;
			break;
		}
	}
	if (flag == 0) {
		cout<<"Username not found";
		return 1;
	}

	char email[] = player.getEmail();

	CAuthSMTPConnection SMTP(587,"smtp.gmail.com","bgsarcade@gmail.com","HelloThere!");
	if (SMTP.Connect())	{
		// Create the text email message
		CMimeMessage msg;
		msg.SetSubject(csTFTDHdr);
		msg.SetSender("bgsarcade@gmail.com");
		msg.SetSenderName("BGS Comp Arcade");
		msg.AddRecipient(email);
		msg.AddText("You seem to have forgetten your password. Type the code: ");
		int code = random(1000);
		msg.AddText((char *)code);
		// Send the email message
		if (SMTP.SendMessage(msg))
			cout<<"\nSent Mail";
		else {
			cout<<"Mail not sent";
			return 1;
		}
	}
	else
	{
		cout<<"Can't connect to mail server";
		return 1;
	}
	int usrEnterredCode; 
	cout<<"\nEnter the code: ";
	cin>>usrEnterredCode;
	if (usrEnterredCode == code) {
		player.setPassword(4872);
		return 0;
	}
	cout<<"Incorrect code entered.";
	return 1;
}