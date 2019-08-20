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

//linked list for chat members
struct ChatMember{
	char username[40];
	ChatMember *node;
};

//linked list for chat messages
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
		ChatMember *ptr = new ChatMember;
		strcpy(ptr->username, username);
		if (members == NULL){
			ptr->node = NULL;
			members = ptr;
		}	
		else{
			ptr->node = members;
			members = ptr;
		}
	}
	void addAdmin(char username[]){
		ChatAdmin *ptr = new ChatAdmin;
		strcpy(ptr->username, username);
		if (admins == NULL){
			ptr->node = NULL;
			admins = ptr;
		}	
		else{
			ptr->node = admins;
			admins = ptr;
		}
	}
	void addMessage(char message[], char author[]){
		ChatMsgs *ptr = new ChatMsgs;
		strcpy(ptr->author, author);
		strcpy(ptr->message, message);
		if (messages == NULL){
			ptr->node = NULL;
			messages = ptr;
		}	
		else{
			ptr->node = messages;
			messages = ptr;
		}
	}
};

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