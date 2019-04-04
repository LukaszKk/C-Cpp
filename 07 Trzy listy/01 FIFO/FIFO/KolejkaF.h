#ifndef _QUEUEFIFO_
#define _QUEUEFIFO_

typedef struct tagQItem
{
	int nKey;
	tagQItem* pNext;
} QItem;
typedef struct
{
	QItem* pHead;
	QItem* pTail;
} Queue;

Queue* QCreate();
int QisEmpty( Queue* q );
void QEnQueue( Queue* q, int x );
int QDeQueue( Queue* q );
void QClear( Queue* q );
void QDel( Queue** q );

#endif