#include<stdio.h>
#include<stdlib.h>
#define SIZE 65536

int source[SIZE],temp[SIZE];

void Merge_Sort(int *s,int  *t,int l,int u)
{
	int i,j,mid,now;
	if(l==u)
		return;
	mid=(l+u)>>1;
	Merge_Sort(s,t,l,mid);
	Merge_Sort(s,t,mid+1,u);
	now=l;
	i=l;
	j=mid+1;
	while(i<=mid&&j<=u)
	{
		if(s[i]<s[j])
		{
			t[now++]=s[i++];	
		}
		else
		{
			t[now++]=s[j++];
		}
	}
	while(i<=mid)
	{
		t[now++]=s[i++];
	}
	while(j<=u)
	{
		t[now++]=s[j++];
	}
	for(i=l;i<=u;i++)
	{
		s[i]=t[i];
	}
}

int Exist(int *s,int target,int total)
{
	int i,j;
	i=0;
	j=total-1;
	while(i<j)
	{
		if(s[i]+s[j]<target)
		{
			i++;
		}
		else if(s[i]+s[j]>target)
		{
			j--;
		}
		else
		{
			printf("��������Ԫ��֮�ͷ���Ҫ��%d+%d=%d\n",s[i],s[j],target);
			return 0;
		}
	}
	return 1;
}

int main()
{
	int i,total,x;
	printf("�������ݵ�������");
	scanf("%d",&total);
	printf("���������Ԫ�ص��ܺͣ�");
	scanf("%d",&x);
	for(i=0;i<total;i++)
	{
		printf("�����%d�����ݣ�",i+1);
		scanf("%d",source+i);
	}
	Merge_Sort(source,temp,0,total-1);
	if(Exist(source,x,total))
	{
		printf("û������Ԫ��֮�ͷ���Ҫ��\n");
	}
	system("pause");
	return 0;
}