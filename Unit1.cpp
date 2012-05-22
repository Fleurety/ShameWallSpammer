//---------------------------------------------------------------------------
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define BROWN			6
#define LIGHTGRAY		7
#define DARKGRAY		8
#define LIGHTBLUE		9
#define LIGHTGREEN		10
#define LIGHTCYAN		11
#define LIGHTRED		12
#define LIGHTMAGENTA	13
#define YELLOW			14
#define WHITE			15
#define BLINK			128
//---------------------------------------------------------------------------

#pragma argsused
int FieldSize = 7;
int Scaler = 3;
int viewx  = (80 - 7*Scaler)/2;
int viewy  = (25 - 7*Scaler)/2;


bool selected = false;
int  selx = 3;
int  sely = 4;
char field[7][7] = {'w','w','w','w','w','w','w',
					'w','?','?','w','?','?','w',
					'w','?','?','s','?','?','w',
					'w','w','s','w','s','w','w',
					'w','?','?','s','?','?','w',
					'w','?','?','w','?','?','w',
					'w','w','w','w','w','w','w'};
//---------------------------------------------------------------------------
void ShowField(int x, int y)
{
	for (int i = 0; i < FieldSize; i++)
	{
		for (int j = 0; j < FieldSize; j++)
		{
			for (int k = 0; k < Scaler; k++)
			{
				for (int l = 0; l < Scaler; l++)
				{
					char smb = 0xDB;
					int delta = 0;
					if (selx == i && sely == j)
					{
						delta = BLINK;
						if (selected)
							smb = 0xFA;
					}

					gotoxy(x+i*Scaler+k, y+j*Scaler+l);
					switch(field[i][j])
					{
						case 'w':	textcolor(WHITE + delta);
									cprintf("%c", smb);   // Wall
									break;
						case 's':   textcolor(BLACK + delta);
									cprintf("%c", ' ');   // Space
									break;
						case 'r':   if (delta)
										textcolor(LIGHTRED);
									else
										textcolor(RED);
									cprintf("%c", smb);  // Block
									break;
						case 'g':   if (delta)
										textcolor(LIGHTGREEN);
									else
										textcolor(GREEN);
									cprintf("%c", smb);  // Block
									break;
						case 'b':   if (delta)
										textcolor(LIGHTCYAN);
									else
										textcolor(BLUE);
									cprintf("%c", smb);  // Block
									break;
						case 'y':   if (delta)
										textcolor(LIGHTCYAN);
									else
										textcolor(CYAN);
									cprintf("%c", smb);  // Block
									break;
					}
				}
			}
		}
	}
}
//---------------------------------------------------------------------------
void StartRandom()
{
	int pos = 0;
	char a[16];
	char b[16]={'r','r','r','r','g','g','g','g','b','b','b','b','y','y','y','y'};

	randomize();
	while (1)
	{
		int i = random(16);
		if (b[i]!=' ')
		{
			a[pos] = b[i];
			b[i] = ' ';
			pos++;
		}
		if (pos == 16)
			break;
	}
	// перенос данныех на игровое поле
	// section 1
	field[1][1] = a[0];
	field[1][2] = a[1];
	field[2][1] = a[2];
	field[2][2] = a[3];
	// section 1
	field[4][1] = a[4];
	field[4][2] = a[5];
	field[5][1] = a[6];
	field[5][2] = a[7];
	// section 1
	field[1][4] = a[8];
	field[2][4] = a[9];
	field[1][5] = a[10];
	field[2][5] = a[11];
	// section 1
	field[4][4] = a[12];
	field[4][5] = a[13];
	field[5][4] = a[14];
	field[5][5] = a[15];
}
//---------------------------------------------------------------------------
bool Check()
{
	int cnt = 0;
	// section 1
	if (field[1][1] == field[1][2] && field[1][1] == field[2][1] && field[1][1] == field[2][2])
		cnt++;
	// section 2
	if (field[4][1] == field[4][2] && field[4][1] == field[5][1] && field[4][1] == field[5][2])
		cnt++;
	// section 3
	if (field[1][4] == field[2][4] && field[1][4] == field[1][5] && field[1][4] == field[2][5])
		cnt++;
	// section 4
	if (field[4][4] == field[4][5] && field[4][4] == field[5][4] && field[4][4] == field[5][5])
		cnt++;

	// check
	if (cnt == 4)
		return true;
	else
		return false;
}
//---------------------------------------------------------------------------
void main()
{
	clrscr();
	StartRandom();
	ShowField(viewx, viewy);

	while(1)
	{
		bool keyused = false;
		int key = getch();

		int newx;
		int newy;

		switch(key)
		{
			case 27:    // Esc
						clrscr();
						printf ("Thank's for playing\r\n\r\n");
						exit(0);
						break;
			case 32:	// Space
						if (field[selx][sely]!= 's')
							if (selected)
								selected = false;
							else
								selected = true;

						keyused = true;
						break;
			case 75:
			case 97:    // Left
						newx = selx-1;
						newy = sely;
						keyused = true;
						break;
			case 77:
			case 100:   // right
						newx = selx+1;
						newy = sely;

						keyused = true;
						break;
			case 72:
			case 119:   // up
						newx = selx;
						newy = sely-1;

						keyused = true;
						break;
			case 80:
			case 115:   // down
						newx = selx;
						newy = sely+1;

						keyused = true;
						break;
		}
		// Отображение действия
		if (keyused)
		{
			if (selected)
			{
				if (field[newx][newy] == 's')
				{
					field[newx][newy] = field[selx][sely];
					field[selx][sely]   = 's';
					selx = newx;
					sely = newy;
				}
			}
			else
			{
				if (field[newx][newy] != 'w')
				{
					selx = newx;
					sely = newy;
				}
			}

			ShowField(viewx, viewy);
		}
		// Проверка выигрыша
		if (Check())
		{
			clrscr();
			gotoxy(36, 12);
			cprintf("You WIN!");
			getch();
			exit(1);
		}
	}
}
//---------------------------------------------------------------------------
