/**********************************************************************************

**********************������Ϊ�ڶ����ϼ���ҵ

******************����Ϊ�����С����������������������������λ��

***********************ʵ����O(n)���Ѳ�����
***********************ʵ����O(nlgn)���Ѳ�����
***********************ʵ���˲�������

******************���������ͬһ������(������������ȫ��ͬ)����������ʵ�ֵ�ʱ��Ƚ�

**********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX  65536//�����С

int Heap1[MAX];//��O(n)���Ѳ�����ʱʹ�õ�����
int Heap2[MAX];//��O(nlgn)���Ѳ�����ʱʹ�õ�����
int Insert[MAX];//��������ʱʹ�õ�����

void Exchange(int heap[],int pos1,int pos2);//��������heap�е�λ��Ϊpos1��pos2������Ԫ��

int NeedHeapfy(int heap[],int lev,int maxChild);//�ж�����heap����lev����Ԫ��Ϊ���Ķ��Ƿ�����������ʣ��Ƿ���1���񷵻�0

int MaxChild(int heap[],int lev,int sum);//��������heap��levλ�ýڵ������������������������ڣ��Ľϴ��λ��

void Heapfy(int heap[],int lev,int sum);//��������heap����lev��Ԫ��Ϊ���Ķѣ�ʹ֮��Ϊ����

void Heap_Insertion(int heap[],int lev);//������heap��ĩ��lev������Ԫ�أ�������ʹ֮������������

void  Insertion_sort(int insert[],int l,int u);//ƽ����������

void Error(int sum);//������������������д��ڴ��󣨲����ϸ�ĵ������������������Ӧ�Ĵ�����Ϣ

int main()
{
	int i,sum;
	clock_t timeStart,timeEnd;
	srand(time(NULL));
	printf("���������������Ĵ�С��");
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
	while(lev<<1<=sum)//�ж�lev�Ƿ�ΪҶ�ӽڵ㣬����ֱ���˳�ѭ��
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
