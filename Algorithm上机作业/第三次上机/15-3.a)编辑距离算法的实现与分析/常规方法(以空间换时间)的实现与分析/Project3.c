#include<stdio.h>
#include<stdlib.h>
#define MAX 4096

int copyCost,replaceCost,deleteCost,insertCost,twiddleCost,killCost;

char strSource[MAX],strTarget[MAX];

int minCost[MAX][MAX];

char minWay[MAX][MAX];

void Initialize(int sourceLength); //��ʼ��minCost[0][]��minWay[0][]

void Fill_In_minCost(int targetPos,int sourcePos);//����minCost[targetPos][sourcePos]��minWay[targetPos][sourcePos]��ֵ

void Endop(int targetLength,int sourceLength);//���KILL����

void Fill_All(int targetLength,int sourceLength);//��ɶ�minCost[][]��minWay[][]������

void Backtrack(int targetPos,int sourcePos);//����minWay[][]��ֵ����

void Find_Way(int targetLength,int sourceLength);//�ҵ�һ������·��

int strLen(char *a);//��aָ���ַ����ĳ���

int main()
{
	int sl,tl;
	printf("Twiddle�����Ļ��ѣ�");
	scanf("%d",&twiddleCost);
	printf("Copy�����Ļ��ѣ�");
	scanf("%d",&copyCost);
	printf("Replace�����Ļ��ѣ�");
	scanf("%d",&replaceCost);
	printf("Insert�����Ļ��ѣ�");
	scanf("%d",&insertCost);
	printf("Delete�����Ļ��ѣ�");
	scanf("%d",&deleteCost);	
	printf("Kill�����Ļ��ѣ�");
	scanf("%d",&killCost);
	printf("����Դ�ַ���:\n");
	scanf("%s",strSource+1);
	sl=strLen(strSource+1);
	printf("����Ŀ���ַ���:\n");
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
	printf("��С����Ϊ��%d\n",min);
	printf("������С���ѵķ���Ϊ��\n");
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