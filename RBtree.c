#include<stdio.h>
#include<stdlib.h>

struct RBtree {struct RBtree *p,*l,*r;int key;char color;};

struct RBtree nil={NULL,NULL,NULL,0,1},*Nil=&nil;

struct RBtree * Initialize()
{
	return Nil;
}

Left_Rotate(struct RBtree * t)
{
	struct RBtree * p;
	p=t->p;
	p->r=t->l;
	t->l->p=p;
	t->l=p;
	t->p=p->p;
	if(p->p->l==p)
		p->p->l=t;
	else
		p->p->r=t;
	p->p=t;
}

Right_Rotate(struct RBtree * t)
{
	struct RBtree * p;
	p=t->p;
	p->l=t->r;
	t->r->p=p;
	t->r=p;
	t->p=p->p;
	if(p->p->l==p)
		p->p->l=t;
	else
		p->p->r=t;
	p->p=t;
}

Left_Rotate1(struct RBtree * t)
{
	struct RBtree * p;
	p=t->r;
	t->r=p->l;
	if(p->l!=Nil)
		p->l->p=t;
	p->l=t;
	if(p!=Nil)
		p->p=t->p;
	if(t->p->l==t)
		t->p->l=p;
	else
		t->p->r=p;
	if(t!=Nil)
		t->p=p;
}

Right_Rotate1(struct RBtree * t)
{
	struct RBtree * p;
	p=t->l;
	t->l=p->r;
	if(p->r!=Nil)
		p->r->p=t;
	p->r=t;
	if(p!=Nil)
		p->p=t->p;
	if(t->p->l==t)
		t->p->l=p;
	else
		t->p->r=p;
	if(t!=Nil)
		t->p=p;
}

struct RBtree * RB_Insert_Fix(struct RBtree * T,struct RBtree * fix)
{
	struct RBtree * parent, *uncle ,*grandparent;
	parent=fix->p;
	while(parent!=Nil&&parent->color==0)
	{
		grandparent=parent->p;
		if(grandparent->l==parent)
		{
			uncle = grandparent->r;
			if(uncle->color==0)
			{
				uncle->color=parent->color=1;
				fix=grandparent;
				fix->color=0;
				parent=fix->p;
			}
			else
			{
				if(fix==parent->r)
				{
					Left_Rotate(fix);
					fix=fix->l;
					parent=fix->p;
					grandparent=parent->p;
				}
				grandparent->color=0;
				parent->color=1;
				Right_Rotate(parent);
			}
		}
		else
		{
			uncle = grandparent->l;
			if(uncle->color==0)
			{
				uncle->color=parent->color=1;
				fix=grandparent;
				fix->color=0;
				parent=fix->p;
			}
			else
			{
				if(fix==parent->l)
				{
					Right_Rotate(fix);
					fix=fix->r;
					parent=fix->p;
					grandparent=parent->p;
				}
				grandparent->color=0;
				parent->color=1;
				Left_Rotate(parent);
			}
		}
	}
	while(T->p!=Nil)
		T=T->p;
	T->color=1;
	return T;
}

struct RBtree * RB_Insert(struct RBtree * T,int key)
{
	struct RBtree * tmp=Nil,* target,* ori=T;
	target = (struct RBtree *)malloc(sizeof(struct RBtree));
	target->color=0;
	target->key=key;
	target->l=target->r=Nil;
	while(T!=Nil)
	{
		tmp=T;
		if(T->key>key)
		{
			T=T->l;
		}
		else
		{
			T=T->r;
		}
	}
	target->p=tmp;
	if(tmp!=Nil&&tmp->key>key)
	{
		tmp->l=target;
	}
	else if(tmp!=Nil&&tmp->key<=key)
	{
		tmp->r=target;
	}
	return RB_Insert_Fix(tmp==Nil?target:ori,target);
}
struct RBtree * RB_Pre(struct RBtree * t)
{
	t=t->l;
	while(t->r!=Nil)
		t=t->r;
	return t;
}

