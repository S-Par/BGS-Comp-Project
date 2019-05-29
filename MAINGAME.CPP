#include <iostream.h>
#include <graphics.h>
#include <conio.h>
#include "pacclass.h"
#include <fstream.h>

int main()
{
	//create introduction screen of pacman
	introduction();
	// request auto detection
	int gdriver = DETECT, gmode, errorcode;

	// initialize graphics and local variables
	initgraph(&gdriver, &gmode, "C:\\TC\\BGI");

	// read result of initialization
	errorcode = graphresult();
	// an error occurred
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
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
	return 0;
}
