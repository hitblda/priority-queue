#pragma once
/*
	参考循环队列
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
	需要结点
*/
typedef int DataType;

typedef struct _QNode {
	int priority; //设置每个结点的优先级，值越大优先级越高
	DataType data;
	int Q_Nth;			//队列元素编号,added by HCJ

	struct _QNode* next;
}QNode;

typedef QNode* QueuePtr;

typedef struct queue
{
	QueuePtr front;    //指向队列第一个元素
	QueuePtr rear;    //指向队列最后一个元素的下一个元素
	int maxsize; //循环队列的最大存储空间
}LinkQueue;

bool CreateQueue(LinkQueue *Q);
void TraverseQueue(LinkQueue *Q);
bool isFullQueue(LinkQueue *Q);
bool isEmptyQueue(LinkQueue *Q);
bool Enqueue(LinkQueue *Q, int val, int priority);
bool Dequeue(LinkQueue *Q, int* val);

#endif
