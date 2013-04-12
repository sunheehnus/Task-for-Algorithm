/***********************************

	*******BTree的操作函数

	*******提供插入和删除函数，并包涵实现插入与删除所需的各种子函数

***********************************/
#include<stdio.h>
#include<stdlib.h>

#define MAX 64

struct BTree{int Key[MAX<<1];struct BTree *Child[MAX<<1];int Sum;char Isleaf;};

typedef struct BTree *pBtree,Btree;


//调整newRoot，使之包含一个元素（leftChild最大值），并将两个指针分别连接leftChild和rightChild，并更新根大小
void FixNewRoot(pBtree leftChild,pBtree newRoot,pBtree rightChild);


//把leftChild里一半的元素放到rightChild里，并更新两个子树大小
void FixChild(pBtree leftChild,pBtree rightChild);


//把rightChild插入到Root的pos位置下，并将pos位置的Key值用leftChild更新
void FixRoot(pBtree leftChild,pBtree Root,pBtree rightChild,int pos);


//把根节点分裂
pBtree SplitRoot(pBtree leftChild);


//创建一颗BTree
pBtree CreateBtree();


//在数组target中的l与u之间查找key，target[返回值]<=key
int Find(int target[],int l,int u,int key);


//p是否为叶子节点，是返回1，否返回0
int IsLeaf(pBtree p);


//把key值插入到p节点的pos位置
void InsertKeyToLeaf(pBtree p,int key,int pos);


//下溯时判断节点是否需要先进行分裂
int NeedSplit(pBtree p);


//分裂p的pos之前一位的子树，并将该子树的提升值放在p的pos处，新生成的孩子节点放在pos处
void SplitNode(pBtree p,int pos);


//一般的插入
void NormalInsert(pBtree p,int key);


//对根的插入，需特殊处理
pBtree SpecialInsert(pBtree root,int key);


//查看根节点是否不含任何元素且不是叶子节点，成立返回1，否则返回0
int IsWaste(pBtree Root);


//查看p的pos处的值是否等于key，是返回1，否则返回0
int Equal(pBtree p,int pos,int key);


//删除叶子节点p位置为pos处的值
void Delete(pBtree p,int pos);


//查看p所含的值是否不小于MAX，以便于操作，成立返回1，否则返回0
int NodeAvailable(pBtree p);


//以p树位置为pos的直接前继key替换pos处的值并返回key
int preUpdate(pBtree p,int pos);


//以p树位置为pos的直接后继key替换pos处值并返回key
int postUpdate(pBtree p,int pos);


//将rightChild于leftChild合并，并给中间预留一个空位
void UnionChild(pBtree leftChild,pBtree rightChild);


//以p树位置为pos值放在leftChild的中间位置，并删除位置为pos的值和指针
void UnionRoot(pBtree p,pBtree leftChild,int pos);


//以p树位置为pos的值与pos-1和pos处的子树合并，放入pos-1子树中
void Union(pBtree p,int pos);


//p树中是否存在pos位置的指针，存在返回1，否则返回0
int Exist(int pos,pBtree p);


//以p树left处指向的节点的最大值放到p的right处，将p的right处原始值插入p树right处指向的节点，并伴随相应的指针操作
void rightFix(int left,pBtree p,int right);


//以p树right处指向的节点的最小值放到p的right处，将p的right处原始值插入p树left处指向的节点，并伴随相应的指针操作
void leftFix(int left,pBtree p,int right);


//一般的插入操作，将key插入到以p为根的树中
void NormalDelete(pBtree p,int key);


//插入根的操作，将key插入到Root树中
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

