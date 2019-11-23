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
//		exit(-1);        //�˳�����
//	}

	Q->front = NULL;         //��ʼ������
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

	if (Q->maxsize == MAXSIZE )    //�ж�ѭ�������Ƿ���
	//if( (int)(Q->front)/sizeof(Q) == ((int)(Q->rear)/sizeof(Q)+2)%Q->maxsize )
		return true;
	else
		return false;
}

/*
	���
*/
bool Enqueue(LinkQueue *Q, int val,int priority)
{
	static int Num = 0;
	if (!Q) return 0;
	if (isFullQueue(Q)) 
	{
		cout << "��������!" << endl;
		return 0;
	}

	/*������� */
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

		Q->rear->next = qNode;  //��β������
		Q->rear = qNode;  //��βָ���²���Ľڵ�
	}

	cout << "qNode->Q_Nth ��ֵ��   "<< qNode->Q_Nth << endl;
	Num++;
	Q->maxsize++;
	return true;
}


/*
	����:�������У����ȼ��ߵģ��ȳ�
*/
bool Dequeue(LinkQueue* Q, int* val)
{
	//ʵ���������
	QNode**prev=NULL,*prev_node=NULL,*last=NULL,*tmp=NULL;
	
	//����ָ�룬��ţ�һ����ָ�룺����ָ��front��rear
	//prev:��Ŷ���ͷ���Ľ��
	//prev_node:���������ȼ����Ĵ����ȼ����
	//tmp�������ֽ�� 	
	

	if((!Q)|| (isEmptyQueue(Q)))
	{
		cout << "�����ǿյģ�" << endl;
		return false;
	}
	if (!val) return false;

	//prev ָ�����ͷ��frontָ��ĵ�ַ
	prev = &(Q->front); 
	cout << "&(Q->front)->Q_Nth ֵ�ǣ� " << &(Q->front)->Q_Nth << endl;
	cout << "(Q->front)->Q_Nth  ֵ�ǣ� " << (Q->front)->Q_Nth << endl;

	cout << "prevָ���Ԫ�� �ı��(*prev)->Q_Nth ֵ�ǣ� " << (*prev)->Q_Nth << endl;


 	printf("��һ���������ȼ���%d\n",(*prev)->priority);
	/*
	(*prev) �� frontָ�루��ַ������front�Ƕ��н��ĵ�ַ
	*/
	last = Q->front;  //ָ����Q->front��ָ����һ����㣡��
	cout << "last �ı���ǣ� " << Q->front->Q_Nth << endl;
	
#if 0
	if (*prev == last)
	{
		cout << "********************************************************** " << endl;
		cout << "*prev == last  ��Ȼ��ȣ���" << endl;
		cout << "*prev ��ֵ�ǣ� " << *prev << endl;
		cout << "last ��ֵ�ǣ� " << last << endl;
		cout << "Q->front ��ֵ�ǣ� " << Q->front << endl;
		cout << "********************************************************** " << endl;
		cout << "���ǣ�*prev �� prev �ǲ�һ���ģ���" << endl;
		cout << "*prev ��ֵ�ǣ� " << *prev <<"  Q->front��ֵ�ǣ�"<< Q->front <<endl;
		cout << "prev ��ֵ�ǣ� " << prev << "  &(Q->front)��ֵ�ǣ�" << &(Q->front) << endl;
	}	
#endif

	tmp = last->next;
	/*
	prev(&front)     Q->front ==last	 last->next	==tmp 
	   |				   |			    	|
	[=====]				[=====]	             [=====]					[=====]	
	prev_nodeΪ��������ȼ��ڵ�ָ��

	*/

	while (tmp)
	{
		//�Ƚ�last��ָ��㡢*prev�����ã������ã�ָ��ĵ�ַ��,�����ڵ�֮���ȼ�
		//����ָ��prev,(*prev)������֮���ǶԵ�ַ��ָ�򣡣�������һ�����ĵ�ַ
		if (tmp->priority > (*prev)->priority)
		{
			cout<< "ץ��һ�����ȼ�����Ľ��[priority:"<<tmp->priority<<"]"<<endl;
			prev = &(last->next);  //prev����lastָ���ָ��
			cout << " &(last->next)->Q_Nthֵ�ǣ� " << &(last->next)->Q_Nth << endl;
			cout << " (last->next)->Q_Nthֵ�ǣ� " << (last->next)->Q_Nth << endl;
			
			prev_node = last;
		}
		last = tmp;
		tmp = tmp->next;
	}

	*val = (*prev)->data;
	cout << "������������ȼ��ǣ� "<<(*prev)->priority <<endl;
	cout << "������������ȼ�����ֵ�� " << (*prev)->data << endl;
	tmp = *prev;
	*prev = (*prev)->next;
	delete tmp;
	Q->maxsize--;

	//�������������Ҫ�ֱ�Դ���
	//1.ɾ������г���Ϊ0����ɾ�������׽��
	if (Q->maxsize == 0) 
	{
		Q->rear = NULL;
	}

	//2.ɾ������β���
	if (prev_node && prev_node->next == NULL)
	{
		Q->rear = prev_node;
	}

	return true;
}

