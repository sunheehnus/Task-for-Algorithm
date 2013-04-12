#include<stdio.h>
#include<stdlib.h>

#define SIZE 65536

int Target[SIZE],temp[SIZE];
int Sum(int *s,int  *t,int l,int u)
{
	int i,j,mid,now,sum;
	if(l==u)
		return 0;
	sum=0;
	mid=(l+u)>>1;
	sum+=Sum(s,t,l,mid);
	sum+=Sum(s,t,mid+1,u);
	now=l;
	i=l;
	j=mid+1;
	while(i<=mid&&j<=u)
	{
		if(s[i]<=s[j])
		{
			t[now++]=s[i++];	
		}
		else
		{
			sum+=mid-i+1;
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
	return sum;
}

int main()
{
	int i,total;
	printf("输入数据的总数：");
	scanf("%d",&total);
	for(i=0;i<total;i++)
	{	
		printf("输入第%d个数据：",i+1);
		scanf("%d",Target+i);
	}
	printf("逆序总数为:%d\n",Sum(Target,temp,0,total-1));
	system("pause");
	return 0;
}