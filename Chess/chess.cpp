#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<vector>
#include<iostream>
using namespace std;

#define BLACK 1
#define WHITE 7
#define EMPTY 0
#define TEMP  -1

struct Point { //��ṹ
	int x, y;
	Point() {};
	Point(int i, int j) :x(i), y(j) {};
};
struct Step { //���ṹ
	Point first, second;
	int value;
};
int Board[19][19];//�洢������Ϣ����Ԫ��ֵΪ BLACK, WHITE, EMPTY ֮һ
int copyBoard1[19][19];
int numberOfMyroad[6] = { 0,0,0,0,0,0 };  //numberOFMyroad[0]���·Ϊ1��ֵ
int numberOfEnemyroad[6] = { 0,0,0,0,0,0 };
const int scoreOfMyroad[2][6] = { {1,10,15,35,25,1000000},{1,5,10,35,25,1000000} };  //condition=0 ��ʾ������ condition=1��ʾ����
const int scoreOfEnemyroad[2][6] = { {1,10,15,1500,1500,100000},{1,10,15,1500,1500,100000} };
void analysisHorizon(int** p, int type, vector<Point>& list, int copyBoard1[19][19]);        //��ʼ��ɨ��
void analysisVertical(int** p, int type, vector<Point>& list, int copyBoard1[19][19]);
void analysisLeftOblique(int** p, int type, vector<Point>& list, int copyBoard1[19][19]);
void analysisRightOblique(int** p, int type, vector<Point>& list, int copyBoard1[19][19]);
void analysisHorizon(int** p, int type);
void analysisVertical(int** p, int type);
void analysisLeftOblique(int** p, int type);
void analysisRightOblique(int** p, int type);




