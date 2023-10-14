#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include<conio.h>
#include <Windows.h>
#pragma comment(lib,"winmm.lib")

#define ROW 4
#define COL 4
int arr[ROW][COL] = { 0 };
int score = 0;
int k = 0;

//�ɼ���¼
void reminder(int a)
{
	time_t time_seconds = time(0);
	//�������ڱ���ʱ��ı�����time()�������ڷ��ش�1970��1��1��00��00��00���񾭹�������
	struct tm timer;//<time.h>ͷ�ļ��ж���Ľṹ��
	localtime_s(&timer, &time_seconds);//��ȡϵͳʱ��
	FILE* fp;//�����ļ�ָ��
	errno_t err;
	//�����������ݣ����Է��ش�����루����ɹ��ͷ���0��ʧ���򷵻���Ӧ�ķ��������룩
	err = fopen_s(&fp, "records.txt", "a");
	//��׷��ģʽ��������ļ�
	if (err)
	{
		printf("�ڼ�¼���ݵ�ʱ���ʧ�ܣ�\n");
		exit(0);
	}
	else
	{
		fprintf_s(fp, "%-8d%.2d.%.2d.%.2d:%.2d:%.2d\n",
			a,
			timer.tm_year + 1900,
			timer.tm_mon + 1,
			timer.tm_mday,
			timer.tm_hour,
			timer.tm_min,
			timer.tm_sec);
		fclose(fp);
	}//�򴴽��ɹ����ļ���д���������Ϸ���ʱ�䣨����������ļ�ʧ�ܣ����ӡ����Ӧ��ʾ���˳���
}
//��ӡ��߼�¼
int best(void)
{
	char m = '0';
	int a = 0, b = 0, max = 0, i = 0;
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, "records.txt", "a");
	fclose(fp);//��׷��ģʽ��������ļ�
	err = fopen_s(&fp, "records.txt", "r");
	//��ֻ��ģʽ���Ѵ��ڵ��ļ��������ļ�ʧ�ܣ����ӡ����Ӧ��ʾ���˳���
	if (err)
	{
		printf("�ڴ�ӡ��ʷ��¼��ʱ���ʧ�ܣ�\n");
		exit(0);
	}
	else
	{
		fseek(fp, 0, 2);//�����ļ�λ��ָʾ���ļ�β
		k = ftell(fp) / 24;
		//��ȡ������k�ĵ�ǰλ�úţ���λ���ļ�β����������24�Լ�����Ϸ��ɴ���
		printf("������%d����Ϸ��¼\n", k);
		fseek(fp, 0, 0);//�����ļ�λ��ָʾ���ļ�ͷ
			for (i = 0; i < k; i++)
			{
				fseek(fp, i * 24, 0);//�����ļ�λ��ָʾ
				fscanf_s(fp, "%d", &a);//��ȡ��Ϸ����
				if (max < a)
					max = a;
				while (m != '\n')
					m = fgetc(fp);
				m++;
				//���ļ��м�¼ʱ������ݸ�ֵ��m�������ƶ��ļ�ָʾλ��
				fscanf_s(fp, "%d", &b);
				if (max < b)
					max = b;
			}//������ȡ��Ϸ�������Ƚϴ�С
	}
	fclose(fp);
	return max;//������߼�¼
}
//���ù���λ��
void SetCurPos(int x, int y)
{
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);//���þ��
	COORD coord = { x, y };
	SetConsoleCursorPosition(hStdOutput, coord);//���ù��λ��
}
//���ع��
void ViewInit(int width, int height)
{
	HANDLE hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;//����һ���ṹ��
	GetConsoleCursorInfo(hStdOutput, &info);//�������
	info.bVisible = 0;//ʹ��겻�ɼ�
	SetConsoleCursorInfo(hStdOutput, &info);//���޸�ֵ���ؿ���̨
}
//��ӡ����
void GamePrint(int row, int col)
{
	SetCurPos(5, 9);
	printf("SCORE = %d", score);//���ù��λ�ò���ӡ����
	SetCurPos(5, 10);
	printf("     Highest=%d", best());
	printf("\n������������������Ϊ��records�����ļ���\n���е���Ϸ��¼\n");
	//���ù��λ�ò���ӡ��߼�¼���鿴�ļ���ʾ
	SetCurPos(48, 5);
	int i = 0;
	for (i = 0; i < row; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			printf(" ");
			for (int j = 0; j < 4; j++)
			{
				printf("-");
			}
		}
		printf("\n\t\t\t\t\t\t");//�����ƶ������ָ��λ��
		for (int k = 0; k < 4; k++)
		{
			printf("|");
			if (arr[i][k])
			{
				printf("%4d", arr[i][k]);//������������
			}
			else
			{
				for (int j = 0; j < 4; j++)
				{
					printf(" ");//û�����ֵ�λ���ÿո����
				}
			}
		}
		printf("|\n\t\t\t\t\t\t");//�����ƶ������ָ��λ��
		if (i == row - 1)
		{
			for (int k = 0; k < 4; k++)
			{
				printf(" ");
				for (int j = 0; j < 4; j++)
				{
					printf("-");
				}
			}//��ӡ���ڡ��� |��ѭ����Χ�ڵĵ�9��
			printf("\n\t\t\t\t\t\t");//�����ƶ������ָ��λ��
		}
	}//ʹ��ѭ������ӡ��񲢽���Ϸ�����������λ
	SetCurPos(48, 4);
	printf("�������ұ�ʾ����\n");
	//���ù��λ���Դ�ӡ��Ϸ����Ҫ��
	SetCurPos(48, 15);//���ù��λ��
}
//���������
void RandNum(int row, int col) //���������
{
	int x = 0;
	int y = 0;
	do
	{
		x = rand() % 4;
		y = rand() % 4;
	} while (arr[x][y]);
	arr[x][y] = (rand() % 10 ? 2 : 4);
}
//������
int MoveLeft(int arr[ROW][COL], int* a)
{
	int m = 0;
	for (int i = 0; i < ROW; i++)
	{
		int j = 1;
		int k = 0;
		for (; j < 4; j++)
		{
			if (arr[i][j] > 0)
			{
				if (arr[i][k] == 0)
				{
					arr[i][k] = arr[i][j];
					arr[i][j] = 0;
					m = 1;
				}
				else if (arr[i][k] == arr[i][j])
				{
					arr[i][k] = 2 * arr[i][k];
					score += arr[i][k];
					arr[i][j] = 0;
					k++;
					m = 1;
					*a = 1;
				}
				else
				{
					arr[i][++k] = arr[i][j];
					if (j != k)
					{
						arr[i][j] = 0;
						m = 1;
					}
				}
			}
		}
	}
	return m;
}
//������
int MoveRight(int arr[ROW][COL], int* a)
{
	int m = 0;
	for (int i = 0; i < ROW; i++)
	{
		int j = 2;
		int k = 3;
		for (; j >= 0; j--)
		{
			if (arr[i][j] > 0)
			{
				if (arr[i][k] == 0)
				{
					arr[i][k] = arr[i][j];
					arr[i][j] = 0;
					m = 1;
				}
				else if (arr[i][k] == arr[i][j])
				{
					arr[i][k] = 2 * arr[i][k];
					score += arr[i][k];
					arr[i][j] = 0;
					k--;
					m = 1;
					*a = 1;
				}
				else
				{
					arr[i][--k] = arr[i][j];
					if (j != k)
					{
						arr[i][j] = 0;
						m = 1;
					}
				}
			}
		}
	}
	return m;
}
//������
int MoveUp(int arr[ROW][COL], int* a)
{
	int m = 0;
	for (int j = 0; j < COL; j++)
	{
		int i = 1;
		int k = 0;
		for (; i < 4; i++)
		{
			if (arr[i][j] > 0)
			{
				if (arr[k][j] == arr[i][j])
				{
					score += arr[k++][j] *= 2;
					arr[i][j] = 0;
					m = 1;
					*a = 1;
				}
				else if (arr[k][j] == 0)
				{
					arr[k][j] = arr[i][j];
					arr[i][j] = 0;
					m = 1;
				}
				else
				{
					arr[++k][j] = arr[i][j];
					if (i != k)
					{
						arr[i][j] = 0;
						m = 1;
					}
				}
			}
		}
	}
	return m;
}
//������
int MoveDown(int arr[ROW][COL], int* a)
{
	int m = 0;
	for (int j = 0; j < COL; j++)
	{
		int i = 2;
		int k = 3;
		for (; i >= 0; i--)
		{
			if (arr[i][j] > 0)
			{
				if (arr[k][j] == 0)
				{
					arr[k][j] = arr[i][j];
					arr[i][j] = 0;
					m = 1;
				}
				else if (arr[k][j] == arr[i][j])
				{
					arr[k][j] = 2 * arr[k][j];
					score += arr[k][j];
					arr[i][j] = 0;
					k--;
					m = 1;
					*a = 1;
				}
				else
				{
					arr[--k][j] = arr[i][j];
					if (i != k)
					{
						arr[i][j] = 0;
						m = 1;
					}
				}
			}
		}
	}
	return m;
}
//�ж��Ƿ��ʤ
int IfWin(int row, int col)
{
	int b = 0;
	int copy_board[ROW][COL], i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			copy_board[i][j] = arr[i][j];
		}
	}

	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			if (arr[i][j] == 2048)
				return 1;//��ʤ
	for (i = 0; i < row; i++)
		for (j = 0; j < col; j++)
			if (MoveLeft(copy_board, &b) == 1 || MoveRight(copy_board, &b) == 1 || MoveUp(copy_board, &b) == 1 || MoveDown(copy_board, &b) == 1)
				return 0;//�ж��Ƿ����ƶ�
	return  -1;//ʧ��
}
//��Ϸ����
int GameContinue()
{
	int ch1 = 0;
	int ch2 = 0;
	int h = 0, b = 0;
	int (*f[4])(int arr[4][4], int* a) = { MoveUp,MoveDown,MoveLeft,MoveRight };
	while (1)
	{
		if (ch1 = _getch())
		{
			ch2 = _getch();
			if (ch2 == 72)
			{
				h = (*f[0])(arr, &b);
				break;
			}
			if (ch2 == 80)
			{
				h = (*f[1])(arr, &b);
				break;
			}
			if (ch2 == 75)
			{
				h = (*f[2])(arr, &b);
				break;
			}
			if (ch2 == 77)
			{
				h = (*f[3])(arr, &b);
				break;
			}
		}
	}
	if (h == 0)
		PlaySound("D:\\����.wav", NULL, SND_FILENAME | SND_ASYNC);
	else if (h == 1 && b == 0)
		PlaySound("D:\\��ת.wav", NULL, SND_FILENAME | SND_ASYNC);
	else
		PlaySound("D:\\�߼�.wav", NULL, SND_FILENAME | SND_ASYNC);
	return h;
}

