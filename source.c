#define _CRT_SECURE_NO_WARNINGS
#pragma warning ( disable : 4996 )

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include "util.h"

#define MAX 1000

typedef struct AirList
{
	int number;		
	char name[10];
	int mileage;
	int year_count;
	int month_count;
	int day_count;
	int gap;
	double priority;

	struct AirList *left;
	struct AirList *right;

} AirList;
// ����ü�� �����Ѵ�. �� ����ü�� ���� 1��� ���λ����� ��ϵȴ�.

typedef struct Air
{
	struct AirList *Root;
}Air;
// ó���� ��Ʈ�� ������ ��Ʈ���� ������� ��µ��� �����̴�.

enum
{
	BLACK, DARK_BLUE, DARK_GREEN, DARK_SKYBLUE, DARK_RED, DARK_YOILET, DARK_YELLOW, GRAY, DARK_GRAY, BLUE, GREEN, SKYBLUE, RED, VIOLET, YELLOW, WHITE,
};
// ���󺯰濡 ���̴� ����ü�̴�.

void Deletebox()
{
	gotoxy(22, 18); printf("                                                       \n");
	gotoxy(22, 19); printf("                                                       \n");
	gotoxy(22, 20); printf("                                                       \n");
	gotoxy(22, 21); printf("                                                       \n");
}
// �޼����� ������ ĭ���� ������ �� ���� ��� �����ִ� �Լ��̴�.

void Init(Air *Air)
{
	Air->Root = NULL;
}
// ��Ʈ�� ���� null�� �ʱ�ȭ�Ѵ�.

void DisplayFile(AirList *Air)
{
	FILE *fp = fopen("AirList.txt", "a");
	fprintf(fp, "%d\t%s\t%d\t%d-%d-%d\n", Air->number, Air->name, Air->mileage, Air->year_count, Air->month_count, Air->day_count);
	fclose(fp);
}
// ������ȸ�� �������� ȭ�鿡 ��µɶ� �� ���� �̾���̱�� ȭ�鿡 ����ϴ� �Լ��̴�.

void Display(AirList *Air)
{
	if (Air != NULL)
	{
		Display(Air->left);
		DisplayFile(Air);
		printf("%30d  %15s  %15d  %15d-%d-%d\n", Air->number, Air->name, Air->mileage, Air->year_count, Air->month_count, Air->day_count);
		Display(Air->right);
	}

}
// ������ȸ�� �����̴�. ȭ�鿡 ��µɶ� ���� ���� ���Ͽ� ����ϱ� ���� DisplayFile�Լ��� �ִ�.

int Searchdelete(Air *Air, AirList List[], double pri, AirList** temp_point)
{
	AirList *now_point = Air->Root; //  now_point�� ��Ʈ��带 ������ �Ʒ� ������ �����Ѵ�.

	if (now_point == NULL) // �ƹ��͵� ���� ��
		return 0;

	while (1)
	{
		if (now_point->priority == pri) // pri ���̶� ������ 1�� ��ȯ�Ѵ�. �� �Լ��� if�� �ȿ� �������Ƿ� 1�� ��ȯ�ؼ� !�� ������ �ϸ� ���̵Ǿ� ���డ���ϴ�.
		{
			return 1;
		}

		else if (now_point->priority <= pri) // ������ �۰ų� ������ �����ϴ� ����
		{
			*temp_point = now_point;
			if (now_point->right == NULL)
				return 0;
			else
				now_point = now_point->right;
		}
		else // ������ ũ�� �����ϴ� ����
		{
			*temp_point = now_point;
			if (now_point->left == NULL)
				return 0;
			else
				now_point = now_point->left;
		}
	}

	return 0;

}

int Search(Air *Air, AirList List[],double pri, AirList** temp_point, int mile)  // ���� �켱���� ó���ϴ� �������� ����� ����.
{
	AirList *now_point = Air->Root;

	if (now_point == NULL)
		return 0;

	while(1) 
	{
			if (now_point->priority == pri && now_point->mileage == mile) // ���ϸ����� �켱������ ���� ���� ������ �����Ͽ� �Է����� �ʴ´�.
				return 1;

			else if (now_point->priority <= pri)
			{
				*temp_point = now_point;
				if (now_point->right == NULL)
					return 0;
				else
					now_point = now_point->right;
			}
			else
			{
				*temp_point = now_point;
				if (now_point->left == NULL)
					return 0;
				else
					now_point = now_point->left;
			}
	}
	
	return 0;
	
}


