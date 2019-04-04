#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "KolejkaF.h"

Queue* QCreate( int nSize )
{
	Queue* p = (Queue*)calloc( 1, sizeof(Queue) );
	if( !p )
	{
		printf( "QCreate: Memory not allocated\n" );
		return 0;
	}
	p->Arr = (int*)calloc( nSize, sizeof(int) );
	if( !p->Arr )
	{
		printf( "QCreate: Memory not allocated\n" );
		return 0;
	}
	p->nMaxEl = nSize;

	return p;
}

int QisEmpty( Queue* q )
{
	return !( q->mCurrSize );
}

void QEnQueue( Queue* q, int x )
{
	if( q->mCurrSize == q->nMaxEl )
	{
		printf( "List full\n" );
		return;
	}
	q->Arr[q->mTail] = x;
	q->mTail = (q->mTail+1)%q->nMaxEl;
	q->mCurrSize++;
}

int QDeQueue( Queue* q )
{
	if( QisEmpty( q ) )
	{
		printf( "Queue is empty\n" );
		return 0;
	}
	int x = q->Arr[q->mFront];
	q->mFront = (q->mFront + 1)%q->nMaxEl;
	q->mCurrSize--;
	return x;
}

void QClear( Queue* q )
{
	while( !QisEmpty( q ) )
		QDeQueue( q );
	q->mTail = 0;
}

void QDel( Queue** q )
{
	QClear( *q );
	free( (*q)->Arr );
	free( *q );
	*q = NULL;
}