#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <synchapi.h>
#include <windows.h>
#include "mmsystem.h"
#include <stdio.h>
#pragma comment(lib,"winmm.lib")
#pragma warning(disable:4996)
#define MAX 1000
#define SIZE 20


struct COOR
{
	int x;
	int y;

};


//键值
enum CH {
	up = 72,
	down = 80,
	left = 75,
	right = 77
};

//蛇类 结构体
struct SNAKE
{
	int n;//舍得节数
	COOR scr[MAX];//蛇的坐标
	CH ch;//蛇的方向
}snake;

//食物
struct FOOD
{
	COOR fcr;//食物的坐标
	int flag;//食物是否生成标志

}food;

void initGame() {
	initgraph(640, 480);

	snake.n = 2;

	snake.scr[0].x = 0;
	snake.scr[0].y = 0;

	snake.ch = right;

	food.flag = 0;//生成食物
	setbkcolor(BLACK);

}

void SnakePaint() {
	//蛇头
	fillrectangle(snake.scr[0].x, snake.scr[0].y, snake.scr[0].x + SIZE, snake.scr[0].y + SIZE);
	//蛇身
	for (int i = snake.n - 1; i>0; i--) {
		fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + SIZE, snake.scr[i].y + SIZE);
	}
}

//蛇的移动
void SnakeMove() {
	for (int i = snake.n - 1; i>0; i--){
		snake.scr[i].x = snake.scr[i - 1].x;
		snake.scr[i].y = snake.scr[i - 1].y;
	}
	switch (snake.ch) {
	case up:
		snake.scr[0].y -= SIZE;
		break;
	case down:
		snake.scr[0].y += SIZE;
		break;
	case left:
		snake.scr[0].x -= SIZE;
		break;
	case right:
		snake.scr[0].x+= SIZE;
		break;

	}

}

//控制蛇的方向
void ChangeSnake() {
	switch (_getch()) {
	case 72:
		if (snake.ch != down)
			snake.ch = up;
		break;
	case 80:
		if (snake.ch != up)
			snake.ch = down;
		break;
	case 75:
		if (snake.ch != right)
			snake.ch = left;
		break;
	case 77:
		if (snake.ch != left)
			snake.ch = right;
		break;
	
	}
}

//生成食物
void FoodCoor() {
	//随机数
	srand((unsigned)time(NULL));

	food.fcr.x = rand() % 32 * SIZE;
	food.fcr.y = rand() % 24 * SIZE;

	food.flag = 1;//生成坐标以后不生成食物

}

void FoodPaint() {
	
	setlinecolor(RED);
	setfillstyle(BS_SOLID);
	setfillcolor(RED);
	roundrect(food.fcr.x,food.fcr.y, food.fcr.x + SIZE, food.fcr.y + SIZE, 10, 10);//绘制
	//setfillcolor(RED);
}

//吃食物
void EatFood() {
	if (snake.scr[0].x == food.fcr.x && snake.scr[0].y == food.fcr.y) {
		snake.n++;
		food.flag = 0;
	}
}

void judge() {
	cleardevice();
	setbkcolor(BLUE);
	settextcolor(GREEN);
	settextstyle(50, 0, _T("黑体"));
	outtextxy(200, 200, _T("Game Over"));
	Sleep(3000);
	exit(0);
}
//判断游戏输赢
void GameOver() {
	//头撞墙
	if (snake.scr[0].x < 0 || snake.scr[0].x>620 || snake.scr[0].y < 0 || snake.scr[0].y > 460) {
		judge();
	}
	//身撞墙
	for (int i = snake.n - 1; i>0; i--) {
		if (snake.scr[0].x == snake.scr[i].x && snake.scr[0].y == snake.scr[i].y) {
			judge();
		}
	}
}
int main() {
	
		initGame();
		while (1) {
			//PlaySound("f:\1.mp3", NULL, SND_FILENAME | SND_ASYNC);
			while (!kbhit()) {
				if (food.flag == 0)
					FoodCoor();
				cleardevice();
				FoodPaint();
				SnakeMove();
				SnakePaint();
				Sleep(150);
				EatFood();

				GameOver();
			}
			ChangeSnake();
	}
	return 0;
}