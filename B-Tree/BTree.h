/*
	*����newRoot��ʹ֮����һ��Ԫ�أ�leftChild���ֵ������������ָ��ֱ�����leftChild��rightChild�������¸���С
*/
void FixNewRoot(pBtree leftChild,pBtree newRoot,pBtree rightChild);


/*
	*��leftChild��һ���Ԫ�طŵ�rightChild�����������������С
*/
void FixChild(pBtree leftChild,pBtree rightChild);


/*
	*��rightChild���뵽Root��posλ���£�����posλ�õ�Keyֵ��leftChild����
*/
void FixRoot(pBtree leftChild,pBtree Root,pBtree rightChild,int pos);


/*
	*�Ѹ��ڵ����
*/
pBtree SplitRoot(pBtree leftChild);


/*
	*����һ��BTree
*/
pBtree CreateBtree();


/*
	*������target�е�l��u֮�����key��target[����ֵ]<=key
*/
int Find(int target[],int l,int u,int key);


/*
	*p�Ƿ�ΪҶ�ӽڵ㣬�Ƿ���1���񷵻�0
*/
int IsLeaf(pBtree p);


/*
	*��keyֵ���뵽p�ڵ��posλ��
*/
void InsertKeyToLeaf(pBtree p,int key,int pos);


/*
	*����ʱ�жϽڵ��Ƿ���Ҫ�Ƚ��з���
*/
int NeedSplit(pBtree p);


/*
	*����p��pos֮ǰһλ������������������������ֵ����p��pos���������ɵĺ��ӽڵ����pos��
*/
void SplitNode(pBtree p,int pos);


/*
	*һ��Ĳ���
*/
void NormalInsert(pBtree p,int key);


/*
	*�Ը��Ĳ��룬�����⴦��
*/
pBtree SpecialInsert(pBtree root,int key);


/*
	*�鿴���ڵ��Ƿ񲻺��κ�Ԫ���Ҳ���Ҷ�ӽڵ㣬��������1�����򷵻�0
*/
int IsWaste(pBtree Root);


/*
	*�鿴p��pos����ֵ�Ƿ����key���Ƿ���1�����򷵻�0
*/
int Equal(pBtree p,int pos,int key);


/*
	*ɾ��Ҷ�ӽڵ�pλ��Ϊpos����ֵ
*/
void Delete(pBtree p,int pos);


/*
	*�鿴p������ֵ�Ƿ�С��MAX���Ա��ڲ�������������1�����򷵻�0
*/
int NodeAvailable(pBtree p);


/*
	*��p��λ��Ϊpos��ֱ��ǰ��key�滻pos����ֵ������key
*/
int preUpdate(pBtree p,int pos);


/*
	*��p��λ��Ϊpos��ֱ�Ӻ��key�滻pos��ֵ������key
*/
int postUpdate(pBtree p,int pos);


/*
	*��rightChild��leftChild�ϲ��������м�Ԥ��һ����λ
*/
void UnionChild(pBtree leftChild,pBtree rightChild);


/*
	*��p��λ��Ϊposֵ����leftChild���м�λ�ã���ɾ��λ��Ϊpos��ֵ��ָ��
*/
void UnionRoot(pBtree p,pBtree leftChild,int pos);


/*
	*��p��λ��Ϊpos��ֵ��pos-1��pos���������ϲ�������pos-1������
*/
void Union(pBtree p,int pos);


/*
	*p�����Ƿ����posλ�õ�ָ�룬���ڷ���1�����򷵻�0
*/
int Exist(int pos,pBtree p);


/*
	*��p��left��ָ��Ľڵ�����ֵ�ŵ�p��right������p��right��ԭʼֵ����p��right��ָ��Ľڵ㣬��������Ӧ��ָ�����
*/
void rightFix(int left,pBtree p,int right);


/*
	*��p��right��ָ��Ľڵ����Сֵ�ŵ�p��right������p��right��ԭʼֵ����p��left��ָ��Ľڵ㣬��������Ӧ��ָ�����
*/
void leftFix(int left,pBtree p,int right);


/*
	*һ��Ĳ����������key���뵽��pΪ��������
*/
void NormalDelete(pBtree p,int key);


/*
	*������Ĳ�������key���뵽Root����
*/
pBtree SpecialDelete(pBtree Root,int key);