int main()
{
	Step step;//��ʱ���ṹ
	char message[256];//ͨ����Ϣ����
	int computerSide;//����ִ����ɫ
	int start = 0;//�Ծֿ�ʼ���
	srand(int(time(0)));
	//�˴����ó�ʼ������
	//...

	while (1)	//������ѭ��
	{
		fflush(stdout);//��Ҫɾ������䣬�������������
		scanf("%s", message);//��ȡƽ̨������Ϣ
		//��������
		if (strcmp(message, "name?") == 0)//���սƽ̨���Ͷ���
		{
			fflush(stdin);
			/***********��"�����"��Ϊ��Ķ�����������6�����ֻ�12��Ӣ����ĸ�������޳ɼ�************/
			/*******/		printf("name С��\n");		/**ֻ�޸�����壬��Ҫɾ��name�ո�****/
			/***********��"�����"��Ϊ��Ķ�����������6�����ֻ�12��Ӣ����ĸ�������޳ɼ�************/
		}
		else if (strcmp(message, "new") == 0)//���������
		{
			int i, j;
			scanf("%s", message);//��ȡ����ִ����ɫ
			fflush(stdin);
			if (strcmp(message, "black") == 0)	computerSide = BLACK;  //ִ��
			else  computerSide = WHITE;   //ִ��

			for (i = 0; i < 19; ++i)   //��ʼ�����
				for (j = 0; j < 19; ++j)
					Board[i][j] = EMPTY;
			start = 1;

			if (computerSide == BLACK)
			{
				/**********���ɵ�һ���ŷ�����������step�ṹ�У���������Ϊ(step.first.x,step.first.y)**********/
				/****************************���·������룬���滻�ҵ�ʾ������******************************/


				step.first.x = 9;
				step.first.y = 9;


				/******************************����������һ���������*******************************************/

				Board[step.first.x][step.first.y] = computerSide;//����������
				printf("move %c%c@@\n", step.first.x + 'A', step.first.y + 'A');//����ŷ�
			}
		}
		else if (strcmp(message, "move") == 0)//����,���������
		{
			scanf("%s", message);//��ȡ���������ŷ�
			fflush(stdin);
			step.first.x = message[0] - 'A';		step.first.y = message[1] - 'A';
			step.second.x = message[2] - 'A';		step.second.y = message[3] - 'A';
			//�����������
			Board[step.first.x][step.first.y] = 8 - computerSide;
			if (!(step.second.x == -1 && step.second.y == -1)) Board[step.second.x][step.second.y] = 8 - computerSide;

			/**********************************************************************************************************/
			/***�������ӵ����꣬������step�ṹ�У���1������(step.first.x,step.first.y)����2������(step.first.x,step.first.y)*****/
			/**************************************���·������룬���滻�ҵ�ʾ������*****************************************/
			int x, y;
			x = rand() % 19; y = rand() % 19;
			while (Board[x][y] != EMPTY)
			{
				x = rand() % 19;	y = rand() % 19;
			}
			step.first.x = x;
			step.first.y = y;
			x = rand() % 19;	y = rand() % 19;
			while (Board[x][y] != EMPTY || (x == step.first.x&&y == step.first.y))
			{
				x = rand() % 19;	y = rand() % 19;
			}
			step.second.x = x;
			step.second.y = y;
			int** copyBoard = new int*[19];
			for (int i = 0; i < 19; i++) {
				copyBoard[i] = new int[19];
			}
			for (int i = 0; i < 19; i++) {
				for (int j = 0; j < 19; j++) {
					copyBoard[i][j] = Board[j][i];
					copyBoard1[i][j] = Board[j][i];
				}
			} //��Board������copyBoard

			vector<Point> p;
			//���ɵ�1������λ��step.first.x��step.first.y
			analysisHorizon(copyBoard, computerSide, p, copyBoard1);
			analysisVertical(copyBoard, computerSide, p, copyBoard1);
			analysisLeftOblique(copyBoard, computerSide, p, copyBoard1);
			analysisRightOblique(copyBoard, computerSide, p, copyBoard1);
			for (int i = 0; i < 19; i++) {
				for (int j = 0; j < 19; j++) {
					if (copyBoard[i][j] == TEMP) {
						copyBoard[i][j] = EMPTY;
					}
				}
			}
			int basescore = 0;
			int condition = 0;
			int score[6] = { 1,10,15,50,50,10000 };
			for (int i = 0; i < 6; i++) {
				basescore += ((numberOfMyroad[i] - numberOfEnemyroad[i])*score[i]); //������ֵ
			}
			if (basescore > 0) {
				condition = 0;
			}
			else {
				condition = 1;
			}
			Point fin_point1;
			x = rand() % 19; y = rand() % 19;
			while (Board[x][y] != EMPTY)
			{
				x = rand() % 19;	y = rand() % 19;
			}
			int maxscore = -10000;
			for (vector<Point>::iterator it1 = p.begin(); it1 != p.end(); ++it1) {
				Point point1 = *it1;
				copyBoard[point1.x][point1.y] = computerSide;
				for (vector<Point>::iterator it2 = it1 + 1; it2 != p.end(); ++it2) {
					Point point2 = *it2;
					copyBoard[point2.x][point2.y] = computerSide;
					int tempscore = 0;
					for (int i = 0; i < 6; i++) {
						numberOfMyroad[i] = 0;
						numberOfEnemyroad[i] = 0;
					}
					analysisHorizon(copyBoard, computerSide);
					analysisVertical(copyBoard, computerSide);
					analysisLeftOblique(copyBoard, computerSide);
					analysisRightOblique(copyBoard, computerSide);
					for (int i = 0; i < 6; i++) {
						tempscore += (numberOfMyroad[i] * scoreOfMyroad[condition][i] - numberOfEnemyroad[i] * scoreOfEnemyroad[condition][i]);
					}
					if (maxscore < tempscore) {
						step.first.x = point1.y; step.first.y = point1.x;
						step.second.x = point2.y; step.second.y = point2.x;
						maxscore = tempscore;
					}
					copyBoard[point2.x][point2.y] = EMPTY;
				}
				copyBoard[point1.x][point1.y] = EMPTY;

			}
			Board[step.first.x][step.first.y] = computerSide;
			Board[step.second.x][step.second.y] = computerSide;
			for (int i = 0; i < 19; i++) {
				delete[] copyBoard[i];
			}
			delete[] copyBoard;

			//���ɵ�2������λ��step.second.x��step.second.y	


			/*****************************************������������******************************************************/
			/**********************************************************************************************************/

			printf("move %c%c%c%c\n", step.first.x + 'A', step.first.y + 'A', step.second.x + 'A', step.second.y + 'A');//����ŷ�
		}
		else if (strcmp(message, "error") == 0)//�ŷ�����
		{
			fflush(stdin);
		}
		else if (strcmp(message, "end") == 0)//�Ծֽ���
		{
			fflush(stdin);
			start = 0;
		}
		else if (strcmp(message, "quit") == 0)//�˳�����
		{
			fflush(stdin);
			printf("Quit!\n");
			break;
		}
	}
	return 0;
}

