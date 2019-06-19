//The database part of the project
#include <iostream.h>
#include <string.h>
#include <conio.h>
#include <fstream.h>

//user class
class User {
	char username[40];
	char password[40];
	int age;
	int pacmanHighScore;
	int galagaHighScore;
	char isRegistered[7];
	//for security reasons, this is a private function
	void setPassword(char pwd[]) {
		strcpy(password, pwd);
	}
	public:
	//default constructor
	User() {
		pacmanHighScore = 0;
		galagaHighScore = 0;
		strcpy(isRegistered, "False");
	}
	//getter and setter methods
	char *getUsername() {
		return username;
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
	int getGalagaHighScore() {
		return galagaHighScore;
	}
	void setAge(int newAge) {
		age = newAge;
	}
	void setPacmanHighScore(int pacScore) {
		pacmanHighScore = pacScore;
	}
	void setGalagaHighScore(int score) {
		galagaHighScore = score;
	}
	//Register function
	void regUser() {
		char usrname[40], pwd[40], pwdCh = '2';
		//User is already registered, show message and exit
		if (strcmp(isRegistered, "True") {
			cout<<"\nYou are already registered";
			return
		}
		//Ask for user details
		cout<<"\nEnter username:";
		cin>>usrname;
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
		setUsername(usrname);
		setPassword(pwd);

		cout<<"\nEnter Age:";
		cin>>age;
		//set isRegistered to True
		strcpy(isRegistered, "True");
	}
	//Change Password function:
	void changePassword() {
		char pwd[40], pwdCh;
		cout<<"\nEnter your existing password:";
		while(i < 39) {
			pwdCh = getch();
			if (pwdCh == 13)
				break;
			cout<<"*";
			pwd[i] = pwdCh;
			i++;
		}
		pwd[i] = '\0';
		char isPwdCorrect = verifyPassword(pwd);
		if (strcmp(isPwdCorrect, "False"))
			return ;
		char newPwd[40];
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
};
