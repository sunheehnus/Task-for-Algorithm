#include<stdio.h>
#include<math.h>

#define DLENGTH 65536
#define WORDMAXLENGTH 20

char tmp[DLENGTH][WORDMAXLENGTH];
char D1[DLENGTH][WORDMAXLENGTH];
char D2[DLENGTH][WORDMAXLENGTH];
int rank[DLENGTH];
int total1[DLENGTH];
int total2[DLENGTH];

int cnt1,cnt2;
int cnt;

double DW1,DW2,DW12;

void Insert(char *tar)
{
	char *pnow;
	while(*tar)
	{
		if(*tar>='A'&&*tar<='Z'||*tar>='a'&&*tar<='z'||*tar>='0'&&*tar<='9')
		{
			pnow=&tmp[cnt][0];
			while(*tar>='A'&&*tar<='Z'||*tar>='a'&&*tar<='z'||*tar>='0'&&*tar<='9')
			{
				if(*tar>='A'&&*tar<='Z')
				{
					*pnow=*tar|0x20;
				}
				else
				{
					*pnow=*tar;
				}
				pnow++;
				tar++;
			}
			*pnow='\0';
			cnt++;
		}
		if(*tar=='\0')
		{
			return ;
		}
		tar++;
	}
}

int strCMP(char *a,char *b)
{
	while(*a&&*a==*b)
	{
		a++;
		b++;
	}
	if(*a=='\0'&&*b=='\0')
		return 0;
	return *a>*b?-1:1;
}

int CMP(int i1,int i2)
{
	return strCMP(&tmp[i1][0],&tmp[i2][0]);
}

void Quicksort(int l,int u)
{
	int i,j,mid,tmp;
	if(l<u)
	{
		i=l;
		j=u;
		mid=(l+u)>>1;
		tmp=rank[mid];
		rank[mid]=rank[l];
		while(i<j)
		{
			while(i<j&&CMP(tmp,rank[j])>=0)
				j--;
			rank[i]=rank[j];
			while(i<j&&CMP(tmp,rank[i])<=0)
				i++;
			rank[j]=rank[i];
		}
		rank[i]=tmp;
		Quicksort(l,i-1);
		Quicksort(i+1,u);
	}
}
void strCopy(char *s,char *t)
{
	while(*s)
	{
		*t++=*s++;
	}
	*t='\0';
}
int main()
{
	FILE *fin;
	char tar[32];
	int i,i1,i2;
	double angle;
	DW1=DW2=DW12=0;
	fin=fopen("D1.in", "r");
	cnt=0;
	while(fscanf(fin,"%s",tar)!=EOF)
	{
		Insert(tar);
	}
	for(i=0;i<cnt;i++)
	{
		rank[i]=i;
	}
	Quicksort(0,cnt-1);
	strCopy(&tmp[rank[0]][0],&D1[0][0]);
	cnt1=0;
	total1[0]++;
	for(i=1;i<cnt;i++)
	{
		if(strCMP(&tmp[rank[i]][0],&tmp[rank[i-1]][0])==0)
		{
			total1[cnt1]++;
		}
		else
		{
			cnt1++;
			strCopy(&tmp[rank[i]][0],&D1[cnt1][0]);
			total1[cnt1]++;
		}
	}
	for(i=0;i<=cnt1;i++)
	{
		DW1+=total1[i]*total1[i];
	}
	DW1=sqrt(DW1);
	fin=fopen("D2.in", "r");
	cnt=0;
	while(fscanf(fin,"%s",tar)!=EOF)
	{
		Insert(tar);
	}
	for(i=0;i<cnt;i++)
	{
		rank[i]=i;
	}
	Quicksort(0,cnt-1);
	strCopy(&tmp[rank[0]][0],&D2[0][0]);
	cnt2=0;
	total2[0]++;
	for(i=1;i<cnt;i++)
	{
		if(strCMP(&tmp[rank[i]][0],&tmp[rank[i-1]][0])==0)
		{
			total2[cnt2]++;
		}
		else
		{
			cnt2++;
			strCopy(&tmp[rank[i]][0],&D2[cnt2][0]);
			total2[cnt2]++;
		}
	}
	for(i=0;i<=cnt2;i++)
	{
		DW2+=total2[i]*total2[i];
	}
	DW2=sqrt(DW2);
	i1=i2=0;
	while(i1<=cnt1&&i2<=cnt2)
	{
		i=strCMP(&D1[i1][0],&D2[i2][0]);
		switch(i)
		{
		case -1:
			i2++;
			break;
		case 0:
			DW12+=total1[i1]*total2[i2];
			i1++;
			i2++;
			break;
		case 1:
			i1++;
			break;
		default:
			break;
		}
	}
	angle=acos(DW12/(DW1*DW2));
	printf("%lf\n",angle);
	return 0;
}