int Insert(Air *Air,AirList List[], int i)
{
	AirList *temp_point = NULL; // �ӽ÷� ����
	AirList *new_point = (AirList *)malloc(sizeof(AirList)); // ���� �Ҵ����� ���ο� �����͸� ����Ų��.
	
	

	new_point->number = List[i].number;
    strcpy(new_point->name, List[i].name);
	new_point->mileage = List[i].mileage;
	new_point->year_count = List[i].year_count;
	new_point->month_count = List[i].month_count;
	new_point->day_count = List[i].day_count;
	new_point->gap = List[i].gap;
	new_point->priority = List[i].priority;
	new_point->right = NULL;
	new_point->left = NULL;
	// ������ ���� new_point�� �ִ´�.
	
	if (new_point->number == 0) // �� ���� �ִ� ��� �����Ѵ�.
		return 0;

	if (Air->Root == NULL) 
	{
		Air->Root = new_point;
		return 0;
	}
	

	if (!Search(Air, List, List[i].priority, &temp_point, List[i].mileage))
	{
		if (temp_point->priority <= List[i].priority) {
			temp_point->right = new_point;
		}
		
		else {
			temp_point->left = new_point;

		}
	}

	return 0;
}


void AddInsert(Air *Air, AirList List[])
{
	gotoxy(25, 18); printf("������ȣ �̸� ���ϸ��� ���Գ⵵�� ���ʴ�� �Է��Ͻÿ�.");

	FILE *fp = fopen("AirList.txt", "a");

	AirList *New = (AirList *)malloc(sizeof(AirList));
	
	gotoxy(25, 19); scanf("%d  %s  %d  %d%d%d", &New->number, New->name, &New->mileage, &New->year_count, &New->month_count, &New->day_count);
	fprintf(fp, "%d\t%s\t%d\t\t%d-%d-%d", New->number, New->name, New->mileage, New->year_count, New->month_count, New->day_count);
	
	fclose(fp);
	Deletebox();
	
}
// ����ڷ� ���� �ش���׵��� �޾� ȭ�鿡 ����ϴ� �����̴�.

  
double Delete(Air *Air,AirList List[], double pri)
{

	AirList *now_point = Air->Root; // ���� ���
	AirList *p_point = NULL; // �θ� ���
	AirList *c_point = NULL; // �ڽ� ���
	AirList *temp_now_point = NULL;	// �ӽ� ���1
	AirList *temp_point = NULL; // �ӽ� ���2

	

	if (!Searchdelete(Air,List, pri, &temp_point))
		return 0;


	while (now_point->priority != pri)
	{
		if (pri > now_point->priority)
		{
			p_point = now_point;
			now_point = now_point->right;
		}
		else
		{
			p_point = now_point;
			now_point = now_point->left;
		}
		
	}
	// ��带 �Űܰ��� �ش���� ���� �����̴�.

	if (now_point->left == NULL && now_point->right == NULL) //�ڽ��� ���� ����̴�.
	{

		if (p_point->left == now_point)
			p_point->left = NULL;

		if (p_point->right == now_point)
			p_point->right = NULL;

		free(now_point);
		return 0;
	}

	if ((now_point->left == NULL && now_point->right != NULL)|| now_point->left != NULL && now_point->right == NULL)//�ڽ��� �ϳ��� ����̴�.
	{
		if (now_point->left != NULL)
			c_point = now_point->left;

		else
			c_point = now_point->right;

		if (p_point->left == now_point)
			p_point->left = c_point;

		else
			p_point->right = c_point;

		
		free(now_point);
		return 0;
	}

	if (now_point->left != NULL && now_point->right != NULL)//�ڽ��� ���� ����̴�.
	{
		temp_now_point = now_point;
		temp_now_point = temp_now_point->right;

		if (temp_now_point->left == NULL)
		{
			temp_point = now_point->left;
			c_point = temp_now_point;
			if (p_point->right == now_point)
			{
				p_point->right = c_point;
				c_point->left = temp_point;
			}
			else
			{
				p_point->left = c_point;
				c_point->left = temp_point;
			}
			
			free(now_point);
			return 0;
		}

		while (temp_now_point->left != NULL)
		{
			p_point = temp_now_point;
			temp_now_point = temp_now_point->left;
		}
		p_point->left = NULL;

		now_point->number = temp_now_point->number;
		strcpy(now_point->name, temp_now_point->name);
		now_point->mileage = temp_now_point->mileage;
		now_point->year_count = temp_now_point->year_count;
		now_point->month_count = temp_now_point->month_count;
		now_point->day_count = temp_now_point->day_count;
		now_point->gap = temp_now_point->gap;
		now_point->priority = temp_now_point->priority;
		 
		free(temp_now_point);
		
	}
	return 0;
}