void analysisHorizon(int** p, int type, vector<Point>& list, int copyBoard1[19][19]) { //type=��������WHITE ����ˮƽ
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 14; j++) {
			int number = copyBoard1[i][j] + copyBoard1[i][j + 1] + copyBoard1[i][j + 2] + copyBoard1[i][j + 3] + copyBoard1[i][j + 4] + copyBoard1[i][j + 5];
			if (number == 0 || (number > 6 && number % 7 != 0)) continue;   //·��Ϊ�ջ��߽����������
			if (copyBoard1[i][j] == EMPTY && p[i][i] != TEMP && (copyBoard1[i][j + 1] == BLACK || copyBoard1[i][j + 1] == WHITE
				|| copyBoard1[i][j + 2] == BLACK || copyBoard1[i][j + 2] == WHITE
				|| copyBoard1[i][j + 3] == BLACK || copyBoard1[i][j + 3] == WHITE)) {
				list.push_back(Point(i, j)); p[i][j] = TEMP;
			}
			if (p[i][j] != TEMP && (copyBoard1[i][j] == BLACK || copyBoard1[i][j] == WHITE)) {
				if (p[i][j + 1] == EMPTY) {
					list.push_back(Point(i, j + 1)); p[i][j + 1] = TEMP;
				}
				if (p[i][j + 2] == EMPTY) {
					list.push_back(Point(i, j + 2)); p[i][j + 2] = TEMP;
				}
				if (p[i][j + 3] == EMPTY) {
					list.push_back(Point(i, j + 3)); p[i][j + 3] = TEMP;
				}
			}
			if (number < 7) {
				if (type == BLACK) {
					numberOfMyroad[number - 1]++;
				}
				else {
					numberOfEnemyroad[number - 1]++;
				}
			}
			else {
				if (type == BLACK) {
					numberOfEnemyroad[number / 7 - 1]++;
				}
				else {
					numberOfMyroad[number / 7 - 1]++;
				}
			}

		}
	}
}
void analysisVertical(int** p, int type, vector<Point>& list, int copyBoard1[19][19]) { //type=��������WHITE ������ֱ
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 19; j++) {
			int number = copyBoard1[i][j] + copyBoard1[i + 1][j] + copyBoard1[i + 2][j] + copyBoard1[i + 3][j] + copyBoard1[i + 4][j] + copyBoard1[i + 5][j];
			if (number == 0 || (number > 6 && number % 7 != 0)) continue;
			if ((copyBoard1[i][j] == EMPTY && p[i][i] != TEMP && (copyBoard1[i + 1][j] == BLACK || copyBoard1[i + 1][j] == WHITE
				|| copyBoard1[i + 2][j] == BLACK || copyBoard1[i + 2][j] == WHITE
				|| copyBoard1[i + 3][j] == BLACK || copyBoard1[i + 3][j] == WHITE))) {
				list.push_back(Point(i, j)); p[i][j] = TEMP;
			}
			if (p[i][j] != TEMP && (copyBoard1[i][j] == BLACK || copyBoard1[i][j] == WHITE)) {
				if (p[i + 1][j] == EMPTY) {
					list.push_back(Point(i + 1, j)); p[i + 1][j] = TEMP;
				}
				if (p[i + 2][j] == EMPTY) {
					list.push_back(Point(i + 2, j)); p[i + 2][j] = TEMP;
				}
				if (p[i + 3][j] == EMPTY) {
					list.push_back(Point(i + 3, j)); p[i + 3][j] = TEMP;
				}
			}

			if (number < 7) {
				if (type == BLACK) {
					numberOfMyroad[number - 1]++;
				}
				else {
					numberOfEnemyroad[number - 1]++;
				}
			}
			else {
				if (type == BLACK) {
					numberOfEnemyroad[number / 7 - 1]++;
				}
				else {
					numberOfMyroad[number / 7 - 1]++;
				}
			}

		}
	}
}
void analysisLeftOblique(int** p, int type, vector<Point>& list, int copyBoard1[19][19]) { //type=��������WHITE   ������б
	for (int i = 5; i < 19; i++) {
		for (int j = 0; j < 14; j++) {
			int number = copyBoard1[i][j] + copyBoard1[i - 1][j + 1] + copyBoard1[i - 2][j + 2] + copyBoard1[i - 3][j + 3] + copyBoard1[i - 4][j + 4] + copyBoard1[i - 5][j + 5];
			if (number == 0 || (number > 6 && number % 7 != 0)) continue;
			if (copyBoard1[i][j] == EMPTY && p[i][i] != TEMP && (copyBoard1[i - 1][j + 1] == BLACK || copyBoard1[i - 1][j + 1] == WHITE
				|| copyBoard1[i - 2][j + 2] == BLACK || copyBoard1[i - 2][j + 2] == WHITE
				|| copyBoard1[i - 3][j + 3] == BLACK || copyBoard1[i - 3][j + 3] == WHITE)) {
				list.push_back(Point(i, j)); p[i][j] = TEMP;
			}
			if (p[i][j] != TEMP && (copyBoard1[i][j] == BLACK || copyBoard1[i][j] == WHITE)) {
				if (p[i - 1][j + 1] == EMPTY) {
					list.push_back(Point(i - 1, j + 1)); p[i - 1][j + 1] = TEMP;
				}
				if (p[i - 2][j + 2] == EMPTY) {
					list.push_back(Point(i - 2, j + 2)); p[i - 2][j + 2] = TEMP;
				}
				if (p[i - 3][j + 3] == EMPTY) {
					list.push_back(Point(i - 3, j + 3)); p[i - 3][j + 3] = TEMP;
				}
			}

			if (number < 7) {
				if (type == BLACK) {
					numberOfMyroad[number - 1]++;
				}
				else {
					numberOfEnemyroad[number - 1]++;
				}
			}
			else {
				if (type == BLACK) {
					numberOfEnemyroad[number / 7 - 1]++;
				}
				else {
					numberOfMyroad[number / 7 - 1]++;
				}
			}

		}
	}
}
void analysisRightOblique(int** p, int type, vector<Point>& list, int copyBoard1[19][19]) { //type=��������WHITE   ������б
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 14; j++) {
			int number = copyBoard1[i][j] + copyBoard1[i + 1][j + 1] + copyBoard1[i + 2][j + 2] + copyBoard1[i + 3][j + 3] + copyBoard1[i + 4][j + 4] + copyBoard1[i + 5][j + 5];
			if (number == 0 || (number > 6 && number % 7 != 0)) continue;
			if (copyBoard1[i][j] == EMPTY && p[i][i] != TEMP && (copyBoard1[i + 1][j + 1] == BLACK || copyBoard1[i + 1][j + 1] == WHITE
				|| copyBoard1[i + 2][j + 2] == BLACK || copyBoard1[i + 2][j + 2] == WHITE
				|| copyBoard1[i + 3][j + 3] == BLACK || copyBoard1[i + 3][j + 3] == WHITE)) {
				list.push_back(Point(i, j)); p[i][j] = TEMP;
			}
			if (p[i][j] != TEMP && (copyBoard1[i][j] == BLACK || copyBoard1[i][j] == WHITE)) {
				if (p[i + 1][j + 1] == EMPTY) {
					list.push_back(Point(i + 1, j + 1)); p[i + 1][j + 1] = TEMP;
				}
				if (p[i + 2][j + 2] == EMPTY) {
					list.push_back(Point(i + 2, j + 2)); p[i + 2][j + 2] = TEMP;
				}
				if (p[i + 3][j + 3] == EMPTY) {
					list.push_back(Point(i + 3, j + 3)); p[i + 3][j + 3] = TEMP;
				}
			}
			if (number < 7) {
				if (type == BLACK) {
					numberOfMyroad[number - 1]++;
				}
				else {
					numberOfEnemyroad[number - 1]++;
				}
			}
			else {
				if (type == BLACK) {
					numberOfEnemyroad[number / 7 - 1]++;
				}
				else {
					numberOfMyroad[number / 7 - 1]++;
				}
			}

		}
	}
}


