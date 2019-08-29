#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Function prototypes
void startGraphicsMode();
void drawPac(int);
void drawPong(int);
void graphicsGameIntro(char[]);
void intro();

int main(){
    //graphicsGameIntro("pacman");
    intro();
    //getch();
    return 0;
}

//Overall introduction
void intro(){
	startGraphicsMode();
	moveto(250,150);
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	outtext("Welcome to ");
	moverel(120, 0);
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
	outtext("ElEMENT");
	getch();
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


