#include<stdio.h>

#include<stdlib.h>

#define MAX 65536

int copyCost=1,replaceCost=2,deleteCost=4,insertCost=8,twiddleCost=16,killCost=-128;

char strSource[MAX],strTarget[MAX];

int minCost[3][MAX];

char minWay[MAX];

char Stack[MAX<<1];//ջ

int sp;//ջָ��

void IniZeroRow(int sourceLength);//��ʼ����0��

void IniFirstRow(int sourceLength);//��ʼ����1��

void Initialize(int targetLength,int sourceLength);//��ʼ��ǰ����,�������

void dp(int targetPos,int sourcePos);//����(targetPos,sourcePos)��

void DP(int targetLength,int sourceLength);//���²�����������еĳ���minCost[targetALength][sourceLength]

int strLen(char *a);//��aָ����ַ����ĳ���

int Find(int sourceLength);//���KILL����

void PUSH(char a);//��aѹ��Stackջ��

int main()
{
	int i,tl,sl,minPos;
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
	DP(tl,sl);
	for(i=0;i<sl;i++)
	{
		minCost[2][i]+=killCost;
	}
	minPos=Find(sl);
	/*************�Ӵ˿�ʼ����·��***************/
	if(minPos<sl) 
	{
		PUSH('K');
	}
	sl=minPos;
	while(sl!=0||tl!=0)//�ظ���⹹���·��
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

