#include<stdio.h>
#include <stdlib.h> 
#include <conio.h> 
#include <time.h> 
#include<math.h>
int infestor()
{
	srand((unsigned)time(NULL));
	int a;
	a = rand() % 13;
	return a;
}
int random_way()
{
	int a;
	a = rand() % 13;
	return a;
}
int input()
{
	int look_up = 0;
	scanf_s("%d", &look_up);
	return look_up;

}
int judge_location()
{
	int look_up;
	int	t;
	do
	{
		t = input();
		if (t >= 0 && t <= 12)
		{
			look_up = t;
			break;
		}
		else
		{
			printf("�������������ݣ�\n");
		}
	} while (1);//���������ݽ��п���
	return look_up;
}
int judge_day()
{
	int look_up;
	int	t;
	do
	{
		t = input();
		if (t >= 1 && t <= 14)
		{
			look_up = t;
			break;
		}
		else
		{
			printf("�������������ݣ�\n");
		}
	} while (1);//���������ݽ��п���
	return look_up;
}
void main()
{

	int unit[13][4];
	for (int i = 0; i < 13; i++)
	{
		unit[i][0] = i;
	}//������Ԫ���
	for (int i = 0; i < 13; i++)
	{
		unit[i][2] = 0;
	}//��ʼ������Ⱦ����0
	int base_station[2][1] = { {0},{10} };//��վλ��
	int infestor_start = infestor();//��ʼ��Ⱦ��λ��
	for (int i = 0; i < 13; i++)
	{
		if (unit[i][0] == infestor_start)
		{
			unit[i][2] = 1;
			printf("%dΪ��ʼ��Ⱦ��\n", infestor_start);//��ʼ��Ⱦ�߸�Ⱦflag��1
		}
	}
	for (int i = 0; i < 13; i++)
	{
		if (unit[i][0] <= 2 || (unit[i][0] >= 8 && unit[i][0] <= 12))
		{
			unit[i][3] = 1;
		}
	}//ֻ�н����վͨ�ŷ�Χ�ڵĵ�Ԫ�Żᱻ��⵽
	int get_tract[13][14];
	get_tract[infestor_start][0] = 1;


	int way_tract[13][14];
	for (int k = 0; k < 13; k++)
	{
		way_tract[k][0] = k;
	}//��¼ÿ����Ԫ�ĳ�ʼλ��
	srand((unsigned)time(NULL));

	for (int i = 1; i < 14; i++)
	{

		for (int j = 0; j < 13; j++)
		{
			unit[j][1] = random_way();
			if (unit[j][1] <= 2 || (unit[i][0] >= 8 && unit[i][0] <= 12))
			{
				way_tract[j][i] = unit[j][1];
				unit[j][3] = 1;
			}
			else
			{
				way_tract[j][i] = 100;//100����δ������վ��¼��
				unit[j][3] = 0;
			}
		}//����������˶�·��������ڻ�վ��Χ���򱻼�¼

		for (int k = 0; k < 13; k++)
		{
			if (unit[k][2] == 1)
			{
				for (int l = 0; l < 13; l++)
				{
					if (unit[l][1] == k && unit[l][3] == 1)
					{
						unit[l][2] = 1;
						get_tract[k][i] = 1;
					}
				}
			}
		}//��Ⱦ�߻Ὣ��ǰ����λ�õ��˸�Ⱦ,���ǲ��ڻ�վ��Χ�ڣ���������⡣
	}
	printf("��ѡ���ѯ���ܣ�\n");
	printf("	1.��ѯָ����14����˶��켣\n	2.��ѯָ����Χ�ڵĸ�Ⱦ����\n");
	int menu;
	scanf_s("%d", &menu);
	switch (menu)
	{
	case 1://ʵ�ֶ�ָ����Ԫ���˶��켣��ѯ
	{
		printf("������Ҫ��ѯ�˶��켣�ĵ�Ԫ���,���뷶Χ��0-12֮�䣬�����������������ݣ�\n");

		//int look_up;
		//int	t;
		//do
		//{
		//	t = input();
		//	if (t >= 0 && t <= 12)
		//	{
		//		look_up = t;
		//		break;
		//	}
		//	else
		//	{
		//		printf("�������������ݣ�\n");
		//	}
		//} while (1);//���������ݽ��п���
		int location = judge_location();
		printf("%d��Ԫ��ʮ�����ڵ����й켣Ϊ��\n", location);
		for (int i = 0; i < 14; i++)
		{
			if (way_tract[location][i] == 100)
				printf("��%d�죺δ���յ��õ�Ԫ�����λ����Ϣ\n", i + 1);
			else
				printf("��%d�죺�õ�Ԫ����%d��Ԫ\n", i + 1, way_tract[location][i]);
		}
	}break;
	case 2://ʵ�ֶ�ָ��λ�ø������Χ�ĸ�Ⱦ����
	{
		printf("��������Ҫ��ѯ��λ�ú����ڣ�λ�����뷶Χ��0-12֮�䣬�������뷶Χ��0-14֮��\n");
		printf("���ڣ�1-14��:\n");
		int day = judge_day();
		printf("λ�ã�0-12����\n");
		int location = judge_location();
		if (location > 0 && location < 12)
		{
			int num = 0;
			for (int i = 1; i < 12; i++)
			{

				if (way_tract[i][day] == location)
				{
					int t = i;

					if (unit[t][2] == 1)
					{
						num++;
					}
				}
			}
			for (int i = 1; i < 12; i++)
			{
				if (way_tract[i][day] == location - 1)
				{
					int t = i;

					if (unit[t][2] == 1)
					{
						num++;
					}
				}
			}
			for (int i = 0; i < 12; i++)
			{
				if (way_tract[i][day] == location + 1)
				{
					int t = i;

					if (unit[t][2] == 1)
					{
						num++;
					}
				}
			}
			printf("��λ���ڸ�����Χ1km�ڵĸ�Ⱦ����Ϊ��%d", num);
		}



		if (location == 0)
		{
			int num = 0;
			for (int i = 1; i < 12; i++)
			{

				if (way_tract[i][day] == location)
				{
					int t = i;

					if (unit[t][2] == 1)
					{
						num++;
					}
				}
			}
			for (int i = 1; i < 12; i++)
			{

				if (way_tract[i][day] == location + 1)
				{
					int t = i;

					if (unit[t][2] == 1)
					{
						num++;
					}
				}
			}
			printf("��λ���ڸ�����Χ1km�ڵĸ�Ⱦ����Ϊ��%d", num);
		}
		if (location == 12)
		{
			int num = 0;
			for (int i = 1; i < 12; i++)
			{

				if (way_tract[i][day] == location)
				{
					int t = i;

					if (unit[t][2] == 1)
					{
						num++;
					}
				}
			}
			for (int i = 1; i < 12; i++)
			{

				if (way_tract[i][day] == location -1)
				{
					int t = i;

					if (unit[t][2] == 1)
					{
						num++;
					}
				}
			}
			printf("��λ���ڸ�����Χ1km�ڵĸ�Ⱦ����Ϊ��%d", num);
		}
	}break;
	default:
		break;
	}

}