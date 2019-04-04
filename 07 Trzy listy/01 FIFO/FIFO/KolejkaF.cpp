#include <stdio.h>
#include <stdlib.h>
#include "KolejkaF.h"

Queue* QCreate()
{
	Queue* p = (Queue*)calloc( 1, sizeof(Queue) );
	if( !p )
		printf( "QCreate: Memory not allocated" );
	return p;
}

int QisEmpty( Queue* q )
{
	return !( q->pHead );
}

void QEnQueue( Queue* q, int x )
{
	QItem* p = (QItem*)calloc( 1, sizeof(QItem) );
	if( !p )
	{
		printf( "QEnQueue: Memory not allocated" );
		return;
	}
	if( QisEmpty( q ) )
		q->pHead = p;
	else
		q->pTail->pNext = p;
	q->pTail = p;
	p->nKey = x;
}

int QDeQueue( Queue* q )
{
	if( QisEmpty( q ) )
	{
		printf( "list empty" );
		return 0;
	}
	QItem* p = q->pHead;
	q->pHead = p->pNext;
	if( !(q->pHead) )
		q->pTail = NULL;
	int x = p->nKey;
	free( p );
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
	free( *q );
	*q = NULL;
}
