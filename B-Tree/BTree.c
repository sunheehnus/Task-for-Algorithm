/***********************************

	*******BTree�Ĳ�������

	*******�ṩ�����ɾ��������������ʵ�ֲ�����ɾ������ĸ����Ӻ���

***********************************/
#include<stdio.h>
#include<stdlib.h>

#define MAX 64

struct BTree{int Key[MAX<<1];struct BTree *Child[MAX<<1];int Sum;char Isleaf;};

typedef struct BTree *pBtree,Btree;


//����newRoot��ʹ֮����һ��Ԫ�أ�leftChild���ֵ������������ָ��ֱ�����leftChild��rightChild�������¸���С
void FixNewRoot(pBtree leftChild,pBtree newRoot,pBtree rightChild);


//��leftChild��һ���Ԫ�طŵ�rightChild�����������������С
void FixChild(pBtree leftChild,pBtree rightChild);


//��rightChild���뵽Root��posλ���£�����posλ�õ�Keyֵ��leftChild����
void FixRoot(pBtree leftChild,pBtree Root,pBtree rightChild,int pos);


//�Ѹ��ڵ����
pBtree SplitRoot(pBtree leftChild);


//����һ��BTree
pBtree CreateBtree();


//������target�е�l��u֮�����key��target[����ֵ]<=key
int Find(int target[],int l,int u,int key);


//p�Ƿ�ΪҶ�ӽڵ㣬�Ƿ���1���񷵻�0
int IsLeaf(pBtree p);


//��keyֵ���뵽p�ڵ��posλ��
void InsertKeyToLeaf(pBtree p,int key,int pos);


//����ʱ�жϽڵ��Ƿ���Ҫ�Ƚ��з���
int NeedSplit(pBtree p);


//����p��pos֮ǰһλ������������������������ֵ����p��pos���������ɵĺ��ӽڵ����pos��
void SplitNode(pBtree p,int pos);


//һ��Ĳ���
void NormalInsert(pBtree p,int key);


//�Ը��Ĳ��룬�����⴦��
pBtree SpecialInsert(pBtree root,int key);


//�鿴���ڵ��Ƿ񲻺��κ�Ԫ���Ҳ���Ҷ�ӽڵ㣬��������1�����򷵻�0
int IsWaste(pBtree Root);


//�鿴p��pos����ֵ�Ƿ����key���Ƿ���1�����򷵻�0
int Equal(pBtree p,int pos,int key);


//ɾ��Ҷ�ӽڵ�pλ��Ϊpos����ֵ
void Delete(pBtree p,int pos);


//�鿴p������ֵ�Ƿ�С��MAX���Ա��ڲ�������������1�����򷵻�0
int NodeAvailable(pBtree p);


//��p��λ��Ϊpos��ֱ��ǰ��key�滻pos����ֵ������key
int preUpdate(pBtree p,int pos);


//��p��λ��Ϊpos��ֱ�Ӻ��key�滻pos��ֵ������key
int postUpdate(pBtree p,int pos);


//��rightChild��leftChild�ϲ��������м�Ԥ��һ����λ
void UnionChild(pBtree leftChild,pBtree rightChild);


//��p��λ��Ϊposֵ����leftChild���м�λ�ã���ɾ��λ��Ϊpos��ֵ��ָ��
void UnionRoot(pBtree p,pBtree leftChild,int pos);


//��p��λ��Ϊpos��ֵ��pos-1��pos���������ϲ�������pos-1������
void Union(pBtree p,int pos);


//p�����Ƿ����posλ�õ�ָ�룬���ڷ���1�����򷵻�0
int Exist(int pos,pBtree p);


//��p��left��ָ��Ľڵ�����ֵ�ŵ�p��right������p��right��ԭʼֵ����p��right��ָ��Ľڵ㣬��������Ӧ��ָ�����
void rightFix(int left,pBtree p,int right);


//��p��right��ָ��Ľڵ����Сֵ�ŵ�p��right������p��right��ԭʼֵ����p��left��ָ��Ľڵ㣬��������Ӧ��ָ�����
void leftFix(int left,pBtree p,int right);


//һ��Ĳ����������key���뵽��pΪ��������
void NormalDelete(pBtree p,int key);


//������Ĳ�������key���뵽Root����
pBtree SpecialDelete(pBtree Root,int key);



int main()
{
	int i;
	pBtree ROOT;
	ROOT=CreateBtree();
	for(i=1000000;i>=1;i--)
	{
		ROOT=SpecialInsert(ROOT,i);
	}
	for(i=1;i<=1000000;i++)
	{
		ROOT=SpecialDelete(ROOT,i);
	}
 	return 0;
}


