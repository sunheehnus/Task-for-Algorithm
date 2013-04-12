#include<stdio.h>

#include<stdlib.h>

#define MAX 65536

int copyCost=1,replaceCost=2,deleteCost=4,insertCost=8,twiddleCost=16,killCost=-128;

char strSource[MAX],strTarget[MAX];

int minCost[3][MAX];

char minWay[MAX];

char Stack[MAX<<1];//栈

int sp;//栈指针

void IniZeroRow(int sourceLength);//初始化第0行

void IniFirstRow(int sourceLength);//初始化第1行

void Initialize(int targetLength,int sourceLength);//初始化前两行,如果存在

void dp(int targetPos,int sourcePos);//更新(targetPos,sourcePos)处

void DP(int targetLength,int sourceLength);//更新并保留最后两行的常规minCost[targetALength][sourceLength]

int strLen(char *a);//求a指向的字符串的长度

int Find(int sourceLength);//完成KILL操作

void PUSH(char a);//将a压入Stack栈中

int main()
{
	int i,tl,sl,minPos;
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
	DP(tl,sl);
	for(i=0;i<sl;i++)
	{
		minCost[2][i]+=killCost;
	}
	minPos=Find(sl);
	/*************从此开始构造路线***************/
	if(minPos<sl) 
	{
		PUSH('K');
	}
	sl=minPos;
	while(sl!=0||tl!=0)//重复求解构造的路线
	{
		Initialize(tl,sl);
		DP(tl,sl);
		PUSH(minWay[sl]);
		switch(minWay[sl])
		{
		case 'I':
			tl--;
			break;
		case 'D':
			sl--;
			break;
		case 'C':
		case 'R':
			tl--;
			sl--;
			break;
		case 'T':
			tl-=2;
			sl-=2;
		default:
			break;

		}
	}
	while(sp)
	{
		printf("%c ",Stack[--sp]);
	}
	printf("\n");
	system("pause");
	return 0;
}

void IniZeroRow(int sourceLength)
{
	int i,mincost;
	for(i=0,mincost=0;i<=sourceLength;i++,mincost+=deleteCost)
	{
		minCost[0][i]=mincost;
		minWay[i]='D';
	}
	minWay[0]='S';
}

void IniFirstRow(int sourceLength)
{
	int i,mincost,cost;
	for(i=0;i<=sourceLength;i++)
	{
		mincost=minCost[0][i]+insertCost;
		minWay[i]='I';
		if(i>0)
		{
			cost=minCost[1][i-1]+deleteCost;
			if(cost<mincost)
			{
				mincost=cost;
				minWay[i]='D';
			}
			if(strSource[i]==strTarget[1])
			{
				cost=minCost[0][i-1]+copyCost;
				if(cost<mincost)
				{
					mincost=cost;
					minWay[i]='C';
				}
			}
			cost=minCost[0][i-1]+replaceCost;
			if(cost<mincost)
			{
				mincost=cost;
				minWay[i]='R';
			}
		}
		minCost[1][i]=mincost;
	}
}

void Initialize(int targetLength,int sourceLength)
{
	IniZeroRow(sourceLength);
	if(targetLength>0)
	{
		IniFirstRow(sourceLength);
	}
}

void dp(int targetPos,int sourcePos)
{
	int mincost,cost;
	mincost=minCost[1][sourcePos]+insertCost;
	minWay[sourcePos]='I';
	if(sourcePos>0)
	{
		cost=minCost[2][sourcePos-1]+deleteCost;
		if(cost<mincost)
		{
			mincost=cost;
			minWay[sourcePos]='D';
		}
		if(strSource[sourcePos]==strTarget[targetPos])
		{
			cost=minCost[1][sourcePos-1]+copyCost;
			if(cost<mincost)
			{
				mincost=cost;
				minWay[sourcePos]='C';
			}
		}
		cost=minCost[1][sourcePos-1]+replaceCost;
		if(cost<mincost)
		{
			mincost=cost;
			minWay[sourcePos]='R';
		}
	}
	if(sourcePos>1&&targetPos>1&&strSource[sourcePos]==strTarget[targetPos-1]&&strSource[sourcePos-1]==strTarget[targetPos])
	{
		cost=minCost[0][sourcePos-2]+twiddleCost;
		if(cost<mincost)
		{
			mincost=cost;
			minWay[sourcePos]='T';
		}
	}
	minCost[2][sourcePos]=mincost;
}

void DP(int targetLength,int sourceLength)
{
	int i,j;
	Initialize(targetLength,sourceLength);
	for(i=2;i<=targetLength;i++)
	{
		for(j=0;j<=sourceLength;j++)
		{
			dp(i,j);
		}
		for(j=0;j<=sourceLength;j++)
		{
			minCost[0][j]=minCost[1][j];
			minCost[1][j]=minCost[2][j];
		}
	}
}

int strLen(char *a)
{
	int i;
	for(i=0;a[i]!='\0';i++);
	return i;
}

int Find(int sourceLength)
{
	int i,min,j;
	for(i=0,j=0,min=minCost[2][i];i<=sourceLength;i++)
	{
		if(minCost[2][i]<min)
		{
			min=minCost[2][i];
			j=i;
		}
	}
	return j;
}

void PUSH(char a)
{
	Stack[sp]=a;
	sp++;
}

