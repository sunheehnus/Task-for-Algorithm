/*
	*调整newRoot，使之包含一个元素（leftChild最大值），并将两个指针分别连接leftChild和rightChild，并更新根大小
*/
void FixNewRoot(pBtree leftChild,pBtree newRoot,pBtree rightChild);


/*
	*把leftChild里一半的元素放到rightChild里，并更新两个子树大小
*/
void FixChild(pBtree leftChild,pBtree rightChild);


/*
	*把rightChild插入到Root的pos位置下，并将pos位置的Key值用leftChild更新
*/
void FixRoot(pBtree leftChild,pBtree Root,pBtree rightChild,int pos);


/*
	*把根节点分裂
*/
pBtree SplitRoot(pBtree leftChild);


/*
	*创建一颗BTree
*/
pBtree CreateBtree();


/*
	*在数组target中的l与u之间查找key，target[返回值]<=key
*/
int Find(int target[],int l,int u,int key);


/*
	*p是否为叶子节点，是返回1，否返回0
*/
int IsLeaf(pBtree p);


/*
	*把key值插入到p节点的pos位置
*/
void InsertKeyToLeaf(pBtree p,int key,int pos);


/*
	*下溯时判断节点是否需要先进行分裂
*/
int NeedSplit(pBtree p);


/*
	*分裂p的pos之前一位的子树，并将该子树的提升值放在p的pos处，新生成的孩子节点放在pos处
*/
void SplitNode(pBtree p,int pos);


/*
	*一般的插入
*/
void NormalInsert(pBtree p,int key);


/*
	*对根的插入，需特殊处理
*/
pBtree SpecialInsert(pBtree root,int key);


/*
	*查看根节点是否不含任何元素且不是叶子节点，成立返回1，否则返回0
*/
int IsWaste(pBtree Root);


/*
	*查看p的pos处的值是否等于key，是返回1，否则返回0
*/
int Equal(pBtree p,int pos,int key);


/*
	*删除叶子节点p位置为pos处的值
*/
void Delete(pBtree p,int pos);


/*
	*查看p所含的值是否不小于MAX，以便于操作，成立返回1，否则返回0
*/
int NodeAvailable(pBtree p);


/*
	*以p树位置为pos的直接前继key替换pos处的值并返回key
*/
int preUpdate(pBtree p,int pos);


/*
	*以p树位置为pos的直接后继key替换pos处值并返回key
*/
int postUpdate(pBtree p,int pos);


/*
	*将rightChild于leftChild合并，并给中间预留一个空位
*/
void UnionChild(pBtree leftChild,pBtree rightChild);


/*
	*以p树位置为pos值放在leftChild的中间位置，并删除位置为pos的值和指针
*/
void UnionRoot(pBtree p,pBtree leftChild,int pos);


/*
	*以p树位置为pos的值与pos-1和pos处的子树合并，放入pos-1子树中
*/
void Union(pBtree p,int pos);


/*
	*p树中是否存在pos位置的指针，存在返回1，否则返回0
*/
int Exist(int pos,pBtree p);


/*
	*以p树left处指向的节点的最大值放到p的right处，将p的right处原始值插入p树right处指向的节点，并伴随相应的指针操作
*/
void rightFix(int left,pBtree p,int right);


/*
	*以p树right处指向的节点的最小值放到p的right处，将p的right处原始值插入p树left处指向的节点，并伴随相应的指针操作
*/
void leftFix(int left,pBtree p,int right);


/*
	*一般的插入操作，将key插入到以p为根的树中
*/
void NormalDelete(pBtree p,int key);


/*
	*插入根的操作，将key插入到Root树中
*/
pBtree SpecialDelete(pBtree Root,int key);
