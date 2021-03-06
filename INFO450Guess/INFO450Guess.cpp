// INFO450Guess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
using namespace std;

//Game board dimensions
const int WIDTH = 8;
const int HEIGHT = 8;

void showIntro();
void initBoard(char grid[WIDTH][HEIGHT], bool blank);
void setItem(char grid[WIDTH][HEIGHT], char item, int amount);
int randomize(int range);
void playGame(char grid[WIDTH][HEIGHT], int attempts);

int main()
{
	char board[WIDTH][HEIGHT], response; 
	bool blank = true;
	do 
	{
		showIntro();
		initBoard(board, blank);
		setItem(board, 'G', 5);
		setItem(board, 'B', 1);
		playGame(board, 5); //5-turn gameplay
		initBoard(board, !blank); 
		cout << "\nWant to play again? Enter 'Y': ";
		cin >> response;
	} while (response == 'y' || response == 'Y');
	return 0;
}

//Welcome message
void showIntro()
{
	cout << " *****************************************\n";
	cout << " **             Find Gold!              **\n";
	cout << " **                                     **\n";
	cout << " **       You have 5 guesses,           **\n";
	cout << " **         5 pieces of Gold            **\n";
	cout << " **             and 1 bomb.             **\n";
	cout << " **                                     **\n";
	cout << " **            Good Luck!               **\n";
	cout << " *****************************************\n\n";
}

//This initializes the array and prints the game board in begginning or end state
void initBoard(char grid[WIDTH][HEIGHT], bool blank)
{
	int row, col;
	cout << "     "; 
	for (col = 0; col < WIDTH; col++)
	{
		cout << col + 1 << "  ";
	}
	cout << "\n    ";
	for (col = 0; col < WIDTH; col++)
	{
		cout << "___";
	} 
	if (blank) //Starting board
	{
		for (row = 0; row < HEIGHT; row++)
		{
			cout << endl << row + 1 << " |  ";
			for (col = 0; col < WIDTH; col++)
			{
				grid[col][row] = ' '; 
				cout << "?  "; 
			}
		}
	}
	else //End board
	{
		for (row = 0; row < HEIGHT; row++)
		{
			cout << endl << row + 1 << " |  ";
			for (col = 0; col < WIDTH; col++)
			{
				cout << grid[col][row] << "  "; 
			}
		}
	}
	cout << endl;
}

//This sets the item in the game board
void setItem(char grid[WIDTH][HEIGHT], char item, int amount)
{
	int randCol, randRow;

	for (int i = 0; i < amount; i++)
	{
		do 
		{
			randRow = randomize(HEIGHT);
			randCol = randomize(WIDTH);
		} while (grid[randCol][randRow] != ' ');
		grid[randCol][randRow] = item;
		
	}
}

//Random integer generator used in setItem.
int randomize(int range)
{
	static int check = 0;
	if (check == 0)
	{
		srand(time(NULL));
	}
	check++;
	return rand() % range;
}

//Keeps track of player guesses and points and prints the end message
void playGame(char grid[WIDTH][HEIGHT], int attempts)
{
	int row, col;
	int points = 0;
	while (attempts > 0) 
	{
		cout << "\nYou have " << attempts << " attempts left.\n\nEnter column: ";
		cin >> col;
		cout << "Enter row: ";
		cin >> row;
		if (grid[(col - 1) % WIDTH][(row - 1) % WIDTH] == 'G')
		{
			cout << "You found Gold! Plus you get an extra turn.";
			grid[(col - 1) % WIDTH][(row - 1) % WIDTH] = 'F'; 
			points++;
			//No change to attempts means an extra turn
		}
		else if (grid[(col - 1) % WIDTH][(row - 1) % WIDTH] == 'B')
		{
			cout << "A bomb! Game over...";
			attempts = 0;
		}
		else
		{
			cout << "Missed! Too bad...";
			attempts--;
		}
	}
	cout << "\n\n *****************************************";
	cout << "\n **              GAME OVER              **";
	cout << "\n **                                     **";
	cout << "\n **         Your final score is         **";
	cout << "\n **           " << points << " POINTS                 **";
	cout << "\n **                                     **";
	cout << "\n **                                     **";
	cout << "\n **      View the game board below      **";
	cout << "\n *****************************************\n\n";
}



