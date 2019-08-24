#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include "usrclass.h"
#include "pacclass.h"
#include <fstream.h>
#include <stdlib.h>
#include <string.h>

//Function prototypes
void drawPac(int);
void drawPong(int);
void graphicsGameIntro(char[]);
void pacmanGame();
void sortPac(Pacman pacm[]);

int main() {
	clrscr();
	// Make a User obj and register it
	User player;
	int counter = player.regUser();
	//write user object to the file
	if (counter == 0){
		fstream user("userobj.txt", ios::app|ios::binary);
		user.write((char *)&player, sizeof(player));
		user.close();
	}
	//introduction
	char activeGame[7] = "pacman";
	graphicsGameIntro(activeGame);
	//as pong not yet complete
	if (strcmp(activeGame,"pong")==0) {
		return 0;
	}

	//play pacman
	pacmanGame(player);
	/*
	Reading from file, disabled till file is rewritten with new objects
	fstream file("pacscore.txt", ios::in|ios::binary);
	Pacman obj;
	while (file.read((char*)&obj, sizeof(obj))){
		cout<<"\nScore:"<<obj.getScore();
	}
	file.close();
	*/
	getch();
	return 0;
}

//Function for implementing the game pacman
void pacmanGame(User player) {

	//introduction
	introduction();

	// request auto detection
	int gdriver = DETECT, gmode, errorcode;

	// initialize graphics and local variables
	initgraph(&gdriver, &gmode, "C:\\TC\\BGI");

	// read result of initialization
	errorcode = graphresult();

	//if an error occurred
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}


	//Display the instruction and map screens
	instructions();
	map();
	//Start game and store pacman object within pac
	Pacman pac = mainGame();
	pac.setName(player.getUsername());
	// clean up
	closegraph();

	/*
	Temporarily commented till new file created
	//Creating objects for file reading
	Pacman pacm[10],obj;
	int i = 0;
	fstream input("pacscore.txt", ios::in|ios::binary);
	while (input.read((char*)&obj, sizeof(obj))){
		pacm[i] = obj;
		i++;
	}
	input.close();

	//pac score is greater than 10th spot of leaderboard, add pac to leaderboard
	if (pac.getScore() > pacm[9].getScore())
	{
		pacm[9] = pac;
	}

	//sort the leaderboard
	sortPac(pacm);

	//write into file
	fstream file("pacscore.txt", ios::out|ios::binary);
	for (i = 0; i < 10; i++) {
		obj = pacm[i];
		file.write((char *)&obj, sizeof(obj));
	}
	//close file
	file.close();
	*/
	//Change back to out soon
	fstream output("pacscore.txt", ios::out | ios::binary);
	output.write((char *)&pac, sizeof(pac));
	output.close();
	fstream input("pacscore.txt", ios::in | ios::binary);
	while(input.read((char *)&pac, sizeof(pac))) {
		cout<<pac.getName()<<" "<<pac.getScore()<<endl;
	}
}

//sorts an array of pac objects in descending order of scores
void sortPac(Pacman pacm[]) {
	Pacman pac;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 9; j++) {
			if (pacm[j].getScore() < pacm[j + 1].getScore()) {
				pac = pacm[j];
				pacm[j] = pacm[j + 1];
				pacm[j + 1] = pac;
			}
		}
	}
}

void drawPac(int active) {

		setcolor(BLACK);
		setfillstyle(SOLID_FILL, BLACK);
		fillellipse(200, 200, 60, 60);
		outtextxy(175, 200, "PACMAN");
	if (active) {
		setcolor(BLACK);
		setfillstyle(SOLID_FILL, YELLOW);
		fillellipse(200, 200, 60, 60);
		outtextxy(175, 200, "PACMAN");
	}
	else {
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, BLACK);
		fillellipse(200, 200, 60, 60);
		outtextxy(175, 200, "PACMAN");
	}
}

void drawPong (int active) {
	int poly[8];
	poly[0] = 400;
	poly[1] = 140;
	poly[2] = 520;
	poly[3] = 140;
	poly[4] = 520;
	poly[5] = 260;
	poly[6] = 400;
	poly[7] = 260;

		setcolor(BLACK);
		setfillstyle(SOLID_FILL, BLACK);
		fillpoly(4, poly);
		outtextxy(445, 200, "PONG");
	if (active) {
		setcolor(BLACK);
		setfillstyle(SOLID_FILL, WHITE);
		fillpoly(4, poly);
		outtextxy(445, 200, "PONG");
	}
	else {
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, BLACK);
		fillpoly(4, poly);
		outtextxy(445, 200, "PONG");
	}
}

void graphicsGameIntro(char activeGame[]) {

	// request auto detection
	int gdriver = DETECT, gmode, errorcode;

	// initialize graphics and local variables
	initgraph(&gdriver, &gmode, "C:\\TC\\BGI");

	// read result of initialization
	errorcode = graphresult();

	//if an error occurred
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}

	//display text
	outtextxy(50, 50, "Toggle by pressing a(to go left) or d(to go right)");
	outtextxy(50, 75, "press enter to select the active game");
	//draw the circle for pacman and square for pong
	drawPac(1);
	drawPong(0);
	//Take user input till the user presses enter, toggle between pacman and pong
	char ch = 1;
	while (ch != 13) {
		ch = getch();
		if (ch == 'a'){
			drawPac(1);
			drawPong(0);
			strcpy(activeGame, "pacman");
		}
		else if (ch == 'd'){
			drawPac(0);
			drawPong(1);
			strcpy(activeGame, "pong");
		}
	}
	cleardevice();
	closegraph();
}
