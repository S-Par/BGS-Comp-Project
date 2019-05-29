#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include "pacclass.h"
#include <fstream.h>
#include <stdlib.h>
#include <string.h>

void drawPac(int);
void drawPong(int);
char *graphicsGameIntro();
void pacmanGame();

int main() {
	//play pacman
	pacmanGame();
	return 0;
}

//Function for implementing the game pacman
void pacmanGame() {



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

	char *activeGame = graphicsGameIntro();
	if (strcmp(activeGame,"pong")==0)
	{
		exit(0);
	}
	//Display the introduction and map screens
	instructions();
	map();
	//Start game and store pacman object within pac
	Pacman pac = mainGame();

	// clean up
	closegraph();

	//write into files
	fstream file("pacmanScores.txt",ios::out|ios::binary);
	file.write((char *)&pac,sizeof(pac));
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

char *graphicsGameIntro() {
	outtextxy(50, 50, "Toggle by pressing a(to go left) or d(to go right)");
	outtextxy(50, 75, "press enter to select the active game");
	drawPac(1);
	drawPong(0);
	char ch = 1, activeGame[7] = "pacman";
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
	return activeGame;
}
