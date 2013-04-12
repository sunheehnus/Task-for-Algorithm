#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 1<<20

char str1[MAX];
char str2[MAX];

int tmp[2][MAX];

int values[41][41];

char choices[41][41];

char out[2][42];

void Initialize(int len)
{
	int i,j;
	for(i=0,j=0;i<=len;i++,j+=2)
	{
		tmp[0][i]=j;
	}
}
void Update(int len1,int now,int select)
{
	int i;
	tmp[select][0]=tmp[(select+1)&1][0]+2;
	for(i=1;i<=len1;i++)
	{
		if(str1[i]==str2[now])
			tmp[select][i]=tmp[(select+1)&1][i-1];
		else
			tmp[select][i]=tmp[(select+1)&1][i-1]+1;
		if(tmp[(select+1)&1][i]+2<tmp[select][i])
			tmp[select][i]=tmp[(select+1)&1][i]+2;
		if(tmp[select][i-1]+2<tmp[select][i])
			tmp[select][i]=tmp[select][i-1]+2;
	}
}

int Compute(int len1,int len2)
{
	int i,select;
	Initialize(len1);
	for(i=1,select=1;i<=len2;i++,select=(select+1)&1)
	{
		Update(len1,i,select);
	}
	select=(select+1)&1;
	return tmp[select][len1];
}

int Memo(int i,int j)
{
	int min=0x7FFFFFFF;
	if(values[i][j]!=-1)
		return values[i][j];
	if(str1[i+1]==str2[j+1])
	{
		if(Memo(i+1,j+1)<min)
		{
			min=Memo(i+1,j+1);
			choices[i][j]='\\';
		}
	}
	else
	{
		if(Memo(i+1,j+1)+1<min)
		{
			min=Memo(i+1,j+1)+1;
			choices[i][j]='\\';
		}
	}

	if(Memo(i+1,j)+2<min)
	{
		min=Memo(i+1,j)+2;
		choices[i][j]='|';
	}
	if(Memo(i,j+1)+2<min)
	{
		min=Memo(i,j+1)+2;
		choices[i][j]='-';
	}
	return values[i][j]=min;
}

void ini(int len1,int len2)
{
	int i,cost;
	memset(values,-1,sizeof(values));
	values[len1][len2]=0;
	choices[len1][len2]='.';
	for(i=len1-1,cost=2;i>=0;i--,cost+=2)
	{
		values[i][len2]=cost;
		choices[i][len2]='|';
	}
	for(i=len2-1,cost=2;i>=0;i--,cost+=2)
	{
		values[len1][i]=cost;
		choices[len1][i]='-';
	}
}

void outvalues(int len1,int len2)
{
	int i,j;
	printf("****************a table of optimal values****************\n");
	printf("        ");
	for(i=0;i<=len2;i++)
	{
		printf("%4d",i);
	}
	printf("\n        ");
	for(i=0;i<=len2;i++)
	{
		printf("   %c",str2[i+1]);
	}
	printf("\n");
	for(i=0;i<=len1;i++)
	{
		printf("%4d   %c",i,str1[i+1]);
		for(j=0;j<=len2;j++)
		{
			printf("%4d",values[i][j]);
		}
		printf("\n");
	}
}

void outchoices(int len1,int len2)
{
	int i,j;
	printf("****************a table of optimal choices****************\n");
	printf("    ");
	for(i=0;i<=len2;i++)
	{
		printf("%2d",i);
	}
	printf("\n    ");
	for(i=0;i<=len2;i++)
	{
		printf(" %c",str2[i+1]);
	}
	printf("\n");
	for(i=0;i<=len1;i++)
	{
		printf("%2d %c",i,str1[i+1]);
		for(j=0;j<=len2;j++)
		{
			printf(" %c",choices[i][j]);
		}
		printf("\n");
	}
}

void outalignment()
{
	int i,j,cnt;
	printf("****************an optimal alignment****************\n");
	i=j=cnt=0;
	while(choices[i][j]!='.')
	{
		switch(choices[i][j])
		{
		case '\\':
			out[0][cnt]=str1[i+1];
			out[1][cnt]=str2[j+1];
			i++;
			j++;
			break;
		case '|':
			out[0][cnt]=str1[i+1];
			out[1][cnt]=' ';
			i++;
			break;
		case '-':
			out[0][cnt]=' ';
			out[1][cnt]=str2[j+1];
			j++;
			break;
		default:
			break;
		}
		cnt++;
	}
	printf("%s\n%s\n",&out[0][0],&out[1][0]);
}

void output(int len1,int len2)
{
	ini(len1,len2);
	Memo(0,0);
	outvalues(len1,len2);
	outchoices(len1,len2);
	outalignment(len1,len2);
}

int main()
{
	int len1,len2;
	scanf("%s",str1+1);
	scanf("%s",str2+1);
	len1=strlen(str1+1);
	len2=strlen(str2+1);
	printf("edit-distance:%d\n",Compute(len1,len2));
	if(len1<=40&&len2<=40)
	{
		output(len1,len2);
	}
	system("pause");
	return 0;
}
//AACAGTTACC TAAGGTCA
