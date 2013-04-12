#include<stdio.h>
#include<stdlib.h>
#define MAX 4096

int copyCost,replaceCost,deleteCost,insertCost,twiddleCost,killCost;

char strSource[MAX],strTarget[MAX];

int minCost[MAX][MAX];

char minWay[MAX][MAX];

void Initialize(int sourceLength); //初始化minCost[0][]与minWay[0][]

void Fill_In_minCost(int targetPos,int sourcePos);//填入minCost[targetPos][sourcePos]与minWay[targetPos][sourcePos]的值

void Endop(int targetLength,int sourceLength);//完成KILL操作

void Fill_All(int targetLength,int sourceLength);//完成对minCost[][]与minWay[][]的填入

void Backtrack(int targetPos,int sourcePos);//根据minWay[][]的值回溯

void Find_Way(int targetLength,int sourceLength);//找到一条构造路径

int strLen(char *a);//求a指向字符串的长度

int main()
{
	int sl,tl;
	printf("Twiddle操作的花费：");
	scanf("%d",&twiddleCost);
	printf("Copy操作的花费：");
	scanf("%d",&copyCost);
	printf("Replace操作的花费：");
	scanf("%d",&replaceCost);
	printf("Insert操作的花费：");
	scanf("%d",&insertCost);
	printf("Delete操作的花费：");
	scanf("%d",&deleteCost);	
	printf("Kill操作的花费：");
	scanf("%d",&killCost);
	printf("输入源字符串:\n");
	scanf("%s",strSource+1);
	sl=strLen(strSource+1);
	printf("输入目标字符串:\n");
	scanf("%s",strTarget+1);
	tl=strLen(strTarget+1);
	Fill_All(tl,sl);
	Find_Way(tl,sl);
	system("pause");
	return 0;
}

void Initialize(int sourceLength)
{
	int i,mincost;
	for(i=0,mincost=0;i<=sourceLength;i++,mincost+=deleteCost)
	{
		minCost[0][i]=mincost;
		minWay[0][i]='D';
	}
	minWay[0][0]='S';
}

void Fill_In_minCost(int targetPos,int sourcePos)
{
	int mincost,cost;
	mincost=minCost[targetPos-1][sourcePos]+insertCost;
	minWay[targetPos][sourcePos]='I';
	if(sourcePos>0)
	{
		cost=minCost[targetPos][sourcePos-1]+deleteCost;
		if(cost<mincost)
		{
			mincost=cost;
			minWay[targetPos][sourcePos]='D';
		}
		if(strSource[sourcePos]==strTarget[targetPos])
		{
			cost=minCost[targetPos-1][sourcePos-1]+copyCost;
			if(cost<mincost)
			{
				mincost=cost;
				minWay[targetPos][sourcePos]='C';
			}
		}
		cost=minCost[targetPos-1][sourcePos-1]+replaceCost;
		if(cost<mincost)
		{
			mincost=cost;
			minWay[targetPos][sourcePos]='R';
		}
	}
	if(sourcePos>1&&targetPos>1&&strSource[sourcePos]==strTarget[targetPos-1]&&strSource[sourcePos-1]==strTarget[targetPos])
	{
		cost=minCost[targetPos-2][sourcePos-2]+twiddleCost;
		if(cost<mincost)
		{
			mincost=cost;
			minWay[targetPos][sourcePos]='T';
		}
	}
	minCost[targetPos][sourcePos]=mincost;
}

void Endop(int targetLength,int sourceLength)
{
	int i;
	for(i=0;i<sourceLength;i++)
	{
		minCost[targetLength][i]+=killCost;
	}
}

void Fill_All(int targetLength,int sourceLength)
{
	int i,j;
	Initialize(sourceLength);
	for(i=1;i<=targetLength;i++)
	{
		for(j=0;j<=sourceLength;j++)
		{
			Fill_In_minCost(i,j);
		}
	}
	Endop(targetLength,sourceLength);
}

void Backtrack(int targetPos,int sourcePos)
{
	switch(minWay[targetPos][sourcePos])
	{
	case 'I':
		Backtrack(targetPos-1,sourcePos);
		printf("Insert ");
		break;
	case 'D':
		Backtrack(targetPos,sourcePos-1);
		printf("Delete ");
		break;
	case 'C':
		Backtrack(targetPos-1,sourcePos-1);
		printf("Copy ");
		break;
	case 'R':
		Backtrack(targetPos-1,sourcePos-1);
		printf("Replace ");
		break;
	case 'T':
		Backtrack(targetPos-2,sourcePos-2);
		printf("Twiddle ");
		break;
	default:
		break;
	}
}

void Find_Way(int targetLength,int sourceLength)
{
	int i,min,minpos;
	for(i=0,min=minCost[targetLength][i],minpos=i;i<=sourceLength;i++)
	{
		if(minCost[targetLength][i]<min)
		{
			min=minCost[targetLength][i];
			minpos=i;
		}
	}
	printf("最小花费为：%d\n",min);
	printf("构造最小花费的方法为：\n");
	Backtrack(targetLength,minpos);
	if(minpos!=sourceLength)
		printf("KILL ");
	printf("\n");
}

int strLen(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++);
	return i;
}