#include "pQ.h"

using namespace std;
/***********************************************
Function: Create a empty stack;
************************************************/
bool CreateQueue(LinkQueue *Q)
{
	if (!Q) return false;
//	Q->pBase = (int*)malloc(sizeof(int) * maxsize);
//	if (NULL == Q->pBase)
//	{
//		printf("Memory allocation failure");
//		exit(-1);        //退出程序
//	}

	Q->front = NULL;         //初始化参数
	Q->rear = NULL;
	Q->maxsize = 0;

	return true;
}

bool isEmptyQueue(LinkQueue* Q)
{
	if (!Q) return false;

	if(Q->front == NULL)
		return true;
	else
		return false;
}

bool isFullQueue(LinkQueue* Q)
{
	if (!Q) return false;

	if (Q->maxsize == MAXSIZE )    //判断循环链表是否满
	//if( (int)(Q->front)/sizeof(Q) == ((int)(Q->rear)/sizeof(Q)+2)%Q->maxsize )
		return true;
	else
		return false;
}

/*
	入队
*/
bool Enqueue(LinkQueue *Q, int val,int priority)
{
	static int Num = 0;
	if (!Q) return 0;
	if (isFullQueue(Q)) 
	{
		cout << "队列已满!" << endl;
		return 0;
	}

	/*创建结点 */
	QNode* qNode = new QNode;
	qNode->data = val;
	qNode->priority = priority;
	qNode->next = NULL;
	
	qNode->Q_Nth = Num;

	if (isEmptyQueue(Q))
	{
		Q->front = Q->rear = qNode;
	}
	else
	{
		cout << " Enqueue() function running......" << endl;

		Q->rear->next = qNode;  //队尾插入结点
		Q->rear = qNode;  //队尾指向新插入的节点
	}

	cout << "qNode->Q_Nth 的值是   "<< qNode->Q_Nth << endl;
	Num++;
	Q->maxsize++;
	return true;
}


/*
	出队:遍历队列，优先级高的，先出
*/
bool Dequeue(LinkQueue* Q, int* val)
{
	//实例化，结点
	QNode**prev=NULL,*prev_node=NULL,*last=NULL,*tmp=NULL;
	
	//二级指针，存放（一级）指针：链表指针front、rear
	//prev:存放队列头部的结点
	//prev_node:存放最高优先级结点的次优先级结点
	//tmp：主动轮结点 	
	

	if((!Q)|| (isEmptyQueue(Q)))
	{
		cout << "队列是空的！" << endl;
		return false;
	}
	if (!val) return false;

	//prev 指向对列头部front指针的地址
	prev = &(Q->front); 
	cout << "&(Q->front)->Q_Nth 值是： " << &(Q->front)->Q_Nth << endl;
	cout << "(Q->front)->Q_Nth  值是： " << (Q->front)->Q_Nth << endl;

	cout << "prev指向的元素 的编号(*prev)->Q_Nth 值是： " << (*prev)->Q_Nth << endl;


 	printf("第一个结点的优先级：%d\n",(*prev)->priority);
	/*
	(*prev) 即 front指针（地址），而front是队列结点的地址
	*/
	last = Q->front;  //指向了Q->front的指向（下一个结点！）
	cout << "last 的编号是： " << Q->front->Q_Nth << endl;
	
#if 0
	if (*prev == last)
	{
		cout << "********************************************************** " << endl;
		cout << "*prev == last  居然相等！！" << endl;
		cout << "*prev 的值是： " << *prev << endl;
		cout << "last 的值是： " << last << endl;
		cout << "Q->front 的值是： " << Q->front << endl;
		cout << "********************************************************** " << endl;
		cout << "但是，*prev 和 prev 是不一样的！！" << endl;
		cout << "*prev 的值是： " << *prev <<"  Q->front的值是："<< Q->front <<endl;
		cout << "prev 的值是： " << prev << "  &(Q->front)的值是：" << &(Q->front) << endl;
	}	
#endif

	tmp = last->next;
	/*
	prev(&front)     Q->front ==last	 last->next	==tmp 
	   |				   |			    	|
	[=====]				[=====]	             [=====]					[=====]	
	prev_node为次最高优先级节点指针

	*/

	while (tmp)
	{
		//比较last所指结点、*prev解引用（解引用：指向的地址）,两个节点之优先级
		//二级指针prev,(*prev)解引用之后，是对地址的指向！！即，下一个结点的地址
		if (tmp->priority > (*prev)->priority)
		{
			cout<< "抓到一个优先级更大的结点[priority:"<<tmp->priority<<"]"<<endl;
			prev = &(last->next);  //prev保存last指针的指向
			cout << " &(last->next)->Q_Nth值是： " << &(last->next)->Q_Nth << endl;
			cout << " (last->next)->Q_Nth值是： " << (last->next)->Q_Nth << endl;
			
			prev_node = last;
		}
		last = tmp;
		tmp = tmp->next;
	}

	*val = (*prev)->data;
	cout << "本队列最高优先级是： "<<(*prev)->priority <<endl;
	cout << "本队列最高优先级结点的值： " << (*prev)->data << endl;
	tmp = *prev;
	*prev = (*prev)->next;
	delete tmp;
	Q->maxsize--;

	//还有两种情况需要分别对待：
	//1.删除完队列长度为0，即删除的是首结点
	if (Q->maxsize == 0) 
	{
		Q->rear = NULL;
	}

	//2.删除的是尾结点
	if (prev_node && prev_node->next == NULL)
	{
		Q->rear = prev_node;
	}

	return true;
}

