#pragma once
/*
	�ο�ѭ������
*/
#ifndef __PQ_H_
#define __PQ_H_

#include <stdio.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
#include "malloc.h"

#define MAXSIZE 9

/*
	��Ҫ���
*/
typedef int DataType;

typedef struct _QNode {
	int priority; //����ÿ���������ȼ���ֵԽ�����ȼ�Խ��
	DataType data;
	int Q_Nth;			//����Ԫ�ر��,added by HCJ

	struct _QNode* next;
}QNode;

typedef QNode* QueuePtr;

typedef struct queue
{
	QueuePtr front;    //ָ����е�һ��Ԫ��
	QueuePtr rear;    //ָ��������һ��Ԫ�ص���һ��Ԫ��
	int maxsize; //ѭ�����е����洢�ռ�
}LinkQueue;

bool CreateQueue(LinkQueue *Q);
void TraverseQueue(LinkQueue *Q);
bool isFullQueue(LinkQueue *Q);
bool isEmptyQueue(LinkQueue *Q);
bool Enqueue(LinkQueue *Q, int val, int priority);
bool Dequeue(LinkQueue *Q, int* val);

#endif