void analysisHorizon(int**p, int type) { //type=��������WHITE ����ˮƽ
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 14; j++) {
			int number = p[i][j] + p[i][j + 1] + p[i][j + 2] + p[i][j + 3] + p[i][j + 4] + p[i][j + 5];
			if (number == 0 || (number > 6 && number % 7 != 0)) continue;   //·��Ϊ�ջ��߽����������
			if (number < 7) {
				if (type == BLACK) {
					numberOfMyroad[number - 1]++;
				}
				else {
					numberOfEnemyroad[number - 1]++;
				}
			}
			else {
				if (type == BLACK) {
					numberOfEnemyroad[number / 7 - 1]++;
				}
				else {
					numberOfMyroad[number / 7 - 1]++;
				}
			}

		}
	}
}
void analysisVertical(int** p, int type) { //type=��������WHITE ������ֱ
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 19; j++) {
			int number = p[i][j] + p[i + 1][j] + p[i + 2][j] + p[i + 3][j] + p[i + 4][j] + p[i + 5][j];
			if (number == 0 || (number > 6 && number % 7 != 0)) continue;
			if (number < 7) {
				if (type == BLACK) {
					numberOfMyroad[number - 1]++;
				}
				else {
					numberOfEnemyroad[number - 1]++;
				}
			}
			else {
				if (type == BLACK) {
					numberOfEnemyroad[number / 7 - 1]++;
				}
				else {
					numberOfMyroad[number / 7 - 1]++;
				}
			}

		}
	}
}
void analysisLeftOblique(int** p, int type) { //type=��������WHITE   ������б
	for (int i = 5; i < 19; i++) {
		for (int j = 0; j < 14; j++) {
			int number = p[i][j] + p[i - 1][j + 1] + p[i - 2][j + 2] + p[i - 3][j + 3] + p[i - 4][j + 4] + p[i - 5][j + 5];
			if (number == 0 || (number > 6 && number % 7 != 0)) continue;
			if (number < 7) {
				if (type == BLACK) {
					numberOfMyroad[number - 1]++;
				}
				else {
					numberOfEnemyroad[number - 1]++;
				}
			}
			else {
				if (type == BLACK) {
					numberOfEnemyroad[number / 7 - 1]++;
				}
				else {
					numberOfMyroad[number / 7 - 1]++;
				}
			}

		}
	}
}
void analysisRightOblique(int**p, int type) { //type=��������WHITE   ������б
	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 14; j++) {
			int number = p[i][j] + p[i + 1][j + 1] + p[i + 2][j + 2] + p[i + 3][j + 3] + p[i + 4][j + 4] + p[i + 5][j + 5];
			if (number == 0 || (number > 6 && number % 7 != 0)) continue;
			if (number < 7) {
				if (type == BLACK) {
					numberOfMyroad[number - 1]++;
				}
				else {
					numberOfEnemyroad[number - 1]++;
				}
			}
			else {
				if (type == BLACK) {
					numberOfEnemyroad[number / 7 - 1]++;
				}
				else {
					numberOfMyroad[number / 7 - 1]++;
				}
			}

		}
	}
}