void TraverseQueue(LinkQueue* Q)
{
	/*������� */
	QNode** prev = NULL;
	
	if ((!Q) || (Q->front == NULL)) return;
	
	cout << "prev = &(Q->front)��ʼ���������е�Ԫ��.........." << endl;
	prev = &(Q->front);
	for (int i = 0; i < Q->maxsize; i++)
	{
		cout << "���е�" << i << "��Ԫ�ص�ֵ��:" << (*prev)->data << endl;
		cout << "     Q->front->Q_Nth ��:" << Q->front->Q_Nth << endl;
		cout << "     (*prev)->Q_Nth  ��:" <<  (*prev)->Q_Nth << endl;

		prev = &((*prev)->next);
	}

	//cout << "*prev = (Q->front)��ʼ���������е�Ԫ��.........." << endl;
	//*prev = (Q->front);
	//for (int i = 0; i < Q->maxsize; i++)
	//{
	//	cout << "���е�" << i << "��Ԫ�ص�ֵ��:" << (*prev)->data << endl;
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
		cout << "���д����ɹ���" << endl;
		cout << "ϣ���Ķ��г��ȣ�" << MAXSIZE << endl;
		cout << "(tQ->rear - tQ->front) / sizeof(tQ) is:" << (tQ->rear - tQ->front) / sizeof(tQ) << endl;
	}

	cout << "********************************************" << endl;
	if (isEmptyQueue(tQ))
	{
		cout << "�����ǿյģ�" << endl;
	}

//	if (Enqueue(tQ, 19, 3))
//	{
//		cout << "*********************" << endl;
//		cout << "��ֵ��:" << tQ->rear->data << endl;
//		cout << "�����ȼ���:" << tQ->rear->priority << endl;
//		cout<< "����Ԫ����ӳɹ���" << endl;
//		cout << "(tQ->rear - tQ->front) / sizeof(tQ) is:" << (tQ->rear - tQ->front) / sizeof(tQ) << endl;
//	}
	//else
	//{
	//	cout << "����Ԫ�����failed��" << endl;
	//}

	for (int count = 0; count < MAXSIZE; count++)
	{
		if (Enqueue(tQ, count + 100, count *37%12))
		{
			cout << "��" << count << "����ӣ��ɹ���" << endl;
			cout << "��ֵ��:" << tQ->rear->data<<"  ";
			cout << "�����ȼ���:" << tQ->rear->priority << endl;
		}
		else
		{
			cout << "��" << count << "����Ӳ������ɹ���" << endl;
		}
		//cout << "(tQ->rear - tQ->front) / sizeof(tQ) is:" << ((tQ->rear - tQ->front) / sizeof(tQ) -4) << endl;
		/*
			�±����ַ������������е�Ԫ�ظ�����ͽ���޹�����
		
		if (tQ->front == NULL)
		{
			cout << "��������û��Ԫ�أ�" << endl;
		}
		else if((tQ->rear - tQ->front) / sizeof(tQ) == 0)
		{
			cout << "����������1��Ԫ�أ�" << endl;
		}
		else
		{
			cout << "����������"<< ((tQ->rear - tQ->front) / sizeof(tQ) - 2)<<"��Ԫ�أ�" << endl;
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
//			cout << "���������" << count << "��Ԫ�ص����ȼ��ǣ�" << tQ->front->priority << endl;
//			cout << "���������"<<count<<"��Ԫ�ص�ֵ�ǣ�"<<aValue << endl;
//		}
//		
//	}
	cout << "********************************************" << endl;
	TraverseQueue(tQ);

	/**/
	system("pause");
	return 0;
}