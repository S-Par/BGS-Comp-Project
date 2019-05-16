#include <iostream.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>

//Character class is super class for pacman class and ghost class
class character {
	protected:
	int xco;
	int yco;
	//When this value changes, it is reflected for all the ghosts and pacman
	static int powerPellet;
	public:
	int getXco(){
		return xco;
	}
	int getYco(){
		return yco;
	}
	int getPowerPellet(){
		return powerPellet;
	}
	int setXco(int newXco){
		xco = newXco;
	}
	int setYco(int newYco){
		yco = newYco;
	}
	int setPowerPellet(int newPellet){
		powerPellet = newPellet;
	}
};

//Class for pacman objects, derived class of Character
class Pacman: public Character{
	int score;
	int life;
	public:
	//Draws pacman with direction as parameter
	void pacDraw(char direction);
	//passes direction as parameter and updates Xco and Yco of pacman
	void pacMove(char direction);
};
