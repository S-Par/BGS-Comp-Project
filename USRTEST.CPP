//Test file for usrclass.h

#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include "usrclass.h"

int main(){
	clrscr();
	User player;
	player.regUser();
	player.changePassword();
	forgotPassword(player);
	getch();
	return 0;
}