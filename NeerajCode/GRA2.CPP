#include <iostream.h>
#include <conio.h>
#include <graphics.h>
#include <process.h>
#include <stdlib.h>
#include <dos.h>
#include <ctype.h>
#include <stdio.h>


//Global variables
char arr1[12];
char arr2[12];
int sc1=1;
int sc2=1;
char ec1[1]="1";
int y1=200;
int tempy1=200;
int y2 = 200;
int tempy2=200;
int i=1;
float velx=10;
float tempx=10;
float vely=-10;
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
}








int main(){
	// request auto detection
	int gdriver = DETECT, gmode, errorcode;

	int key=0;
	initgraph(&gdriver, &gmode, "C:\\TC\\BGI");

	// select the text style, direction, and size
	settextstyle(TRIPLEX_FONT, HORIZ_DIR, 8);
	setcolor(10);

	outtextxy(85,25, "PONG");

	//Prints the rules
	setcolor(11);
	settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
	outtextxy(10,120, "*Rules");

	setcolor(14);
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);

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

			//reset screen to starting position

		       reset();
		       //	gotoxy (85,25);
		      //	printf("%d",sc1);
		      // outtextxy(85,25,ec1);
			sprintf(arr1,"%d",sc1);

			outtextxy(85,25,arr1);
		      // outtextxy(435,25,arr2);
			sc1++;
			if(sc1==6)
		       {settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
			outtextxy(getmaxx()/2,getmaxy()/2,"Player 1 wins");
			getch();
			exit(0);    }

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
			//reset screen to starting position
			reset();
				sprintf(arr2,"%d",sc2);
			outtextxy(435,25,arr2);
			outtextxy(85,25,arr1);
			sc2++;
			if(sc2==6)
		       {settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
			outtextxy(getmaxx()/2,getmaxy()/2,"Player 2 wins");
			getch();
			exit(0);    }

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
	return 0;
}
