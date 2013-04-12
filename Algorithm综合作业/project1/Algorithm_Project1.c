#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define VERMAXSUM 1<<17
#define EDGMAXSUM 1<<17

char visit[VERMAXSUM],reach[VERMAXSUM];

int verSum;//节点总数
int edgSum;//变总数
int edges[EDGMAXSUM<<1];//存储边
int Heap[VERMAXSUM],heapsize,heappos[VERMAXSUM];
int prefix[VERMAXSUM];//构造路径所需
int Stack1[VERMAXSUM],Stack2[VERMAXSUM],Stack[VERMAXSUM],sp1,sp2,sp;

double cost[VERMAXSUM];//最小花费

struct Tmp{int pos1,pos2;}tmp[EDGMAXSUM];//缓存输入的边

struct Vertice{int pos,suffix,limit;char is;} vertices[VERMAXSUM];//节点


int start();//搜索编号最小的顶点
int next(int i);//搜索i位置的下一个顶点


double distance(int ver1,int ver2);//求两点之间的距离

/**********************堆操作**************************/
void Insert(int ver);
void Update(int ver);
int  HeapMin();
/*****************************************************/


/**********************栈操作*************************/
void push(int i);
int Empty();
void pop();
void push1(int i);
int Empty1();
void pop1();
void push2(int i);
int Empty2();
void pop2();
/*****************************************************/

int main()
{
	int i,j,k,pos,xtmp,ytmp,source,sink,curVer;
	FILE *fin  = fopen ("project1.in", "r");
	fscanf(fin,"%d %d",&verSum,&edgSum);

	for(i=0;i<verSum;i++)
	{
		fscanf(fin,"%d %d %d",&pos,&xtmp,&ytmp);
		vertices[pos].pos=(xtmp<<16)|ytmp;
		vertices[pos].is=1;
	}

	for(i=0;i<edgSum;i++)
	{
		fscanf(fin,"%d %d",&tmp[i].pos1,&tmp[i].pos2);
		vertices[tmp[i].pos1].limit++;
		vertices[tmp[i].pos2].limit++;
	}
	i=start();

	vertices[i].suffix=0;
	for(k=1;k<verSum;k++)
	{
		j=next(i);
		vertices[j].suffix=vertices[i].suffix+vertices[i].limit;
		vertices[i].limit=vertices[i].suffix;
		i=j;
	}
	vertices[i].limit=vertices[i].suffix;
	for(i=0;i<edgSum;i++)
	{
		edges[vertices[tmp[i].pos1].limit++]=tmp[i].pos2;
		edges[vertices[tmp[i].pos2].limit++]=tmp[i].pos1;
	}
	while(1)
	{
		printf("input two place:");
		scanf("%d %d",&source,&sink);
		visit[source]=reach[source]=1;
		heapsize=0;
		push1(source);
		push2(source);
		cost[source]=0;
		curVer=source;
		while(curVer!=sink)
		{
			for(i=vertices[curVer].suffix;i<vertices[curVer].limit;i++)
			{
				if(visit[edges[i]])
					continue;
				if(reach[edges[i]]==0)
				{
					cost[edges[i]]=cost[curVer]+distance(vertices[curVer].pos,vertices[edges[i]].pos);
					reach[edges[i]]=1;
					push2(edges[i]);
					Insert(edges[i]);
					prefix[edges[i]]=curVer;
				}
				else if(cost[edges[i]]>cost[curVer]+distance(vertices[curVer].pos,vertices[edges[i]].pos))
				{
					cost[edges[i]]=cost[curVer]+distance(vertices[curVer].pos,vertices[edges[i]].pos);
					Update(edges[i]);
					prefix[edges[i]]=curVer;
				}
			}
			if(heapsize==0)
			{
				break;
			}
			curVer=HeapMin();
			visit[curVer]=1;
			push1(curVer);
		}
		while(Empty1())
		{
			pop1();
		}
		while(Empty2())
		{
			pop2();
		}
		if(curVer==sink)
		{
			printf("distance:%lf\n",cost[sink]);
			while(curVer!=source)
			{
				push(curVer);
				curVer=prefix[curVer];
			}
			push(source);
			printf("route:");
			while(Empty())
			{
				pop();
			}
			printf("\n");
		}
		else
		{
			printf("NULL\n");
		}
	}
	return 0;
}
int start()
{
	int i;
	for(i=0;vertices[i].is==0;i++)
	{
		NULL;
	}
	return i;
}

int next(int i)
{
	for(i++;vertices[i].is==0;i++)
	{
		NULL;
	}
	return i;
}

double distance(int ver1,int ver2)
{
	double tmp1,tmp2;
	tmp1=((ver1&0xffff)-(ver2&0xffff))*((ver1&0xffff)-(ver2&0xffff));
	tmp2=((ver1>>16)-(ver2>>16))*((ver1>>16)-(ver2>>16));
	return sqrt(tmp1+tmp2);
}

void Insert(int ver)
{
	int i;
	heapsize++;
	for(i=heapsize;i>=2;i>>=1)
	{
		if(cost[ver]<cost[Heap[i>>1]])
		{
			Heap[i]=Heap[i>>1];
			heappos[Heap[i]]=i;
		}
		else
		{
			break;
		}
	}
	Heap[i]=ver;
	heappos[Heap[i]]=i;
}
void Update(int ver)
{
	int i,pos;
	pos=heappos[ver];
	for(i=pos;i>=2;i>>=1)
	{
		if(cost[ver]<cost[Heap[i>>1]])
		{
			Heap[i]=Heap[i>>1];
			heappos[Heap[i]]=i;
		}
		else
		{
			break;
		}
	}
	Heap[i]=ver;
	heappos[Heap[i]]=i;
}
int  HeapMin()
{
	int ver,result,i,j;
	result=Heap[1];
	ver=Heap[heapsize--];
	for(i=1;i<<1<=heapsize;i<<=1)
	{
		j=i<<1;
		if(j+1<=heapsize&&cost[Heap[i+1]]<cost[Heap[i]])
		{
			j++;
		}
		if(cost[ver]>cost[Heap[j]])
		{
			Heap[i]=Heap[j];
			heappos[Heap[i]]=i;
		}
		else
		{
			break;
		}
	}
	Heap[i]=ver;
	heappos[Heap[i]]=i;
	return result;
}

void push(int i)
{
	Stack[++sp]=i;
}
int Empty()
{
	return sp!=0;
}
void pop()
{
	printf("%d  ",Stack[sp--]);
}

void push1(int i)
{
	Stack1[++sp1]=i;
}
int Empty1()
{
	return sp1!=0;
}
void pop1()
{
	visit[Stack1[sp1--]]=0;
}
void push2(int i)
{
	Stack2[++sp2]=i;
}
int Empty2()
{
	return sp2!=0;
}
void pop2()
{
	reach[Stack2[sp2--]]=0;
}
/*
6 9
0 1000 2400
1 2800 3000
2 2400 2500
3 4000 0
4 4500 3800
5 6000 1500

  0 1
  0 3
  1 2
  1 4
  2 4
  2 3
  2 5
  3 5
  4 5
	0 5

*/