int Monthcount(int month, int year)
{
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		return 31;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else if (month == 2 && ((year % 4 == 0) && (year % 100 != 0) || year % 400 == 0))
		return 29;
	else
		return 28;
}
// �� �޿� �ش��ϴ� �� ���� ������ ����� �� ���� ���ϴ� �Լ��̴�.

void Daybyday(int y, int m, int d, int **gap)
{
	struct tm* now;
	time_t now_t;
	time(&now_t);
	now = localtime(&now_t);

	int todayyear = now->tm_year + 1900;;
	int todaymonth = now->tm_mon + 1;
	int todaydate = now->tm_mday;

	int first = 0;
	int second = 0;
	

	for (int i = 1; i < m; i++)
	{
		first += Monthcount(i,y);
	}
	first += d;

	for (int i = 1; i < todaymonth; i++)
	{
		second += Monthcount(i, todayyear);
	}
	for (int i = y; i < todayyear; i++)
	{
		second += 365;
		if ((y % 4 == 0) && (y % 100 != 0) || y % 400 == 0)
			second++;
	}

	second += todaydate;

	**gap = second - first;

	
}
// ��¥ ���̸� ���ϴ� �Լ��̴�.


void Readtxt(Air *Air, AirList list[], int **txt_count, int *pricount)
{

	FILE *fp = fopen("AirList.txt", "r");

	int mile_max = 0; // ���ϸ��� �ִ밪
	int days_max = 0; // �ϼ��� �ִ밪


	if (fp == NULL)
	{	
		printf("������ �� �� �����ϴ�.");
		return ;
	}
	gotoxy(0, 30);

	
	
	for (int i = 0; !feof(fp); i++)
	{
		fscanf(fp,"%d %s %d %d %d %d", &list[i].number, list[i].name, &list[i].mileage, &list[i].year_count, &list[i].month_count, &list[i].day_count);

		if (list[i].month_count < 0 || list[i].day_count < 0)
		{
			list[i].month_count = -list[i].month_count;
			list[i].day_count = -list[i].day_count;
		} // �Է¹����� -�� �Բ� ������� ����� �ٲپ� ���ڸ� ������.
	    
		if (mile_max < list[i].mileage)
			mile_max = list[i].mileage;
		
		int ini = 0;
		int *gap = &ini;

	
		Daybyday(list[i].year_count, list[i].month_count, list[i].day_count, &gap);
		list[i].gap = *gap;

		if (days_max < list[i].gap)
			days_max = list[i].gap;
		
		(**txt_count)++;
					
	}



	fseek(fp, 0, SEEK_SET);

	
	


	for (int i = 0; !feof(fp); i++)
	{
		fscanf(fp, "%d %s %d %d %d %d", &list[i].number, list[i].name, &list[i].mileage, &list[i].year_count, &list[i].month_count, &list[i].day_count);
		if (list[i].month_count < 0 || list[i].day_count < 0)
		{
			list[i].month_count = -list[i].month_count;
			list[i].day_count = -list[i].day_count;
		}
		
			if(*pricount == 1)
				list[i].priority = -(list[i].number - ((double)list[i].mileage / mile_max * 10) - ((double)list[i].gap/ days_max * 5)); // ����ȯ
			else if(*pricount == 2)
				list[i].priority = -list[i].mileage;
			else if(*pricount ==3)
				list[i].priority = -list[i].gap;
		
		Insert(Air, list, i); // ��忡 ����
	}
		
	
	fclose(fp);
	
}



void Deletetxt(Air *Air, AirList List[], double num, int **txt_count)
{
	
	int yesno;
	Deletebox();
	
	gotoxy(25, 18); printf("����� �����Ͻðڽ��ϱ�?");
	gotoxy(25, 19); printf("1. YES  2. NO ");
	gotoxy(50, 18); scanf("%d", &yesno);


	if (yesno == 1)
	{
		Delete(Air, List, num);
		(**txt_count)--;
	}
		

	else if(yesno == 2)
	{
		gotoxy(25, 21); printf("�ʱ�ȭ������ ���ư��ϴ�.");
		Sleep(2000);
		return;
	}

	else 
	{
		gotoxy(25, 21);  printf("�߸��� �Է��Դϴ�. �ʱ�ȭ������ ���ư��ϴ�.");
		Sleep(2000);
		return ;
	}
		
	

}
// �������� ���� �ϴ� �Լ��̴�.

