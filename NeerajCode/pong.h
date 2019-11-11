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

/*
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
char arr1[12];
char arr[12];
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
	void getTopYCo(){
		return topYCo;
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
	int getVelX(){
		return velX;
	}
	int getVelY(){
		return velY;	
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
	ball.drawBall(15);
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
	int key = 0;
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

		if (LeftPaddle.isColliding(ball.getX(), ball.getY())){
			ball.setVelX(-1*ball.getVelX());
		}
		if (RightPaddle.isColliding(ball.getX(), ball.getY())){
			ball.setVelX(-1*ball.getVelX());
		}
		if(ball.getX()>625){
			ball.setVelX(2*ball.getVelX());
			delay(100);
			reset(ball, LeftPaddle, RightPaddle);
			player1score++;
			if(player1score==5){
				setcolor(WHITE);
				settextstyle(TRIPLEX_FONT,HORIZ_DIR,5);
				outtextxy(180,175,"Player 1 wins");
				getch();
				exit(0);
			}
			reset(ball,LeftPaddle,RightPaddle);
			getch();	
		}
		else if(ball.getX()<15){
			ball.setVelX(2*ball.getVelX());
			delay(100);
			reset(ball, LeftPaddle, RightPaddle);
			player2score++;
			if(player2score==5){
				setcolor(WHITE);
				settextstyle(TRIPLEX_FONT,HORIZ_DIR,5);
				outtextxy(180,175,"Player 2 wins");
				getch();
				exit(0);
			}
			reset(ball,LeftPaddle,RightPaddle);
			getch();	

		}
		if(ball.getY()<10 || ball.getY() > 460){
			ball.setVelY(-1*ball.getVelY())
		}
		//ball.drawBall(15);
		delay(40);
		reset(ball,LeftPaddle,RightPaddle);
		while(kbhit()){
			key=getch();
			if(key == 'W'||key == 'S')
				key = tolower(key);
			switch(key){

				case 72:
					if(RightPaddle.getTopYCo()!=10){
						RightPaddle.moveUp();
					}
					break;

				case 80:
					if(RightPaddle.getTopYCo()!=370){
						RightPaddle.moveDown();
					}	
					break;
				case 119:
					if(LeftPaddle.getTopYCo()!=10){
						LeftPaddle.moveUp();
					}	
					break;
				case 115:
					if(LeftPaddle.getTopYCo()!=370){
						LeftPaddle.moveDown();
					}	
					break;
				case 27:
					exit(0);	
			}	
		}
	}
}
*/

//Global variables
char arr1[12];
char arr2[12];
int p1=-1;
int p2=-1;
int sc1=0;
int sc2=0;
char ec1[1]="1";
int y1=200;
int tempy1=200;
int y2 = 200;
int tempy2=200;
int i=1;
float nvelx=-4;

float ntempx=-4;
float velx=4;
float tempx=4;
float vely=-4;
float ballx=300;
float tempballx=300;
float bally=250;
float tempbally=250;
float linex,liney;

//Function to check if ball hit a paddle, returns 1 if hit else returns 0
int checkCol(int num){
	//right paddle
	if(num == 1) {
		if(y1 < bally && bally < y1 + 100)
			return 1;
		else
			return 0;
	}
	//left paddle
	else if(num == 2){
		if(y2 < bally && bally < y2 + 100)
			return 1;
		else
			return 0;
	}
}

//Draws the ball
void drawball(int color){
	setcolor(color);
	setlinestyle(SOLID_LINE, 1, 1);
	setfillstyle(SOLID_FILL, BLACK);
	circle(ballx, bally, 10);
}

void reset(){
	// Sets color and linestyle for shapes and the fillstyle for the bar(paddle)
	setcolor(WHITE);
	setlinestyle(SOLID_LINE,1,1);
	setfillstyle(SOLID_FILL, WHITE);
	//Draws the outer box
	rectangle(0,0,635,480);
	//Draws the circle
	circle(ballx,bally, 10);

	//Draws the two bars(paddles)
	bar(620, y1, 625,y1+100 );
	bar(10,y2,15,y2+100);

	//Draws the centre dashed line
	setlinestyle(DASHED_LINE,0,3);
	line(300,0,300,500);

	//Print scores
	sprintf(arr1,"%d",sc1);
	outtextxy(85,25,arr1);
	sprintf(arr2,"%d",sc2);
	outtextxy(435,25,arr2);
}








