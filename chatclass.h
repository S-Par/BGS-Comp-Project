// Created by Siddharth Parmar
// The chat class header file
#ifndef __chatclass_h
#define __chatclass_h
#include <iostream.h>
#include <fstream.h>
#include <stdlib.h>
#include "usrclass.h"

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
	// add functions
	//add lines of code to add chat to user object
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
		//add chat to user
		User obj;
		fstream usrfile("userobj.txt", ios::in | ios::bin);
		while (usrfile.read((char *)&obj, sizeof(obj))) {
			if (strcmp(obj.getUsername(), username) == 0){
				obj.addChat(atoi(identifier));
			}
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
		//add chat to user
		User obj;
		fstream usrfile("userobj.txt", ios::in | ios::bin);
		while (usrfile.read((char *)&obj, sizeof(obj))) {
			if (strcmp(obj.getUsername(), username) == 0){
				obj.addChat(atoi(identifier));
			}
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

	// remove functions
	void removeMember(char username[]){
		ChatMember *ptr1 = members, *ptr2 = members;
		while (strcmp(ptr1->username, username) != 0) {
			ptr1 = ptr1->node;
		}
		if (ptr1 == members) {
			members = members->node;
			delete ptr1;
			
		}
		else {
			while (ptr2->node != ptr1) {
				ptr2 = ptr2->node; 
			}
			ptr2->node = ptr1->node;
			delete ptr1;
		}
		//remove chat from user
		User obj;
		fstream usrfile("userobj.txt", ios::in | ios::bin);
		while (usrfile.read((char *)&obj, sizeof(obj))) {
			if (strcmp(obj.getUsername(), username) == 0){
				obj.removeChat(atoi(identifier));
			}
		}
	}

	void removeAdmin(char username[]){
		ChatAdmin *ptr1 = admins, *ptr2 = admins;
		while (strcmp(ptr1->username, username) != 0) {
			ptr1 = ptr1->node;
		}
		if (ptr1 == admins) {
			admins = admins->node;
			delete ptr1;
			
		}
		else {
			while (ptr2->node != ptr1) {
				ptr2 = ptr2->node; 
			}
			ptr2->node = ptr1->node;
			delete ptr1;
		}
		//remove chat from user
		User obj;
		fstream usrfile("userobj.txt", ios::in | ios::bin);
		while (usrfile.read((char *)&obj, sizeof(obj))) {
			if (strcmp(obj.getUsername(), username) == 0){
				obj.removeChat(atoi(identifier));
			}
		}
	}

	// promote user function
	void promoteMember(char username[]) {
		removeMember(username);
		addAdmin(username);
	}

	// demote user function
	void demoteAdmin(char username[]){
		removeAdmin(username);
		addMember(username);
	}
	//displays the messages
	void displayMessages(int startMsg, int lastMsg) {
		startMsg--;
		lastMsg--;
		int i = 0;
		ChatMsgs *ptr = messages;
		while (ptr && startMsg < lastMsg + 1) {
			if (i == startMsg) {
				cout<<ptr->message;
				cout<<"\nBy : "<<ptr->author<<endl;
				startMsg++;
			}
			i++;
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
