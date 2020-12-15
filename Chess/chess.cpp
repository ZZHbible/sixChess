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

struct Point { //点结构
	int x, y;
	Point() {};
	Point(int i, int j) :x(i), y(j) {};
};
struct Step { //步结构
	Point first, second;
	int value;
};
int Board[19][19];//存储棋盘信息，其元素值为 BLACK, WHITE, EMPTY 之一
int copyBoard1[19][19];
int numberOfMyroad[6] = { 0,0,0,0,0,0 };  //numberOFMyroad[0]存放路为1的值
int numberOfEnemyroad[6] = { 0,0,0,0,0,0 };
const int scoreOfMyroad[2][6] = { {1,10,15,35,25,1000000},{1,5,10,35,25,1000000} };  //condition=0 表示进攻， condition=1表示防守
const int scoreOfEnemyroad[2][6] = { {1,10,15,1500,1500,100000},{1,10,15,1500,1500,100000} };
void analysisHorizon(int** p, int type, vector<Point>& list, int copyBoard1[19][19]);        //初始化扫描
void analysisVertical(int** p, int type, vector<Point>& list, int copyBoard1[19][19]);
void analysisLeftOblique(int** p, int type, vector<Point>& list, int copyBoard1[19][19]);
void analysisRightOblique(int** p, int type, vector<Point>& list, int copyBoard1[19][19]);
void analysisHorizon(int** p, int type);
void analysisVertical(int** p, int type);
void analysisLeftOblique(int** p, int type);
void analysisRightOblique(int** p, int type);




int main()
{
	Step step;//临时步结构
	char message[256];//通信消息缓冲
	int computerSide;//己方执棋颜色
	int start = 0;//对局开始标记
	srand(int(time(0)));
	//此处放置初始化代码
	//...

	while (1)	//程序主循环
	{
		fflush(stdout);//不要删除此语句，否则程序会出问题
		scanf("%s", message);//获取平台命令消息
		//分析命令
		if (strcmp(message, "name?") == 0)//向对战平台发送队名
		{
			fflush(stdin);
			/***********将"令狐冲"改为你的队名，不超过6个汉字或12个英文字母，否则无成绩************/
			/*******/		printf("name 小张\n");		/**只修改令狐冲，不要删除name空格****/
			/***********将"令狐冲"改为你的队名，不超过6个汉字或12个英文字母，否则无成绩************/
		}
		else if (strcmp(message, "new") == 0)//建立新棋局
		{
			int i, j;
			scanf("%s", message);//获取己方执棋颜色
			fflush(stdin);
			if (strcmp(message, "black") == 0)	computerSide = BLACK;  //执黑
			else  computerSide = WHITE;   //执白

			for (i = 0; i < 19; ++i)   //初始化棋局
				for (j = 0; j < 19; ++j)
					Board[i][j] = EMPTY;
			start = 1;

			if (computerSide == BLACK)
			{
				/**********生成第一手着法，并保存在step结构中，落子坐标为(step.first.x,step.first.y)**********/
				/****************************在下方填充代码，并替换我的示例代码******************************/


				step.first.x = 9;
				step.first.y = 9;


				/******************************在上面填充第一步行棋代码*******************************************/

				Board[step.first.x][step.first.y] = computerSide;//处理己方行棋
				printf("move %c%c@@\n", step.first.x + 'A', step.first.y + 'A');//输出着法
			}
		}
		else if (strcmp(message, "move") == 0)//行棋,本程序核心
		{
			scanf("%s", message);//获取对手行棋着法
			fflush(stdin);
			step.first.x = message[0] - 'A';		step.first.y = message[1] - 'A';
			step.second.x = message[2] - 'A';		step.second.y = message[3] - 'A';
			//处理对手行棋
			Board[step.first.x][step.first.y] = 8 - computerSide;
			if (!(step.second.x == -1 && step.second.y == -1)) Board[step.second.x][step.second.y] = 8 - computerSide;

			/**********************************************************************************************************/
			/***生成落子的坐标，保存在step结构中，第1子下在(step.first.x,step.first.y)，第2子下在(step.first.x,step.first.y)*****/
			/**************************************在下方填充代码，并替换我的示例代码*****************************************/
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
			} //将Board拷贝到copyBoard

			vector<Point> p;
			//生成第1子落子位置step.first.x和step.first.y
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
				basescore += ((numberOfMyroad[i] - numberOfEnemyroad[i])*score[i]); //基础分值
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

			//生成第2子落子位置step.second.x和step.second.y	


			/*****************************************在上面填充代码******************************************************/
			/**********************************************************************************************************/

			printf("move %c%c%c%c\n", step.first.x + 'A', step.first.y + 'A', step.second.x + 'A', step.second.y + 'A');//输出着法
		}
		else if (strcmp(message, "error") == 0)//着法错误
		{
			fflush(stdin);
		}
		else if (strcmp(message, "end") == 0)//对局结束
		{
			fflush(stdin);
			start = 0;
		}
		else if (strcmp(message, "quit") == 0)//退出引擎
		{
			fflush(stdin);
			printf("Quit!\n");
			break;
		}
	}
	return 0;
}

void analysisHorizon(int** p, int type, vector<Point>& list, int copyBoard1[19][19]) { //type=传进来的WHITE ——水平
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 14; j++) {
			int number = copyBoard1[i][j] + copyBoard1[i][j + 1] + copyBoard1[i][j + 2] + copyBoard1[i][j + 3] + copyBoard1[i][j + 4] + copyBoard1[i][j + 5];
			if (number == 0 || (number > 6 && number % 7 != 0)) continue;   //路上为空或者交替则继续，
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
void analysisVertical(int** p, int type, vector<Point>& list, int copyBoard1[19][19]) { //type=传进来的WHITE ——垂直
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
void analysisLeftOblique(int** p, int type, vector<Point>& list, int copyBoard1[19][19]) { //type=传进来的WHITE   ——左斜
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
void analysisRightOblique(int** p, int type, vector<Point>& list, int copyBoard1[19][19]) { //type=传进来的WHITE   ——右斜
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


void analysisHorizon(int**p, int type) { //type=传进来的WHITE ——水平
	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 14; j++) {
			int number = p[i][j] + p[i][j + 1] + p[i][j + 2] + p[i][j + 3] + p[i][j + 4] + p[i][j + 5];
			if (number == 0 || (number > 6 && number % 7 != 0)) continue;   //路上为空或者交替则继续，
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
void analysisVertical(int** p, int type) { //type=传进来的WHITE ——垂直
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
void analysisLeftOblique(int** p, int type) { //type=传进来的WHITE   ——左斜
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
void analysisRightOblique(int**p, int type) { //type=传进来的WHITE   ——右斜
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

