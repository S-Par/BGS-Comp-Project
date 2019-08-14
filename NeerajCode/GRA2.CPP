#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<process.h>
#include<stdlib.h>
#include<dos.h>
#include<ctype.h>
#include<stdio.h>

char msg[80];


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

int checkCol(int num)
{

 if(num==1)  //right
{

if(y1<bally && bally<y1+100)
  return 1;
else
 return 0;

}

else if(num==2)
{
 if(y2<bally && bally<y2+100)
  return 1;
 else
 return 0;

}

}


void drawball(int color)
{

	setcolor(color);
	setlinestyle(SOLID_LINE, 1,1);
	setfillstyle(SOLID_FILL, BLACK);
	circle(ballx,bally,10);
}

void reset()
{
    setcolor(WHITE);
	setlinestyle(SOLID_LINE,1,1);
		setfillstyle(SOLID_FILL, WHITE);
	rectangle(0,0,635,480);

    circle(ballx,bally, 10);

    //  bar(320,250,340,260);

    /* draw the bar */
    bar(620, y1, 625,y1+100 );

    bar(10,y2,15,y2+100);
    setcolor(WHITE);
    setlinestyle(DASHED_LINE,0,3);
    line(300,0,300,500);


}








int main()
{
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;

	int key=0;
	initgraph(&gdriver, &gmode, "C:\\TC\\BGI");

	/* select the text style, direction, and size */
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 8);
	setcolor(10);
    /* create a message string */
    sprintf(msg, "PONG", i);

    /* output the message */
    outtextxy(85,25, msg);

    setcolor(11);
    settextstyle(GOTHIC_FONT, HORIZ_DIR, 5);
    sprintf(msg, "*Rules:");
    outtextxy(10,120, msg);

	/*rules output*/

	setcolor(14);
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
	sprintf(msg,"->Player 2 press up arrow to move the bar up  ");
	outtextxy(10,175,msg);
/*
  setcolor(14);
  settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
  sprintf(msg,"snake.");
  outtextxy(40,205,msg);   */

	setcolor(14);
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
	sprintf(msg,"->Press Down arrow to move the bar down ");
	outtextxy(10,245,msg);
/*
  setcolor(14);
  settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
  sprintf(msg,"snake.");
  outtextxy(40,275,msg);    */

	setcolor(14);
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
	sprintf(msg,"->Player 1 press W arrow to move the bar up ");
	outtextxy(10,385,msg);
/*
  setcolor(14);
  settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
  sprintf(msg,"you lose the game.");
  outtextxy(40,415,msg);*/
	setcolor(14);
	settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
	sprintf(msg,"-> press S arrow to move the bar up ");
	outtextxy(10,315,msg);

/*  setcolor(14);
  settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
  sprintf(msg,"increase in size");
  outtextxy(40,345,msg);       */

	delay(700);
	cleardevice();



/* initialize graphics and local
variables */
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
	circle(ballx, bally, 10);
    rectangle(0,0,635,480);

	bar(620, y1, 625,y1+100 );
    bar(10,y2,15,y2+100);
    setlinestyle(DASHED_LINE,0,3);
    line(300,0,300,500);

    while(1){
		drawball(0);

		ballx+=velx;
		bally+=vely;

		if(ballx>610 && ballx<625){
			if(checkCol(1)==1)
				velx= -velx;


		}
		else if(ballx<25 && ballx>15){
			if(checkCol(2)==1)
				velx= -velx;

		}
		else if(ballx>625){
		velx+=velx;
		delay(100);
		ballx=tempballx;
		bally=tempbally;
			setfillstyle(SOLID_FILL, BLACK);
			bar(0,0,getmaxx(),getmaxy());
		  y1=tempy1;
		  y2=tempy2;


		velx=tempx;
		reset();
		getch();
		}
		else if(ballx<15){
		velx+=velx;
		delay(100);
		ballx=tempballx;
		bally=tempbally;
			setfillstyle(SOLID_FILL, BLACK);
			bar(0,0,getmaxx(),getmaxy());
		   y1=tempy1;
		   y2=tempy2;

		velx=tempx;
		reset();
		getch();
	       }
		if(bally<10){
			vely= -vely;
		}

		if(bally>460){
			vely= -vely;
		}
		drawball(15);
		delay(40);
		reset();
		while(kbhit()){
			key=getch();
			switch(key){
				case 72:
					if(y1!=10){
						setfillstyle(SOLID_FILL, BLACK);
						bar(620, y1, 625,y1+100 );
						y1=y1-10;
						setfillstyle(SOLID_FILL, WHITE);
						bar(620, y1, 625,y1+100 );
					}
					break;
				case 80:
					if(y1!=370){
						setfillstyle(SOLID_FILL, BLACK);
						bar(620, y1, 625,y1+100 );
						y1=y1+10;
						setfillstyle(SOLID_FILL, WHITE);
						bar(620, y1, 625,y1+100 );
					}
					break;
				case 119:
					if(y2!=10){
						setfillstyle(SOLID_FILL, BLACK);
						bar(10, y2, 15,y2+100 );
						y2=y2-10;
						setfillstyle(SOLID_FILL, WHITE);
						bar(10, y2, 15,y2+100 );
					}
					break;
				case 115:
					if(y2!=370){
						setfillstyle(SOLID_FILL, BLACK);
						bar(10, y2, 15,y2+100 );
						y2=y2+10;
						setfillstyle(SOLID_FILL, WHITE);
						bar(10, y2, 15,y2+100 );
					}
					break;
				case 27: exit(0);
			}
		}
	}
	return 0;
}
