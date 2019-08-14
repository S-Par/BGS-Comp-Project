// Created by Siddharth Parmar
// The chat class header file
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>

//Function Prototypes
int nextIdentifier();

// Last chat identifier is stored in file usrChatIden.txt
//linked list for chat identifiers
struct ChatIdentifier{
	char identifier[8];
	ChatIdentifier *node;
};

//linked list for chat admins
struct ChatAdmin{
	char username[40];
	ChatAdmin *node;
};

//linked list for chat admins
struct ChatMember{
	char username[40];
	ChatMember *node;
};

//linked list for chat admins
struct ChatMsgs{
	char message[300];
	char author[40];
	ChatMsgs *node;
};

//Chat class
class Chat{
	char identifier[8];
	ChatAdmin *admins;
	ChatMember *members;
	ChatMsgs *messages;
	public:
	Chat(int Identifier){
		admins = NULL;
		members = NULL;
		messages = NULL;
		strcpy(identifier, itoa(Identifier));
	}
	void addMember(char username[]){
		
	}
}

//Function to find next chat identifier
int nextIdentifier(){
	fstream chatFile("usrChatIden.txt", ios::in);
	char ch[8];
	chatFile>>ch;
	int newIdentifier = atoi(ch) + 1;
	strcpy(ch,itoa(newIdentifier));
	chatFile.close();
	fstream chatFile("usrChatIden.txt", ios::out);
	chatFile<<ch;
	chatFile().close();
	return newIdentifier;	
}