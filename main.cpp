#include<stdio.h>
#include <conio.h>
#include<time.h>
#include <windows.h>
#include<iostream>
#include<mmsystem.h>
#include<stdlib.h>
void clrscr(void)
{
CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
HANDLE hConsoleOut;
COORD Home = {0,0};
DWORD dummy;

hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);

FillConsoleOutputCharacter(hConsoleOut,' ',csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
csbiInfo.dwCursorPosition.X = 0;
csbiInfo.dwCursorPosition.Y = 0;

}

void gotoXY (int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}


using namespace std;

int main(){

       ShowCur(0);
	int scores = 30;
	int time = 10;

	while(time!=0){
		clrscr();
		time--;
		Beep(659,500);
		gotoXY(50,15);
		cout<<time;
		Sleep(1000);
	}

		PlaySound(TEXT("music.wav"),NULL,SND_ASYNC);
		getch();


	return 0;
}
