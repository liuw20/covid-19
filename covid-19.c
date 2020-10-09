#include<stdio.h>
#include <stdlib.h> 
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
	scanf("%d", &look_up);
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
			printf("请重新输入数据：\n");
		}
	} while (1);//对输入数据进行控制
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
			printf("请重新输入数据：\n");
		}
	} while (1);//对输入数据进行控制
	return look_up;
}
void main()
{

	int unit[13][4];
	for (int i = 0; i < 13; i++)
	{
		unit[i][0] = i;
	}//各个单元标号
	for (int i = 0; i < 13; i++)
	{
		unit[i][2] = 0;
	}//初始均不感染，置0
	int base_station[2][1] = { {0},{10} };//基站位置
	int infestor_start = infestor();//初始感染者位置
	for (int i = 0; i < 13; i++)
	{
		if (unit[i][0] == infestor_start)
		{
			unit[i][2] = 1;
			printf("%d为初始感染者\n", infestor_start);//初始感染者感染flag置1
		}
	}
	for (int i = 0; i < 13; i++)
	{
		if (unit[i][0] <= 2 || (unit[i][0] >= 8 && unit[i][0] <= 12))
		{
			unit[i][3] = 1;
		}
	}//只有进入基站通信范围内的单元才会被检测到
	int get_tract[13][14];
	get_tract[infestor_start][0] = 1;


	int way_tract[13][14];
	for (int k = 0; k < 13; k++)
	{
		way_tract[k][0] = k;
	}//记录每个单元的初始位置
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
				way_tract[j][i] = 100;//100代表未曾被基站记录到
				unit[j][3] = 0;
			}
		}//产生当天的运动路径，如果在基站范围内则被记录

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
		}//感染者会将当前所在位置的人感染,但是不在基站范围内，将不被检测。
	}
	printf("请选择查询功能：\n");
	printf("	1.查询指定人14天的运动轨迹\n	2.查询指定范围内的感染人数\n");
	int menu;
	scanf("%d", &menu);
	switch (menu)
	{
	case 1://实现对指定单元的运动轨迹查询
	{
		printf("请输入要查询运动轨迹的单元标号,输入范围在0-12之间，请问勿输入其他数据：\n");

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
		//		printf("请重新输入数据：\n");
		//	}
		//} while (1);//对输入数据进行控制
		int location = judge_location();
		printf("%d单元在十四天内的运行轨迹为：\n", location);
		for (int i = 0; i < 14; i++)
		{
			if (way_tract[location][i] == 100)
				printf("第%d天：未曾收到该单元今天的位置信息\n", i + 1);
			else
				printf("第%d天：该单元曾到%d单元\n", i + 1, way_tract[location][i]);
		}
	}break;
	case 2://实现对指定位置该天的周围的感染人数
	{
		printf("请输入所要查询的位置和日期，位置输入范围在0-12之间，日期输入范围在0-14之间\n");
		printf("日期（1-14）:\n");
		int day = judge_day();
		printf("位置（0-12）：\n");
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
			printf("该位置在该天周围1km内的感染人数为：%d", num);
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
			printf("该位置在该天周围1km内的感染人数为：%d", num);
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
			printf("该位置在该天周围1km内的感染人数为：%d", num);
		}
	}break;
	default:
		break;
	}

}
