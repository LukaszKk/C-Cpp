// ArrFIFO.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "KolejkaF.h"

#define MAX 5

void PrintArr( Queue* q );

int main( int argc, char* argv[] )
{
	if( argc != 1 )
		return 1;
	Queue* pFifo = QCreate( MAX );
	for( int i = 0; i <= MAX; i++ )
		QEnQueue( pFifo, i + 1 );
	PrintArr( pFifo );
	/*for( int i = 0; i <= MAX; i++ )
		QDeQueue( pFifo );
	PrintArr( pFifo );
	for( int i = 0; i < 4; i++ )
		QEnQueue( pFifo, i + 1 );
	PrintArr( pFifo );*/
	QDel( &pFifo );

	printf( "\n\n" );
    return 0;
}

void PrintArr( Queue* q )
{
	int i = q->mFront;
	for( int j = 0; j < q->mCurrSize; j++, i++ )
	{
		i %= q->nMaxEl;
		printf( "%d ", q->Arr[i] );
	}
	printf( "\n" );
}