void game()
{
	srand((unsigned int)time(NULL));
	ViewInit(20, 10);
	RandNum(ROW, COL);
	RandNum(ROW, COL);
	GamePrint(ROW, COL);
	while (1)
	{
		if (IfWin(ROW, COL) == 1)
		{
			printf("YOU WIN!\n");
			PlaySound("D:\\ʤ��.wav", NULL, SND_FILENAME | SND_ASYNC);
			reminder(score);
			return;
		}
		else if (IfWin(ROW, COL) == -1)
		{
			printf("GAME OVER\n");
			PlaySound("D:\\ʧ��.wav", NULL, SND_FILENAME | SND_ASYNC);
			reminder(score);
			return;
		}
		else
		{
			if (GameContinue())
			{
				system("cls");
				RandNum(ROW, COL);
				GamePrint(ROW, COL);
			}
			else continue;
		}
	}
}
void game2()
{
	ViewInit(20, 10);
	GamePrint(ROW, COL);
	while (1)
	{
		if (IfWin(ROW, COL) == 1)
		{
			printf("YOU WIN!\n");
			PlaySound("D:\\ʤ��.wav", NULL, SND_FILENAME | SND_ASYNC);
			reminder(score);
			return;
		}
		else if (IfWin(ROW, COL) == -1)
		{
			printf("GAME OVER\n");
			PlaySound("D:\\ʧ��.wav", NULL, SND_FILENAME | SND_ASYNC);
			reminder(score);
			return;
		}
		else
		{
			if (GameContinue())
			{
				system("cls");
				RandNum(ROW, COL);
				GamePrint(ROW, COL);
			}
			else continue;
		}
	}
}
void GAME()
{
	char c = '1', a;
	int m, i;
	while (1)
	{
		while (c == '1')
		{
			for (i = 0; i < 4; i++)
				for (m = 0; m < 4; m++)
					arr[m][i] = 0;
			score = 0;
			system("cls");
			game();
			if (score < 2000)
			{
				printf("������1�Լ���������b�˳���\n");
				do {
					c = _getch();

				} while (!((c == '1') || (c == 'b')));
				if (c == 'b')
					exit(0);
			}
			else
			{
				printf("���Ƿ�ѡ����2000�ֻ�ȡ���������һ�����ֲ������½ǻ�ø�����\n����ѡ�񸴻��ظ�2;\n�����¿�ʼ��Ϸ����ظ�1��\n��С�������㣬�ظ�3�о�ϲ��\n");
				do {
					c = _getch();

				} while (!(c == '2' || c == '3' || c == '1'));
			}
			continue;
		}
		while (c == '2')
		{
			arr[0][0] = 0;
			arr[0][1] = 0;
			arr[0][2] = 0;
			arr[0][3] = 0;
			arr[3][0] = 1024;
			score -= 2000;
			game2();
			if (score < 2000)
			{
				printf("������1�Լ���������b���˳���Ϸ��\n");
				do {
					c = _getch();

				} while (!((c == '1') || (c == 'b')));
				if (c == 'b')
					exit(0);
			}
			else
			{
				printf("���Ƿ�ѡ�������2000���Ӷ�������һ�����ֲ������½ǻ�ø���,�õ����\n����ѡ�񸴻��ظ�2;\n�����¿�ʼ��Ϸ����ظ�1������b���˳���Ϸ��\n��С�������㣬�ظ�3�о�ϲ��\n");
				c = _getch();
			}
			continue;
		}
		while (c == '3')
		{
			printf("������һ������ĵ��ڲ�ͨ�������������룬���ܲ�һ����2048��\n��������������������������������������\n���ͷ�С���QQ��876918519������Ҫ������\n\nҪ�������ü���ظ�0���ʵ��˾�����1������b���˳���Ϸ����\n");
			do
			{
				a = _getch();
			} while (!(a == '1' || a == 'b' || a == '0'));

			if (a == 'b') exit(0);

			if (a == '0')
			{
				printf("������1�Լ���������b���˳���Ϸ��\n");
				do
				{
					c = _getch();
				} while (!(c == '1' || c == 'b'));
				if (c == 'b') exit(0);
			}

			else if (a == '1')
			{
				char code[50];
				printf("\n�����ģ��Ҳ���Ҫ���������룬��ô�����������������룺");
				scanf_s("%s", code);
				if (strcmp(code, "iama2048genius") == 0)
				{
					int i, j;
					for (i = 0; i < ROW; i++)
					{
						for (j = 0; j < COL; j++)
							arr[i][j] = 128;
					}
					score = 100000;
					game2();
					c = '4';
					printf("������1�Լ���������b���˳���Ϸ��\n");
					do {
						c = _getch();

					} while (!((c == '1') || (c == 'b')));
					if (c == 'b')
						exit(0);
				}
				else
				{
					printf("��Ϲ������²��Եģ�������ʵʵ��С���Ҫ������\n(Ҫ�ǲ�����˼Ҳ���������ǵĿͷ�С��QQ��2830904724Ҫ)\n\n�ٸ���һ����ͷѡ��Ļ���\n\n");
					printf("�Ƿ�ѡ����շ������Ӷ�������һ�����ֲ������½ǻ�ø���,���õ������������\n����ѡ�񸴻��ظ�2;\n�����¿�ʼ��Ϸ����ظ�1(����b���˳���Ϸ����\n3�ٿ���һ�£�������Ĳ���ҪǮ\n");
					do {
						c = _getch();
					} while (!(c == '2' || c == '1' || c == 'b' || c == '3'));
					if (c == 'b')
						exit(0);
				}
			}
			continue;
		}
	}
	printf("\n\t\t�����˳���Ϸ��\n");
}
int main()
{
	system("color E8");
	GAME();
	system("pause");
	return 0;
}



