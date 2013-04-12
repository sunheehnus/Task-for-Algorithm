/**********************************************************************************

**********************本程序为第二次上级作业

******************输入为数组大小，本程序用随机数填入数组的所有位置

***********************实现了O(n)建堆并排序
***********************实现了O(nlgn)建堆并排序
***********************实现了插入排序

******************输出体现了同一条件下(待排序数组完全相同)，三种排序实现的时间比较

**********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX  65536//数组大小

int Heap1[MAX];//用O(n)建堆并排序时使用的数组
int Heap2[MAX];//用O(nlgn)建堆并排序时使用的数组
int Insert[MAX];//插入排序时使用的数组

void Exchange(int heap[],int pos1,int pos2);//交换数组heap中的位置为pos1和pos2的两个元素

int NeedHeapfy(int heap[],int lev,int maxChild);//判断数组heap的以lev处的元素为根的堆是否符合最大堆性质，是返回1，否返回0

int MaxChild(int heap[],int lev,int sum);//返回数组heap中lev位置节点的左子树与右子树（如果存在）的较大的位置

void Heapfy(int heap[],int lev,int sum);//调整数组heap的以lev处元素为根的堆，使之成为最大堆

void Heap_Insertion(int heap[],int lev);//在最大堆heap的末端lev处插入元素，并调整使之符合最大堆性质

void  Insertion_sort(int insert[],int l,int u);//平凡插入排序

void Error(int sum);//如果三个已排序数组中存在错误（不是严格的单调不减），则输出相应的错误信息

int main()
{
	int i,sum;
	clock_t timeStart,timeEnd;
	srand(time(NULL));
	printf("请输入待排序数组的大小：");
	scanf("%d",&sum);
	for(i=1;i<=sum;i++)
	{
		Heap1[i]=rand();
		Heap2[i]=Heap1[i];
		Insert[i]=Heap1[i];
	}
	timeStart=clock();
	for(i=sum>>1;i>=1;i--)
	{
		Heapfy(Heap1,i,sum);
	}
	for(i=sum;i>1;i--)
	{
		Exchange(Heap1,i,1);
		Heapfy(Heap1,1,i-1);
	}
	timeEnd=clock();
	printf("Heapsort#1 complete. Time: %ldms\n",timeEnd-timeStart);
	timeStart=clock();
	for(i=2;i<=sum;i++)
	{
		Heap_Insertion(Heap2,i);
	}
	for(i=sum;i>1;i--)
	{
		Exchange(Heap2,i,1);
		Heapfy(Heap2,1,i-1);
	}
	timeEnd=clock();
	printf("Heapsort#2 complete. Time: %ldms\n",timeEnd-timeStart);
	timeStart=clock();
	Insertion_sort(Insert,1,sum);
	timeEnd=clock();
	printf("Insertsort complete. Time: %ldms\n",timeEnd-timeStart);
	Error(sum);
	system("pause");
	return 0;
}

void Exchange(int heap[],int pos1,int pos2)
{
	if(pos1==pos2)
		return;
	heap[pos1]^=heap[pos2];
	heap[pos2]^=heap[pos1];
	heap[pos1]^=heap[pos2];
}

int NeedHeapfy(int heap[],int lev,int maxChild)
{
	return heap[lev]<heap[maxChild];
}

int MaxChild(int heap[],int lev,int sum)
{
	int leftChild=lev<<1,rightChild=leftChild<sum?leftChild+1:leftChild;
	return heap[leftChild]<heap[rightChild]?rightChild:leftChild;
}

void Heapfy(int heap[],int lev,int sum)
{
	int maxChild;
	while(lev<<1<=sum)//判断lev是否为叶子节点，是则直接退出循环
	{
		maxChild=MaxChild(heap,lev,sum);
		if(NeedHeapfy(heap,lev,maxChild))
		{
			Exchange(heap,lev,maxChild);
			lev=maxChild;
		}
		else
		{
			return;
		}
	}
}

void Heap_Insertion(int heap[],int lev)
{
	int preNode;
	while((preNode=(lev>>1))>=1)
	{
		if(heap[preNode]>heap[lev])
		{
			return;
		}
		else
		{
			Exchange(heap,preNode,lev);
			lev=preNode;
		}	
	}
}

void  Insertion_sort(int insert[],int l,int u)
{
	int i,j,k,min;
	for(i=l;i<=u;i++)
	{
		min=insert[i];
		k=i;
		for(j=i;j<=u;j++)
		{
			if(insert[j]<min)
			{
				min=insert[j];
				k=j;
			}
		}
		Exchange(insert,i,k);
	}
}

void Error(int sum)
{
	int i;
	for(i=2;i<=sum;i++)
	{
		if(Heap1[i]<Heap1[i-1])
			printf("Heapsort #1 error\n");
		if(Heap2[i]<Heap2[i-1])
			printf("Heapsort #2 error\n");
		if(Insert[i]<Insert[i-1])
			printf("Insertsort error\n");
	}
}
