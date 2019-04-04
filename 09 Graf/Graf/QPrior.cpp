#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "QPrior.h"

void UpdateDown( PQueue*, int l, int p );
void UpdateUp( PQueue*, int l, int p );


PQueue* PQInit( int nSize )
{
	PQueue* p = (PQueue*)calloc( 1, sizeof(PQueue) );
	if( !p )
	{
		printf( "Memory not allocated" );
		return 0;
	}
	p->Arr = (PQItem*)calloc( nSize, sizeof(PQItem) );
	if( !p->Arr )
	{
		printf( "Memory not allocated" );
		return 0;
	}
	p->pQSize = nSize;

	return p;
}

int pQisEmpty( PQueue* q )
{
	return !(q->pQCurrSize);
}

void PQEnQueue( PQueue* q, int nKey, double nPrior )
{
	if( q->pQCurrSize == q->pQSize )
	{
		printf( "Queue is full" );
		return;
	}
	q->Arr[q->pQCurrSize].nKey = nKey;
	q->Arr[q->pQCurrSize].nPrior = nPrior;
	UpdateUp( q, 0, q->pQCurrSize );
	q->pQCurrSize++;
}

int PQDeQueue( PQueue* q )
{
	if( pQisEmpty( q ) )
	{
		printf( "Queue is empty" );
		return 0;
	}
	q->pQCurrSize--;
	int x = q->Arr[0].nKey;
	q->Arr[0] = q->Arr[q->pQCurrSize];
	UpdateDown( q, 0, q->pQCurrSize - 1 );

	return x;
}

void PQRelease( PQueue** q )
{
	while( !pQisEmpty( *q ) )
		PQDeQueue( *q );
	free( (*q)->Arr );
	free( *q );
	*q = NULL;
}

void PQPrint( PQueue* q, int i )
{
	if( i >= q->pQCurrSize ) return;
	PQPrint( q, 2 * i + 1 );
	printf( "%d ", q->Arr[i].nKey );
	printf( "%.0lf\t", q->Arr[i].nPrior );
	PQPrint( q, 2 * i + 2 );
}

void IncreaseKey( PQueue* q, int nKey, int nPrior )
{
	if( nKey >= q->pQCurrSize )
	{
		printf( "There is no index like %d\n", nKey );
		return;
	}
	if( q->Arr[nKey].nPrior >= nPrior )
	{
		printf( "Prior can't be increased\n" );
		return;
	}
	q->Arr[nKey].nPrior = nPrior;
	UpdateUp( q, 0, nKey );
}

void DecreaseKey( PQueue* q, int nKey, int nPrior )
{
	if( nKey >= q->pQCurrSize )
	{
		printf( "There is no index like %d\n", nKey );
		return;
	}
	if( q->Arr[nKey].nPrior <= nPrior )
	{
		printf( "prior can't be decreased\n" );
		return;
	}
	q->Arr[nKey].nPrior = nPrior;
	UpdateDown( q, nKey, q->pQCurrSize - 1 );
}

void UpdateDown( PQueue* q, int l, int p )
{
	if( l == p ) return;

	int i = l;
	int j = 2 * i + 1;
	PQItem tmp = q->Arr[i];
	while( j < p )
	{
		if( q->Arr[j].nPrior > q->Arr[j + 1].nPrior )
			j++;
		if( tmp.nPrior <= q->Arr[j].nPrior )
			break;
		q->Arr[i] = q->Arr[j];
		i = j;
		j = 2 * i + 1;
	}
	q->Arr[i] = tmp;
}

void UpdateUp( PQueue* q, int l, int p )
{
	if( l == p ) return;

	int i = p;
	int j = (i - 1) / 2;
	PQItem tmp = q->Arr[i];
	while( i > l )
	{
		if( (j > l) && (q->Arr[j].nPrior < q->Arr[j - 1].nPrior) )
			j--;
		if( tmp.nPrior >= q->Arr[j].nPrior )
			break;
		q->Arr[i] = q->Arr[j];
		i = j;
		j = (i - 1) / 2;
	}
	q->Arr[i] = tmp;
}