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


//��ֵ
enum CH {
	up = 72,
	down = 80,
	left = 75,
	right = 77
};

//���� �ṹ��
struct SNAKE
{
	int n;//��ý���
	COOR scr[MAX];//�ߵ�����
	CH ch;//�ߵķ���
}snake;

//ʳ��
struct FOOD
{
	COOR fcr;//ʳ�������
	int flag;//ʳ���Ƿ����ɱ�־

}food;

void initGame() {
	initgraph(640, 480);

	snake.n = 2;

	snake.scr[0].x = 0;
	snake.scr[0].y = 0;

	snake.ch = right;

	food.flag = 0;//����ʳ��
	setbkcolor(BLACK);

}

void SnakePaint() {
	//��ͷ
	fillrectangle(snake.scr[0].x, snake.scr[0].y, snake.scr[0].x + SIZE, snake.scr[0].y + SIZE);
	//����
	for (int i = snake.n - 1; i>0; i--) {
		fillrectangle(snake.scr[i].x, snake.scr[i].y, snake.scr[i].x + SIZE, snake.scr[i].y + SIZE);
	}
}

//�ߵ��ƶ�
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

//�����ߵķ���
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

//����ʳ��
void FoodCoor() {
	//�����
	srand((unsigned)time(NULL));

	food.fcr.x = rand() % 32 * SIZE;
	food.fcr.y = rand() % 24 * SIZE;

	food.flag = 1;//���������Ժ�����ʳ��

}

void FoodPaint() {
	
	setlinecolor(RED);
	setfillstyle(BS_SOLID);
	setfillcolor(RED);
	roundrect(food.fcr.x,food.fcr.y, food.fcr.x + SIZE, food.fcr.y + SIZE, 10, 10);//����
	//setfillcolor(RED);
}

//��ʳ��
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
	settextstyle(50, 0, _T("����"));
	outtextxy(200, 200, _T("Game Over"));
	Sleep(3000);
	exit(0);
}
//�ж���Ϸ��Ӯ
void GameOver() {
	//ͷײǽ
	if (snake.scr[0].x < 0 || snake.scr[0].x>620 || snake.scr[0].y < 0 || snake.scr[0].y > 460) {
		judge();
	}
	//��ײǽ
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