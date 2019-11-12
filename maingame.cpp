#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include "usrclass.h"
#include "pacclass.h"
#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include "pong.h"

//Function prototypes
int registerUser(User &player);
int loginUser(User &player);
void pacmanGame(User &player);
void sortPac(Pacman pacm[]);
void startGraphicsMode();
void drawRegister(int);
void drawLogin(int);
void drawPac(int);
void drawPong(int);
void graphicsGameIntro(char[]);
void startScreen(char []);

int main() {
	clrscr();
	start:
	User player;
	int optionReply;
	char option[10] = "register";
	startScreen(option);
	if (strcmp(option, "register") == 0) {
		optionReply = registerUser(player);
		if (optionReply == 1){
			goto start;
		}
	}
	else{
		optionReply = loginUser(player);
		if (optionReply == 1){
			goto start;
		}
	}
	/*
	fstream userfile("userobj.txt", ios::in|ios::binary);
	while (userfile.read((char *)&player, sizeof(player))){
		cout<<player.getUsername()<<endl;
		getch();
	}
	userfile.close();
	*/
	//introduction
	char activeGame[7] = "pacman";
	graphicsGameIntro(activeGame);
	//as pong not yet complete
	if (strcmp(activeGame,"pong")==0) {
		Game();
	}
	else{
		//play pacman
		pacmanGame(player);
	}
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
void pacmanGame(User &player) {

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
	fstream output("pacscore.txt", ios::app | ios::binary);
	output.write((char *)&pac, sizeof(pac));
	output.close();

	fstream input("pacscore.txt", ios::in | ios::binary);
	while(input.read((char *)&pac, sizeof(pac))) {
		cout<<pac.getName()<<" "<<pac.getScore()<<endl;
	}
	input.close();
}

// Registers a user object, if unsuccessful returns 1
int registerUser(User &player){
	int counter = player.regUser();
	// If counter = 0, user registered successfully
	// Write user obj to file
	if (counter == 0){
		fstream user("userobj.txt", ios::app|ios::binary);
		user.write((char *)&player, sizeof(player));
		user.close();
		return 0;
	}
	else{
		return 1;
	}
}

//Logs in a user, if unsuccessful returns 1
int loginUser(User &player){
	char usrname[40], pwd[40], pwdCh = '2';
	cout<<"\nEnter username:";
	cin>>usrname;
	// Password entry
	int i = 0;
	cout<<"Enter password(39 characters or below):";
	strcpy(pwd, acceptPassword());
	// Open user file to check
	fstream user("userobj.txt", ios::in|ios::binary);
	int successfulLogin = 0;
	while (user.read((char*)&player, sizeof(player))) {
		// Checks if username is taken
		if (strcmp(player.getUsername(), usrname) == 0) {
			user.close();
			if(strcmp(player.verifyPassword(pwd),"True") == 0){
				cout<<"\nYou have logged in successfully!";
				successfulLogin++;
			}
			break;
		}
	}
	user.close();
	if (successfulLogin == 0){
		cout<<"\nSorry, details didn't match!";
		delay(2000);
		return 1;
	}
}

//Displays the start screen
void startScreen(char activeOp[]){
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
			strcpy(activeOp, "register");
		}
		else if (ch == 's'){
			drawRegister(0);
			drawLogin(1);
			strcpy(activeOp, "login");
		}
		else if (ch == 'q'){
			exit(0);
		}
	}

	cleardevice();
	closegraph();
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

// Draws the register box in start screen
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
		outtextxy(335, 210, "Register");
	}
	else {
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, BLACK);
		fillpoly(4, regPoly);
		outtextxy(335, 210, "Register");
	}
}

// Draws the login box in start screen
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
		outtextxy(330, 260, "Login");
	}
	else {
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, BLACK);
		fillpoly(4, logPoly);
		outtextxy(330, 260, "Login");
	}
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
