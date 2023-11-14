#include "graphTe.h" // used for graphics
#include <stdio.h>
#include <stdlib.h> // used for files
#include <time.h> // used for time function
#include <string.h>

// the sudoku board is a matrix of 81 of numbers
int board[9][9];

// coordinates of the cursor which are placed outside the board
int cursorX = -1, cursorY = -1;

// a matrix which helps to verify if a position can be filled 
BOOL canWriteBoard[9][9];

// this function loads a sudoku game from a random file and fills both matrixes with the corresponding values  
void generate()
{
	srand(time(0));
	int gameNumber = rand() % 9 + 1;
	char path[100];
	sprintf(path, "assets/%d.sudoku", gameNumber);
	FILE* file = fopen(path, "r");
	int value;
	for(int x = 0; x < 9; x++)
		for(int y = 0; y < 9; y++)
			{
				canWriteBoard[y][x] = TRUE;
				fscanf(file, "%d", &value);
				if(value != 0)
					canWriteBoard[y][x] = FALSE;

				board[y][x] = value;
			}
}

// this function checks if the mouse button is pressed and moves the cursor accordingly
void mouseInput()
{
	if(checkKeyLiveInput(VK_LBUTTON))
	{
		POINT mPos = getMousePosition();
		cursorX = mPos.x / 33;
		cursorY = mPos.y / 33;
	}

	// this function also draws the cursor itself
	line(cursorX * 33, cursorY * 33, cursorX * 33 + 33, cursorY * 33, 4, rgb(255, 0, 0));
	line(cursorX * 33 + 33, cursorY * 33, cursorX * 33 + 33, cursorY * 33 + 33, 4, rgb(255, 0, 0));
	line(cursorX * 33 + 33, cursorY * 33 + 33 , cursorX * 33, cursorY * 33 + 33, 4, rgb(255, 0, 0));
	line(cursorX * 33, cursorY * 33 + 33, cursorX * 33, cursorY * 33, 4, rgb(255, 0, 0));
}

// this function firstly verifies if the cursor is placed on the board and then continues by puttin in the matrix the number introduced
void keyboardInput()
{
	if(cursorX < 0 || cursorY < 0 || cursorX > 9 || cursorY > 9 || !canWriteBoard[cursorX][cursorY]) 
		return;

	int value = 0;
	if(checkKeyLiveInput(0x31))
		value = 1;
	else if(checkKeyLiveInput(0x32))
		value = 2;
	else if(checkKeyLiveInput(0x33))
		value = 3;
	else if(checkKeyLiveInput(0x33))
		value = 3;
	else if(checkKeyLiveInput(0x34))
		value = 4;
	else if(checkKeyLiveInput(0x35))
		value = 5;
	else if(checkKeyLiveInput(0x36))
		value = 6;
	else if(checkKeyLiveInput(0x37))
		value = 7;
	else if(checkKeyLiveInput(0x38))
		value = 8;
	else if(checkKeyLiveInput(0x39))
		value = 9;

	if(value != 0)
		board[cursorX][cursorY] = value;
}

// this function places the picture of the number at the corresponding coordinates
void drawNumber(int value, int x, int y)
{ 
	switch(value)
	{
		case 0:
			break;
		case 1: 
			image(x, y, 33, 33, "assets/1.bmp");
			break;
		case 2:
			image(x, y, 33, 33, "assets/2.bmp");
			break;
		case 3:
			image(x, y, 33, 33, "assets/3.bmp");
			break;
		case 4:
			image(x, y, 33, 33, "assets/4.bmp");
			break;
		case 5:
			image(x, y, 33, 33, "assets/5.bmp");
			break;
		case 6:
			image(x, y, 33, 33, "assets/6.bmp");
			break;
		case 7:
			image(x, y, 33, 33, "assets/7.bmp");
			break;
		case 8:
			image(x, y, 33, 33, "assets/8.bmp");
			break;
		case 9:
			image(x, y, 33, 33, "assets/9.bmp");
			break;
	}
}

// this function takes care of drawing everything to the screen
void render()
{  
    //background
	fill(rgb(100, 100, 100)); // grey
 	rect(0, 0, 297, 297, rgb(245, 245, 245)); // white

    //numbers
 	for(int x = 0; x < 9; x++)
 		for(int y = 0; y < 9; y++)
 			drawNumber(board[x][y], x * 33, y * 33);

 	//lines	
 	for(int x = 0; x < 10; x++)
 	{
 		if(x == 0 || x == 3 || x == 6 || x == 9)
 			line(x * 33, 0, x * 33, 297, 3, rgb(15, 15, 15)); // black
 		else
 			line(x * 33, 0, x * 33, 297, 1, rgb(15, 15, 15)); // black
 	}
 	for(int y = 0; y < 10; y++)
 	{  
 		if(y == 0 || y == 3 || y == 6 || y == 9)
 			line(0, y * 33, 297, y * 33, 3, rgb(15, 15, 15)); // black
 		else 
 			line(0, y * 33, 297, y * 33, 1, rgb(15, 15, 15)); // black
 	}

 	//cursor
 	mouseInput();

 	// displays on screen
  	display();
}

int main()
{
	initHost(); // sets the console on graphic mode
	setWindowTitle("sudoku");
	setWindowSize(350, 350);
	update(); // updates the memory canvas to the new window size

	// start screen
	image(-20, 0, 350, 350, "assets/start.bmp");
	display();
	forceInput();

	generate();

	// do something every frame
	while(1)
	{	
		render();
		keyboardInput();
	}

	releaseHost(); // frees up the memory used by graphTe.h
}
