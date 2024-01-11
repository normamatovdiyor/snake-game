#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

using namespace std;
bool gmov;

const int wd = 40;
const int hg = 40;
int x, y, fx, fy, score;
int tx[100], ty[100];
int lt; //length of tail

enum drt { STOP = 0, LEFT, RIGHT, UP, DOWN };
drt dir;

void setup()     // there are intial condion 
{
	gmov = false;
	dir = STOP;
	x = wd / 2;
	y = hg / 2;
	fx = rand() % wd;
	fy = rand() % hg;
	score = 0;
}

void img()
{
	system("cls");

	for (int i = 0; i < wd+2; i++) // top line 
	{
		cout << "#";
	}

	cout << endl;

	for (int i = 0; i < hg; i++) // borders of box 
	{
		for (int j = 0; j < wd; j++)
		{
			if (j == 0)
				cout << "#";

			if (i == y && j == x)  // when cordinates of snake's head equal to point on the screen, code will display it 
				cout << "O";
			else if (i == fy && j == fx)  // this is for fruit 
				cout << "F";
			else
			{
				bool print = false;

				for (int p = 0; p < lt; p++)
				{
					if (tx[p] == j && ty[p] == i)
					{
						cout << "o";
						print = true;

					}
				}
				if (!print)
					cout << " ";
			}
			

			if (j == wd - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < wd+2; i++) // bottom line 
	{
		cout << "#";
	}

	cout << endl;
}

void input()
{

	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		
		case 'd':
			dir = RIGHT;
			break;
		
		case 'w':
			dir = UP;
			break;
	
		case 's':
			dir = DOWN;
			break;
		
		case 'x':
			gmov = true;
			break;


		}
	}

}

void logic()
{
	int prevx = tx[0];
	int prevy = ty[0];

	int prev2x, prev2y;

	tx[0] = x;
	ty[0] = y;

	for (int i = 1; i < lt; i++)
	{
		prev2x = tx[i];
		prev2y = ty[i];

		tx[i] = prevx;
		ty[i] = prevy;

		prevx = prev2x;
		prevy = prev2y;
	}

	switch (dir)
	{
	
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	
	}

	if (x > wd || x < 0 || y > hg || y < 0)
	{
		gmov = true;
	}

	for (int p = 0; p < lt; p++)
	{
		if (x == tx[p] && y == ty[p])
		{
			gmov = true;
		}
	}

	if (x == fx && y == fy)
	{
		score = score + 1;
		fx = rand() % wd;
		fy = rand() % hg;
		lt++;
	}

}


int main()
{
	setup();

	while (!gmov)
	{
		img();
		input();
		logic();
		Sleep(10);
	}

	system("cls");

	cout << "Your score is " << score;
	return 0;
}