void FixNewRoot(pBtree leftChild,pBtree newRoot,pBtree rightChild)
{
	newRoot->Sum=1;
	newRoot->Isleaf=0;
	newRoot->Key[1]=leftChild->Key[MAX];
	newRoot->Child[0]=leftChild;
	newRoot->Child[1]=rightChild;
}

void FixChild(pBtree leftChild,pBtree rightChild)
{
	int i;
	leftChild->Sum=rightChild->Sum=MAX-1;
	rightChild->Isleaf=leftChild->Isleaf;
	for(i=1;i<MAX;i++)
	{
		rightChild->Key[i]=leftChild->Key[MAX+i];
	}
	if(leftChild->Isleaf==0)
	{
		for(i=0;i<MAX;i++)
		{
			rightChild->Child[i]=leftChild->Child[i+MAX];
		}
	}
}

void FixRoot(pBtree leftChild,pBtree Root,pBtree rightChild,int pos)
{
	int i;
	for(i=Root->Sum;i>=pos;i--)
	{
		Root->Child[i+1]=Root->Child[i];
		Root->Key[i+1]=Root->Key[i];
	}
	Root->Child[pos]=rightChild;
	Root->Key[pos]=leftChild->Key[MAX];
	Root->Sum++;
}

pBtree SplitRoot(pBtree leftChild)
{
	pBtree newRoot,rightChild;
	newRoot=(pBtree)malloc(sizeof(Btree));
	rightChild=(pBtree)malloc(sizeof(Btree));
	FixNewRoot(leftChild,newRoot,rightChild);
	FixChild(leftChild,rightChild);
	return newRoot;
}

pBtree CreateBtree()
{
	pBtree p;
	p=(pBtree)malloc(sizeof(Btree));
	p->Isleaf=1;
	p->Sum=0;
	return p;
}

int Find(int target[],int l,int u,int key)
{
	int mid;
	while(l<=u)
	{
		mid=(l+u)>>1;
		if(target[mid]>=key)
			u=mid-1;
		else
			l=mid+1;
	}
	return l;
}

int IsLeaf(pBtree p)
{
	return p->Isleaf==1;
}

void InsertKeyToLeaf(pBtree p,int key,int pos)
{
	int i;
	for(i=p->Sum;i>=pos;i--)
	{
		p->Key[i+1]=p->Key[i];
	}
	p->Key[pos]=key;
	p->Sum++;
}

int NeedSplit(pBtree p)
{
	return p->Sum==(MAX<<1)-1;
}

void SplitNode(pBtree p,int pos)
{
	pBtree leftChild,rightChild;
	leftChild=p->Child[pos-1];
	rightChild=(pBtree)malloc(sizeof(Btree));
	FixChild(leftChild,rightChild);
	FixRoot(leftChild,p,rightChild,pos);
}

void NormalInsert(pBtree p,int key)
{
	int pos;
	pos=Find(p->Key,1,p->Sum,key);
	if(IsLeaf(p))
	{
		InsertKeyToLeaf(p,key,pos);
	}
	else
	{
		if(NeedSplit(p->Child[pos-1]))
		{
			SplitNode(p,pos);
			pos=Find(p->Key,1,p->Sum,key);
		}
		NormalInsert(p->Child[pos-1],key);
	}
}


pBtree SpecialInsert(pBtree root,int key)
{
	if(root->Sum==(MAX<<1)-1)
	{
		root=SplitRoot(root);
	}
	NormalInsert(root,key);
	return root;
}

int IsWaste(pBtree Root)
{
	return Root->Sum==0&&Root->Isleaf==0;
}

int Equal(pBtree p,int pos,int key)
{
	return p->Key[pos]==key;
}

void Delete(pBtree p,int pos)
{
	int i;
	for(i=pos;i<=p->Sum;i++)
	{
		p->Key[i]=p->Key[i+1];
	}
	p->Sum--;
}

int NodeAvailable(pBtree p)
{
	return p->Sum>=MAX;
}

int preUpdate(pBtree p,int pos)
{
	pBtree ppre=p->Child[pos-1];
	int key=ppre->Key[ppre->Sum];
	p->Key[pos]=key;
	return key;
}

int postUpdate(pBtree p,int pos)
{
	pBtree ppost=p->Child[pos];
	int key=ppost->Key[1];
	p->Key[pos]=key;
	return key;
}

