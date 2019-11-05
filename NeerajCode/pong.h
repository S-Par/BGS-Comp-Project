// The Pong header file
#ifndef __chatclass_h
#define __chatclass_h
#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <process.h>
#include <stdlib.h>
#include <dos.h>
#include <ctype.h>
#include <stdio.h>

//Constants:
const int startPaddleTopYCo = 200;
const int leftPaddleXco = 10;
const int rightPaddleXco = 620;
const int startBallYCo = 250;
const int startBallXCo = 300;
const int RadBall=10;
//Global Variables:
int player1score = 0;
int player2score = 0;
int ntempx=-4;
int velx=4;
int tempx=4;
int vely=-4;
char score[1]="1";
int tempballx=300;

int tempbally=250;

class Paddle{
    //xCo is x coordinate of the left edge of the paddle
    //thickness is 5
    int xCo;
    int topYCo;
    // bottom y coordinate is topYCo + 100
    int bottomYCo;
    public:
    // Constructor for the Paddle, takes xCo as a parameter
    Paddle(int startXCo);
    // Destructor
    ~Paddle();
    // Checks if ball hits the paddle, if it does, returns 1 else returns 0
    int isColliding(int ballXCo, int ballYCo);
    // Draws the paddle at the current coordinates
    void drawPaddle();
    // Erases the paddle at the current coordinates
    void erasePaddle();
    // Moves the paddle up
    void moveUp();
    // Moves the paddle down
    void moveDown();
	//sets the y-coordinate
	void setY(int newY){
		topYCo = newY;
		bottomYCo = topYCo + 100;
	}
};

class Ball{
	// x coordinate of the ball
	int BallXCo;
	// y coordinate of the ball
	int BallYCo;
	// x component of velocity
	int velX;
	// y component of velocity
	int velY;
	public:
	//Constructer for ball
	Ball();
	//Destructor
	~Ball();
	//Draws the ball at current coordinates
	void drawBall();
	//Erases the ball
	void eraseBall();
	//Moves the ball;
	void MoveBall();
	// Returns BallX
	int getX(){
		return BallXCo;
	}
	// Returns BallY
	int getY(){
		return BallYCo;
	}
	// Sets the x-coordinate
	void setX(int newX){
		BallXCo = newX;
	}
	// Sets the y-coordinate
	void setY(int newY){
		BallYCo = newY;
	}
	// Sets velX
	void setVelX(int newVelX){
		velX = newVelX;
	}
	//Sets velY
	void setVelY(int newVelY){
		velY = newVelY;
	}
};

Paddle::Paddle(int startXCo){
    xCo = startXCo;
    topYCo = startPaddleTopYCo;
    bottomYCo = topYCo + 100;
}

Paddle::~Paddle(){

}

int Paddle::isColliding (int ballXCo, int ballYCo){
    if (ballXCo + 10 >= xCo && ballXCo + 10 <= xCo + 15){
		if (ballYCo >= topYCo && ballYCo <= bottomYCo){
			return 1;
		}
    }
    return 0;
}

void Paddle::drawPaddle(){
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    bar(xCo, topYCo, xCo + 5, bottomYCo);
}

void Paddle::erasePaddle(){
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    bar(xCo, topYCo, xCo + 5, bottomYCo);
}

void Paddle::moveDown(){
    erasePaddle();
    topYCo += 10;
    bottomYCo += 10;
    drawPaddle();
}

void Paddle::moveUp(){
    erasePaddle();
    topYCo -= 10;
    bottomYCo -= 10;
    drawPaddle();
}


Ball::Ball(){
	BallXCo = startBallXCo;
	BallYCo = startBallYCo;
	velX = 4;
	velY = 4; 
}
Ball::~Ball(){
}
Ball::drawBall(int color){
	setcolor(color);
	setlinestyle(SOLID_LINE, 1, 1);
	setfillstyle(SOLID_FILL, BLACK);
	circle(BallXCo, BallYCo, RadBall);
}
Ball::eraseBall(){
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	circle(BallXCo, BallYCo, RadBall);
}
Ball::moveBall(){
	eraseBall();
	BallXCo+=velx;
	BallYCo+=vely;
	drawBall(0);
}



// Draws the map (but not the paddles or ball)
void drawMap(){
    setcolor(WHITE);
	setlinestyle(SOLID_LINE,1,1);
    //Draws the outer box
	rectangle(0,0,635,480);
    //Draws the centre dashed line
	setlinestyle(DASHED_LINE,0,3);
	line(300,0,300,500);
    // Strings that store score of player 1 and player 2
    char sc1[1], sc2[1];
	//Print scores
	sprintf(sc1, "%d", player1score);
	outtextxy(85, 25, arr1);
	sprintf(sc2, "%d", player2score);
	outtextxy(435, 25, arr2);
}

void reset(Ball &ball, Paddle &leftPad, Paddle &rightPad){
	// Erase ball and paddles
	ball.eraseBall();
	leftPad.erasePaddle();
	rightPad.erasePaddle();
	// Reset each paddle back to start Yco
	leftPad.setY(startPaddleTopYCo);
	rightPad.setY(startPaddleTopYCo);
	// Reset ball to start coordinates
	ball.setX(startBallXCo);
	ball.setY(startBallYCo);
	// Reset velocity to random values 
	//counters
	int a, b;
	a = random(2);
	b = random(2);
	if (a){
		ball.setVelX(4);
	}
	else {
		ball.setVelX(-4);
	}
	if (b){
		ball.setVelY(4);
	}
	else {
		ball.setVelY(-4);
	}
	//Draw everything:
	leftPad.drawPaddle();
	rightPad.drawPaddle();
	ball.drawBall();
}

void Text()
{
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 8);
	setcolor(4);

	outtextxy(195,25, "PONG");

	//Prints the rules
	setcolor(10);
	settextstyle(SIMPLEX_FONT, HORIZ_DIR, 5);
	outtextxy(10,120, "*Rules");

	setcolor(14);
	settextstyle(TRIPLEX_SCR_FONT,HORIZ_DIR,3);

	outtextxy(10, 175, "->Player 1 press W arrow to move the bar up ");
	outtextxy(10, 225, "->Press S arrow to move the bar down");
	outtextxy(10, 275, "->Player 2 press up arrow to move the bar up");
	outtextxy(10, 325, "->Press Down arrow to move the bar down ");
	outtextxy(10, 375, "Press any key to start the game");

}

void Game()
{
	Text();
	getch();
	cleardevice();
	drawMap();
	Paddle LeftPaddle(10);
	Paddle RightPaddle(620);
	Ball ball;
	ball.drawBall();
	LeftPaddle.drawPaddle();
	RightPaddle.drawPaddle();
	while (1)
	{
		ball.MoveBall();
		LeftPaddle.isColliding(ball.getX(), ball.getY());
		RightPaddle.isColliding(ball.getX(), ball.getY());
	}
}

#endif