void TraverseQueue(LinkQueue* Q)
{
	/*创建结点 */
	QNode** prev = NULL;
	
	if ((!Q) || (Q->front == NULL)) return;
	
	cout << "prev = &(Q->front)开始遍历队列中的元素.........." << endl;
	prev = &(Q->front);
	for (int i = 0; i < Q->maxsize; i++)
	{
		cout << "队列第" << i << "个元素的值是:" << (*prev)->data << endl;
		cout << "     Q->front->Q_Nth 是:" << Q->front->Q_Nth << endl;
		cout << "     (*prev)->Q_Nth  是:" <<  (*prev)->Q_Nth << endl;

		prev = &((*prev)->next);
	}

	//cout << "*prev = (Q->front)开始遍历队列中的元素.........." << endl;
	//*prev = (Q->front);
	//for (int i = 0; i < Q->maxsize; i++)
	//{
	//	cout << "队列第" << i << "个元素的值是:" << (*prev)->data << endl;
	//	prev = &((*prev)->next);
	//}

	system("pause");
}



int main(void)
{
	int aValue = 0;
	LinkQueue* tQ = new LinkQueue;
	if (CreateQueue(tQ))
	{
		cout << "队列创建成功！" << endl;
		cout << "希望的队列长度：" << MAXSIZE << endl;
		cout << "(tQ->rear - tQ->front) / sizeof(tQ) is:" << (tQ->rear - tQ->front) / sizeof(tQ) << endl;
	}

	cout << "********************************************" << endl;
	if (isEmptyQueue(tQ))
	{
		cout << "队列是空的！" << endl;
	}

//	if (Enqueue(tQ, 19, 3))
//	{
//		cout << "*********************" << endl;
//		cout << "其值是:" << tQ->rear->data << endl;
//		cout << "其优先级是:" << tQ->rear->priority << endl;
//		cout<< "队列元素添加成功！" << endl;
//		cout << "(tQ->rear - tQ->front) / sizeof(tQ) is:" << (tQ->rear - tQ->front) / sizeof(tQ) << endl;
//	}
	//else
	//{
	//	cout << "队列元素添加failed！" << endl;
	//}

	for (int count = 0; count < MAXSIZE; count++)
	{
		if (Enqueue(tQ, count + 100, count *37%12))
		{
			cout << "第" << count << "个入队，成功！" << endl;
			cout << "其值是:" << tQ->rear->data<<"  ";
			cout << "其优先级是:" << tQ->rear->priority << endl;
		}
		else
		{
			cout << "第" << count << "个入队不。。成功！" << endl;
		}
		//cout << "(tQ->rear - tQ->front) / sizeof(tQ) is:" << ((tQ->rear - tQ->front) / sizeof(tQ) -4) << endl;
		/*
			下边这种方法计算加入队列的元素个数，徒劳无功！！
		
		if (tQ->front == NULL)
		{
			cout << "队列里面没有元素！" << endl;
		}
		else if((tQ->rear - tQ->front) / sizeof(tQ) == 0)
		{
			cout << "队列里面有1个元素！" << endl;
		}
		else
		{
			cout << "队列里面有"<< ((tQ->rear - tQ->front) / sizeof(tQ) - 2)<<"个元素！" << endl;
		}
		*/
	}
	cout << "********************************************" << endl;
	TraverseQueue(tQ);
	cout << "********************************************" << endl;
	Dequeue(tQ, &aValue);
	cout << "********************************************" << endl;
	Dequeue(tQ, &aValue);
//	for (int count = 1; count < MAXSIZE; count++)
//	{
//		if (Dequeue(tQ, &aValue))
//		{
//			cout << "队列里面第" << count << "个元素的优先级是：" << tQ->front->priority << endl;
//			cout << "队列里面第"<<count<<"个元素的值是："<<aValue << endl;
//		}
//		
//	}
	cout << "********************************************" << endl;
	TraverseQueue(tQ);

	/**/
	system("pause");
	return 0;
}