struct RBtree * RB_Delete_Fix(struct RBtree * T,struct RBtree * fix)
{
	while(T!=Nil&&fix->p!=Nil&&fix->color==1)
	{
		if(fix==fix->p->l)
		{
			if(fix->p->r->color==0)
			{
				Left_Rotate1(fix->p);
				fix->p->color=0;
				fix->p->p->color=1;
			}
			if(fix->p->r->l->color==1&&fix->p->r->r->color==1)
			{
				fix->p->r->color=0;
				fix=fix->p;
				continue;
			}
			else if(fix->p->r->r->color==1)
			{
				Right_Rotate1(fix->p->r);
				fix->p->r->color=1;
 				fix->p->r->r->color=0;
			}
			Left_Rotate1(fix->p);
			fix->p->p->color=fix->p->color;
			fix->p->p->r->color=1;
			fix->p->color=1;
			fix=fix->p->p;
			goto MJ;
		}
		else
		{
			if(fix->p->l->color==0)
			{
				Right_Rotate1(fix->p);
				fix->p->color=0;
				fix->p->p->color=1;
			}
			if(fix->p->l->l->color==1&&fix->p->l->r->color==1)
			{
				fix->p->l->color=0;
				fix=fix->p;
				continue;
			}
			else if(fix->p->l->l->color==1)
			{
				Left_Rotate1(fix->p->l);
				fix->p->l->color=1;
				fix->p->l->l->color=0;
			}
			Right_Rotate1(fix->p);
			fix->p->p->color=fix->p->color;
			fix->p->p->l->color=1;
			fix->p->color=1;
			fix=fix->p->p;
			goto MJ;
		}
	}
	fix->color=1;
MJ:
	while(T->p!=Nil)
		T=T->p;
	T->color=1;
	return T;
}

struct RBtree * RB_Delete(struct RBtree * root,int key)
{
	struct RBtree * pre,* suc,* ori=root;
	pre=Nil;
	while(root!=Nil&&root->key!=key)
	{
		if(root->key<key)
		{
			root=root->r;
		}
		else
		{
			root=root->l;
		}
	}
	if(root==Nil)
		return ori;
	if(root->l==Nil)
	{
		pre=root->p;
		suc=root->r;
		suc->p=root->p;
		if(pre->l==root)
			pre->l=suc;
		else
			pre->r=suc;
		if(root==ori)
			ori=suc;
	}
	else if(root->r==Nil)
	{
		pre=root->p;
		suc=root->l;
		suc->p=root->p;
		if(pre->l==root)
			pre->l=suc;
		else
			pre->r=suc;
		if(root==ori)
			ori=suc;
	}
	else
	{
		suc=RB_Pre(root);
		pre=suc->p;
		suc->l->p=pre;
		if(pre->r==suc)
			pre->r=suc->l;
		else
			pre->l=suc->l;
		root->key=suc->key;
		root=suc;
		suc=suc->l;
	}
	if(root->color==1)
	{
		ori=RB_Delete_Fix(ori,suc);
	}
	free(root);
	return ori;
}

void Print(struct RBtree * t,int rank)
{
	int i;
	if(t->l!=Nil)
		Print(t->l,rank+1);
	for(i=1;i<=rank;i++)
		printf("   ");
	printf("%3d",t->key);
	if(t->color==0)
		printf("r\n");
	else
		printf("b\n");
	if(t->r!=Nil)
		Print(t->r,rank+1);
}

int main()
{
	struct RBtree * RBT;
	int i;
	RBT=Initialize();
	for(i=1;i<=127;i++)
	{
		RBT=RB_Insert(RBT,i);
	//	Print(RBT,0);
	//	printf("\n\n");
	}
	Print(RBT,0);
	for(i=1;i<=10000;i++)
	{
		RBT=RB_Delete(RBT,i);
	//	Print(RBT,0);
	//	printf("\n\n");
	}
	Print(RBT,0);
	return 0;
}