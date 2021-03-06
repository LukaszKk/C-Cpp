// FIFO.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "KolejkaF.h"

#define MAX 5

void PrintQueue( Queue* q );

int main( int argc, char* argv[] )
{
	if( argc != 1 )
		return 1;
	Queue* pFifo = QCreate();
	for( int i = 0; i < MAX; i++ )
		QEnQueue( pFifo, i - MAX + 1 );
	PrintQueue( pFifo );
	for( int i = 0; i < MAX; i++ )
	{
		QDeQueue( pFifo );
		PrintQueue( pFifo );
	}
	PrintQueue( pFifo );
	QDel( &pFifo );


	printf( "\n\n" );
    return 0;
}

void PrintQueue( Queue* q )
{
	QItem* p = q->pHead;
	while( p )
	{
		printf( "%d ", p->nKey );
		p = p->pNext;
	}
	printf( "\n" );
}