void Game(){
	// request auto detection
	int gdriver = DETECT, gmode, errorcode;

	int key=0;
	initgraph(&gdriver, &gmode, "C:\\TC\\BGI");

	// select the text style, direction, and size
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

	// If user presses a key, clears instructions
	getch();
	cleardevice();

	// Draw map
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	circle(ballx, bally, 10);
	rectangle(0,0,635,480);
	bar(620, y1, 625,y1+100 );
	bar(10,y2,15,y2+100);
	setlinestyle(DASHED_LINE,0,3);
	line(300,0,300,500);

	//Game runs till one player scores 5
	while(1){
		drawball(0);
		/*
		For random directions:
		int a = random(2);
		if (a == 1){
			velx is +ve
		}
		else{
			velx is -ve
		}
		a = random(2);
		if (a == 1){
			vely is +ve
		}
		else{
			vely is -ve
		}
		*/
		ballx+=velx;
		bally+=vely;


		// Ball within paddle x-coordinate, check if it touches the paddle, if yes reverse the ball
		if(ballx>610 && ballx<625){
			if(checkCol(1)==1)
				velx= -velx;
		}
		else if(ballx<25 && ballx>15){
			if(checkCol(2)==1)
				velx= -velx;
		}
		// Ball is touching the end of the map
		if(ballx>625){
			velx+=velx;
			delay(100);
			ballx=tempballx;
			bally=tempbally;
			//erase prev map
			setfillstyle(SOLID_FILL, BLACK);
			bar(0,0,getmaxx(),getmaxy());
			y1=tempy1;
			y2=tempy2;
			velx=tempx;




		    //increment score
			sc1++;
			if(velx<0)
			velx=-1*velx;//changes the server to whoevr loses the point
			if(sc1==5){

				setcolor(WHITE);
				settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
				outtextxy(180,175,"Player 1 wins");
				getch();
				exit(0);
			}
			//reset screen to starting position
			reset();
			getch();

		}
		else if(ballx<15){
			velx+=velx;
			delay(100);
			ballx=tempballx;
			bally=tempbally;
			//erase prev map
			setfillstyle(SOLID_FILL, BLACK);
			bar(0,0,getmaxx(),getmaxy());
			y1=tempy1;
			y2=tempy2;
			velx=tempx;
			//increments scores
			if(velx>0)
			velx=-1*velx;
			sc2++;
			if(sc2==5){
				setcolor(WHITE);
				settextstyle(TRIPLEX_FONT, HORIZ_DIR, 5);
				outtextxy(180,175,"Player 2 wins");
				getch();
				exit(0);
			}
			//reset screen to starting position
			reset();
			getch();

		}

		//Checks if ball is touching the top or bottom of the map, if yes then reverse its direction
		if(bally<10){
			vely= -vely;
		}
		else if(bally>460){
			vely= -vely;
		}
		//Draw the ball
		drawball(15);
		delay(40);
		reset();
		// If a key is pressed, then move paddles
		while(kbhit()){
			key=getch();
			//if 'W' or 'S' key is pressed, convert to lowercase
			if (key == 'W' || key == 'S')
				key = tolower(key);
			switch(key){
				//Up arrow pressed
				case 72:
					if(y1!=10){
						//erase prev bar
						setfillstyle(SOLID_FILL, BLACK);
						bar(620, y1, 625,y1+100 );
						//Change y coordinate and draw new bar
						y1=y1-10;
						setfillstyle(SOLID_FILL, WHITE);
						bar(620, y1, 625,y1+100 );
					}
					break;
				//Down arrow pressed
				case 80:
					if(y1!=370){
						//erase prev bar
						setfillstyle(SOLID_FILL, BLACK);
						bar(620, y1, 625,y1+100 );
						//Change y coordinate and draw new bar
						y1=y1+10;
						setfillstyle(SOLID_FILL, WHITE);
						bar(620, y1, 625,y1+100 );
					}
					break;
				//w key pressed
				case 119:
					if(y2!=10){
						//erase prev bar
						setfillstyle(SOLID_FILL, BLACK);
						bar(10, y2, 15,y2+100 );
						//Change y coordinate and draw new bar
						y2=y2-10;
						setfillstyle(SOLID_FILL, WHITE);
						bar(10, y2, 15,y2+100 );
					}
					break;
				//s key pressed
				case 115:
					if(y2!=370){
						//erase prev bar
						setfillstyle(SOLID_FILL, BLACK);
						bar(10, y2, 15,y2+100 );
						//Change y coordinate and draw new bar
						y2=y2+10;
						setfillstyle(SOLID_FILL, WHITE);
						bar(10, y2, 15,y2+100 );
					}
					break;
				// If esc key pressed, exit program
				case 27: exit(0);
			}
		}
	}
}

#endif