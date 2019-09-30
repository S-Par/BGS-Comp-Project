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
//Global Variables:
int player1score = 0;
int player2score = 0;


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

#endif