void UnionChild(pBtree leftChild,pBtree rightChild)
{
	int i;
	for(i=1;i<MAX;i++)
	{
		leftChild->Key[i+MAX]=rightChild->Key[i];
	}
	if(IsLeaf(leftChild)==0)
	{
		for(i=0;i<MAX;i++)
		{
			leftChild->Child[i+MAX]=rightChild->Child[i];
		}
	}
	free(rightChild);
	leftChild->Sum<<=1;
}

void UnionRoot(pBtree p,pBtree leftChild,int pos)
{
	int i;
	leftChild->Key[MAX]=p->Key[pos];
	for(i=pos;i<=p->Sum;i++)
	{
		p->Key[i]=p->Key[i+1];
		p->Child[i]=p->Child[i+1];
	}
	p->Sum--;
	leftChild->Sum++;
}

void Union(pBtree p,int pos)
{
	pBtree leftChild,rightChild;
	leftChild=p->Child[pos-1];
	rightChild=p->Child[pos];
	UnionChild(leftChild,rightChild);
	UnionRoot(p,leftChild,pos);
}

int Exist(int pos,pBtree p)
{
	return pos>=0&&pos<=p->Sum; 
}

void rightFix(int left,pBtree p,int right)
{
	int i;
	pBtree leftChild,rightChild;
	leftChild=p->Child[left];
	rightChild=p->Child[right];
	for(i=MAX-1;i>=1;i--)
	{
		rightChild->Key[i+1]=rightChild->Key[i];
	}
	if(IsLeaf(rightChild)==0)
	{
		for(i=MAX-1;i>=0;i--)
		{
			rightChild->Child[i+1]=rightChild->Child[i];
		}
		rightChild->Child[0]=leftChild->Child[leftChild->Sum];
	}
	rightChild->Key[1]=p->Key[right];
	p->Key[right]=leftChild->Key[leftChild->Sum];
	leftChild->Sum--;
	rightChild->Sum++;
}

void leftFix(int left,pBtree p,int right)
{
	int i;
	pBtree leftChild,rightChild;
	leftChild=p->Child[left];
	rightChild=p->Child[right];
	leftChild->Sum++;
	leftChild->Key[leftChild->Sum]=p->Key[right];
	p->Key[right]=rightChild->Key[1];
	for(i=1;i<=rightChild->Sum;i++)
	{
		rightChild->Key[i]=rightChild->Key[i+1];
	}
	if(IsLeaf(rightChild)==0)
	{
		leftChild->Child[leftChild->Sum]=rightChild->Child[0];
		for(i=0;i<=rightChild->Sum;i++)
		{
			rightChild->Child[i]=rightChild->Child[i+1];
		}
	}
	rightChild->Sum--;
}

void NormalDelete(pBtree p,int key)
{
	int pos;
	pos=Find(p->Key,1,p->Sum,key);
	if(IsLeaf(p))
	{
		if(Equal(p,pos,key))
		{
			Delete(p,pos);
		}
		return;
	}
	else
	{
		if(Equal(p,pos,key))
		{
			if(NodeAvailable(p->Child[pos-1]))
			{
				key=preUpdate(p,pos);
				NormalDelete(p->Child[pos-1],key);
			}
			else if(NodeAvailable(p->Child[pos]))
			{
				key=postUpdate(p,pos);
				NormalDelete(p->Child[pos],key);
			}
			else
			{
				Union(p,pos);
				NormalDelete(p->Child[pos-1],key);
			}
		}
		else
		{
			if(NodeAvailable(p->Child[pos-1]))
			{
				NormalDelete(p->Child[pos-1],key);
			}
			else
			{
				if(Exist(pos-2,p)&&NodeAvailable(p->Child[pos-2]))
				{
					rightFix(pos-2,p,pos-1);
					NormalDelete(p->Child[pos-1],key);
				}
				else if(Exist(pos,p)&&NodeAvailable(p->Child[pos]))
				{
					leftFix(pos-1,p,pos);
					NormalDelete(p->Child[pos-1],key);
				}
				else if(Exist(pos-2,p))
				{
					Union(p,pos-1);
					NormalDelete(p->Child[pos-2],key);
				}
				else
				{
					Union(p,pos);
					NormalDelete(p->Child[pos-1],key);
				}
			}
		}
	}
}

pBtree SpecialDelete(pBtree Root,int key)
{
	pBtree pWaste;
	if(Root->Sum==0)
		return Root;
	NormalDelete(Root,key);
	if(IsWaste(Root))
	{
		pWaste=Root;
		Root=Root->Child[0];
		free(pWaste);
	}
	return Root;
}

