#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include "usrclass.h"
#include <stdlib.h>

//Function prototypes
void startGraphicsMode();
void drawRegister(int);
void drawLogin(int);
void drawPac(int);
void drawPong(int);
void graphicsGameIntro(char[]);
void intro(char []);

int main(){
    //graphicsGameIntro("pacman");
    intro("register");
    //getch();
    return 0;
}

//Overall introduction
void intro(char activeOp[]){
	User player;
	startGraphicsMode();
	//Moves to x = 250, y = 150 to display title text
	moveto(270,150);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	outtext("Welcome to ");
	moverel(120, 0);

	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
	rectangle(335, 135, 375, 175);
	setcolor(RED);
	outtext("Pr OTON");

	// Login and Register options
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	drawRegister(1);
	drawLogin(0);

	//Instructions for selecting an option
	outtextxy(350, 350, "Toggle by pressing w(to go up) or s(to go down)");
	outtextxy(350, 375, "    Press enter to select the option");

	//Take user input till the user presses enter, toggle between pacman and pong
	char ch = 1;
	while (ch != 13) {
		ch = getch();
		if (ch == 'w'){
			drawRegister(1);
			drawLogin(0);
			strcpy(activeOp, "Register");
		}
		else if (ch == 's'){
			drawRegister(0);
			drawLogin(1);
			strcpy(activeOp, "Login");
		}
	}

	cleardevice();
	closegraph();
}

//Introduction in graphics
void graphicsGameIntro(char activeGame[]) {

	startGraphicsMode();
	/*
	Text styles:
	char *fname[] = { "DEFAULT font",
		"TRIPLEX font",
		"SMALL font",
		"SANS SERIF font",
		"GOTHIC font"
	};
	*/
	//display text
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 1);
	outtextxy(100, 50, "Toggle by pressing a(to go left) or d(to go right)");
	outtextxy(100, 75, "    Press enter to select the active game");
	//draw the circle for pacman and square for pong
	settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
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

//switches on graphics mode
void startGraphicsMode(){
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

void drawRegister(int active) {
	int regPoly[8];
	regPoly[0] = 280;
	regPoly[1] = 200;
	regPoly[2] = 380;
	regPoly[3] = 200;
	regPoly[4] = 380;
	regPoly[5] = 230;
	regPoly[6] = 280;
	regPoly[7] = 230;

	if (active) {
		setcolor(BLACK);
		setfillstyle(SOLID_FILL, WHITE);
		fillpoly(4, regPoly);
		outtextxy(335, 215, "Register");
	}
	else {
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, BLACK);
		fillpoly(4, regPoly);
		outtextxy(335, 215, "Register");
	}
}

void drawLogin(int active) {
	int logPoly[8];
	logPoly[0] = 280;
	logPoly[1] = 250;
	logPoly[2] = 380;
	logPoly[3] = 250;
	logPoly[4] = 380;
	logPoly[5] = 280;
	logPoly[6] = 280;
	logPoly[7] = 280;

	if (active) {
		setcolor(BLACK);
		setfillstyle(SOLID_FILL, WHITE);
		fillpoly(4, logPoly);
		outtextxy(330, 265, "Login");
	}
	else {
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, BLACK);
		fillpoly(4, logPoly);
		outtextxy(330, 265, "Login");
	}
}