void Searchtxt(Air *Air,AirList List[], int **txt_count)
{
	int situ;
	int num;
	int cnt = 0;
	char name[10] = { 0 };

	gotoxy(25, 18);	
	printf("�˻��� ����� �Է��Ͻÿ�  1. ������ȣ  2, �̸�");
	scanf("%d", &situ);
	gotoxy(0, 29);
	

	if (situ == 1)
	{
		gotoxy(25, 19);
		printf("������ȣ�� �Է��Ͻÿ�.  ");
		scanf("%d", &num);

		for (int i = 0; i < **txt_count; i++)
		{
			if (List[i].number == num)
			{

				gotoxy(30, 24);
				printf("%d  %15s  %15d  %15d-%d-%d\n", List[i].number, List[i].name, List[i].mileage, List[i].year_count, List[i].month_count, List[i].day_count);
				cnt++;

				Deletetxt(Air, List, List[i].priority, txt_count);
				gotoxy(30, 24);
				printf("                                                                           ");
			}

		}
	}
	
	else if (situ == 2)
	{
		AirList *temp = (AirList *)malloc(sizeof(AirList));

		gotoxy(25, 19);
		printf("�̸��� �Է��Ͻÿ�.  ");
		scanf("%s", &name);

		for (int i = 0; i < **txt_count; i++)
		{
					
			if (strcmp(List[i].name, name)==0)
			{

				gotoxy(30, 24);
				printf("%d  %15s  %15d  %15d-%d-%d\n", List[i].number, List[i].name, List[i].mileage, List[i].year_count, List[i].month_count, List[i].day_count);
				cnt++;

				Deletetxt(Air, List, List[i].priority, txt_count);
				gotoxy(30, 24);
				printf("                                                                           ");
			}

		}
	}


	else
	{
		gotoxy(25, 19);
		printf("�߸��� �Է��Դϴ�. �ʱ�ȭ������ ���ư��ϴ�.");
		Sleep(2000);
		Deletebox();
		return;
	}
		


	if (cnt == 0)
	{
		gotoxy(25, 20);
		printf("��ȿ�� �����Ͱ� �����ϴ�.                                  ");
		Sleep(2000);
		gotoxy(25, 20);  printf("                                                           ");
	}
			

	Deletebox();
	

}
// ������ �������� �˻��� �ǽ������� ���� �Լ��̴�.


void Setchangecolor()
{
	int colornum;
	gotoxy(25, 18); printf("������ ������ ��ȣ�� �Է��Ͻÿ�.");
	gotoxy(22, 19); printf(" 0. BLACK       1. DARK_BLUE,   2. DARK_GREEN  3. DARK_SKYBLUE 4. DARK_RED");
	gotoxy(22, 20); printf(" 5. DARK_YOILET 6. DARK_YELLOW  7. GRAY        8. DARK_GRAY    9. BLUE     ");
	gotoxy(22, 21); printf(" 10.GREEN       11. SKYBLUE     12.RED         13. VIOLET      14. YELLOW  ");
	gotoxy(22, 22); printf(" 15.WHITE       16. ��������    17.�ڷΰ���"); 
	gotoxy(60, 18); scanf("%d", &colornum);

	switch (colornum)
	{
		case 0:
			colorchange(BLACK);
			break;
		case 1:
			colorchange(DARK_BLUE);
			break;
		case 2:
			colorchange(DARK_GREEN);
			break;
		case 3:
			colorchange(DARK_SKYBLUE);
			break;
		case 4:
			colorchange(DARK_RED);
			break;
		case 5:
			colorchange(DARK_YOILET);
			break;
		case 6:
			colorchange(DARK_YELLOW);
			break;
		case 7:
			colorchange(GRAY);
			break;
		case 8:
			colorchange(DARK_GRAY);
			break;
		case 9:
			colorchange(BLUE);
			break;
		case 10:
			colorchange(GREEN);
			break;
		case 11:
			colorchange(SKYBLUE);
			break;
		case 12:
			colorchange(RED);
			break;
		case 13:
			colorchange(VIOLET);
			break;
		case 14:
			colorchange(YELLOW);
			break;
		case 15:
			colorchange(WHITE);
			break;
		case 16:
			colorchange(rand() % 16);
			break;
		case 17:
			gotoxy(68, 22);  printf("�ʱ�ȭ������ ���ư��ϴ�.");
			Sleep(2000);
			break;

	}

	Deletebox();

}
// ���� ������ ����ڷκ��� �޴� �Լ��̴�.

void Whatispri(int* pricount)
{
	int pricountset;

	gotoxy(25, 18); printf("������ �켱������ �����Ͻÿ�.");
	gotoxy(25, 19); printf("1. �켱���� ��������");
	gotoxy(25, 20); printf("2. ���ϸ��� ��������");
	gotoxy(25, 21); printf("3. ��¥���� ��������");

	gotoxy(55, 18); scanf("%d", &pricountset);
	*pricount = pricountset;

	
	Deletebox();

	
}
// �켱������ �ٲ� �� ����ڷκ��� �޾� ������ �ٲٴ� �Լ��̴�.

