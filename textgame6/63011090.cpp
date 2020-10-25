#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

void setcolor(int, int);
void setcursor(bool);
void gotoxy(int, int);
void draw_ship(int, int);
void erase_ship(int, int);
void draw_bullet(int, int);
void erase_bullet(int, int);
void text_score(int, int, int);

int main() {

	srand(time(NULL));
	int rand_x[20] = { 0 }, rand_y[20] = { 0 };
	for (int i = 0; i < 20; i++)
	{
		rand_y[i] = rand() % 5 + 2;
	}
	for (int i = 0; i < 20; i++)
	{
		rand_x[i] = rand() % 70 + 10;
	}
	for (int i = 0; i < 20; i++)
	{
		gotoxy(rand_x[i], rand_y[i]);
		printf("*");
	}

	int score = 0;
	char ch = 'null';
	int x = 38, y = 20;
	int pt = 3;
	int bullet[5] = { 0 };
	int count_bullet1 = 0, checkmax_bullet = 0, bullet_x[5], bullet_y[5];
	
	draw_ship(x, y);
	setcursor(0);
	do {
		if (_kbhit()) {
			ch = _getch();
			
			if (ch == ' ' && checkmax_bullet < 5)
			{
				bullet[count_bullet1 % 5] = 1;
				bullet_x[count_bullet1 % 5] = x + 2;
				bullet_y[count_bullet1 % 5] = y - 1;
				checkmax_bullet++;
				count_bullet1++;
			}
			if (ch == 'a') {
				pt = 0;
			}
			if (ch == 'd') {
				pt = 1;
			}
			if (ch == 's') {
				pt = 3;
			}
		}
		if (pt == 0 && x > 0) {
			erase_ship(x, y);
			draw_ship(--x, y);
		}
		if (pt == 1 && x < 80) {
			erase_ship(x, y);
			draw_ship(++x, y);
		}
		
		for (int a = 0; a < 5; a++)
		{
			
			if (bullet[a] == 1)
			{
				int check_po_star = 0;
				erase_bullet(bullet_x[a], bullet_y[a]);
		
				for (int j = 0; j < 20; j++)
				{
					if (bullet_y[a] == rand_y[j]  && bullet_x[a] == rand_x[j])
					{
						rand_y[j] = { 'null' };
						rand_x[j] = { 'null' };
						check_po_star++;
						Beep(450, 20);
						score++;
						break;	
					}
				}
			
				if (bullet_y[a] > 0 && check_po_star != 1)
				{
					draw_bullet(bullet_x[a], --bullet_y[a]);
				}
				if (bullet_y[a] == 0 || check_po_star == 1)
				{
					bullet[a] = 0;
					checkmax_bullet--;
					erase_bullet(bullet_x[a], bullet_y[a]);
				}
			}
			text_score(80, 0, score);
		}
		fflush(stdin);
		Sleep(100);
	} while (ch != 'x');
	return 0;
}



void setcolor(int fg, int bg) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
	setcolor(2, 4);
	gotoxy(x, y); printf("<-0->");
}
void erase_ship(int a, int b)
{
	gotoxy(a, b);
	setcolor(7, 0);
	printf("     ");
}

void draw_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(7, 0);
	printf("^");
}
void erase_bullet(int a, int b)
{
	gotoxy(a, b);
	setcolor(7, 0);
	printf(" ");
}
void text_score(int x, int y, int score)
{
	setcolor(2, 0);
	gotoxy(x, y);
	printf("score : %d", score);
}