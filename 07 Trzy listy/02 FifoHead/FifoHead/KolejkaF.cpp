#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "KolejkaF.h"

Queue* QCreate()
{
	Queue* p = (Queue*)calloc( 1, sizeof(Queue) );
	if( !p )
	{
		printf( "QCreate: Memory not allocated" );
		return 0;
	}
	QItem* v = p->pHead = p->pTail = (QItem*)calloc( 1, sizeof(QItem) );
	if( !v )
	{
		printf( "QCreate: Memory not allocated" );
		return 0;
	}
	return p;
}

int QisEmpty( Queue* q )
{
	return !( q->pHead->pNext );
}

void QEnQueue( Queue* q, int x )
{
		QItem* p = (QItem*)calloc( 1, sizeof(QItem) );
		if( !p )
		{
			printf( "QEnQueue: Memory not allocated\n" );
			return;
		}
		q->pTail->pNext = p;
		q->pTail = p;
		p->nKey = x;
}

int QDeQueue( Queue* q )
{
	if( QisEmpty( q ) )
	{
		printf( "List empty" );
		return 0;
	}
	QItem* p = q->pHead->pNext;
	q->pHead->pNext = p->pNext;
	int x = p->nKey;
	free( p );
	if( QisEmpty( q ) )										//jest tylko glowa
		q->pTail = q->pHead;
		
	return x;
}

void QClear( Queue* q )
{
	while( !QisEmpty( q ) )
		QDeQueue( q );
}

void QDel( Queue** q )
{
	QClear( *q );
	free( (*q)->pHead );
	free( *q );
	*q = NULL;
}