int Startmain(int pos)
{
	gotoxy(34, 5); printf("J  o  n  g  W  o  o  k ");
	gotoxy(44, 8); printf("A  i  r  L  i  n  e");
	gotoxy(54, 11); printf("S  y  s  t  e  m");

	gotoxy(22, 13); printf("ESC�� ������ ����˴ϴ�.");
	gotoxy(20, 14); printf("����������������������������������������������������������������������������������������������������������������������������������������������������������");

	gotoxy(20, 25); printf("����������������������������������������������������������������������������������������������������������������������������������������������������������");

	gotoxy(pos, 16); printf("��");

	gotoxy(24, 16); printf("�˻�/�����ϱ�");
	gotoxy(39, 16); printf("�߰��ϱ�");
	gotoxy(54, 16); printf("���󺯰��ϱ�");
	gotoxy(69, 16); printf("����ϱ�");
	gotoxy(84, 16); printf("�켱��������");

	struct tm* now;
	time_t now_t;
	time(&now_t);
	now = localtime(&now_t);

	gotoxy(75, 13); printf("%d��   %d��   %d��", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	return pos;
}
// �޴��� �ٸ��ִ� �Լ��̴�.


void Option(AirList List[], int count)
{
	Air Air;
	Init(&Air); // �ʱ�ȭ

	int firstcount = 0;
	int *txt_count = &firstcount; // ����ƽ���� �����ص� �ǳ� ���������͸� �����غ��� �; ���� �̷��� �����غô�.
	static int pricount = 1; // �켱������ ���������� ���� �����̴�.
	
	
		if (count == 1) // �˻�,���� ���
		{
			system("cls");
			Startmain(22 + 15 * (count - 1));
			Readtxt(&Air, List, &txt_count, &pricount);
			Searchtxt(&Air, List, &txt_count);
			FILE *fp = fopen("AirList.txt", "w");
			fclose(fp);
			gotoxy(0, 30);
			Display(Air.Root);
			gotoxy(0, 0);

		} // �����ϰ� �ٷ� ���

		else if (count == 2) // �߰����
		{
			system("cls");
			Startmain(22 + 15 * (count - 1));
			Readtxt(&Air, List, &txt_count, &pricount);
			AddInsert(&Air, List);
			txt_count = &firstcount;
			Readtxt(&Air, List, &txt_count, &pricount);
			FILE *fp = fopen("AirList.txt", "w");
			fclose(fp);
			gotoxy(0, 30);
			Display(Air.Root);
			gotoxy(0, 0);
		}// �����ϰ� �ٷ� ���

		else if (count == 3) // ���� ���� ���
		{
			system("cls");
			Startmain(22 + 15 * (count - 1));
			Setchangecolor();
			system("cls");
			Startmain(22 + 15 * (count - 1));
		}

		else if (count == 4)// ��� ���
		{
			
			system("cls");
			Startmain(22 + 15 * (count - 1));
			Readtxt(&Air, List, &txt_count, &pricount);
			gotoxy(0, 30);
			FILE *fp = fopen("AirList.txt", "w");
			fclose(fp);
			Display(Air.Root);
			gotoxy(0, 0);
		}


		else if (count == 5) // �켱���� ���� ���
		{
			system("cls");
			Startmain(22 + 15 * (count - 1));
			Whatispri(&pricount);
			gotoxy(0, 0); printf("%d", pricount);
		}
	
	

}


int main()
{
	
	SetCursorVisible(0); // Ŀ���� �����Ÿ��� �ʰ� �ϱ� �����̴�.
	int pos = 22;
	Startmain(pos);
	AirList List[MAX] = { 0 };
	int key = 0;
	int count = 1;


	while (1) {
		key = getch();
		if (key == 77) {
			gotoxy(pos, 16); printf("��");
			if (pos < 82)
			{
				pos += 15;
				count++;
			}
				
			gotoxy(pos, 16); printf("��");

		}
		else if (key == 75) {
			gotoxy(pos, 16); printf("��");
			if (pos > 22)
			{
				pos -= 15;
				count--;
			}
				
			gotoxy(pos, 16); printf("��");

		}
		else if (key == 13)
		{
			Option(List, count);
					
		}
		else if (key == 27)
		{		
				system("cls"); // ȭ���� ��� ���� �� ����
				break;
		}
			
	}
	return 0;
	
}