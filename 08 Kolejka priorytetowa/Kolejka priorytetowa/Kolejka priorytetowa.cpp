// Kolejka priorytetowa.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "QPrior.h"

#define MAX 10

int main( int argc, char* argv[] )
{
	PQueue* pQ = PQInit( MAX );
	PQEnQueue( pQ, 3, 2 );
	PQEnQueue( pQ, 4, 1 );
	PQEnQueue( pQ, 2, 3 );
	PQEnQueue( pQ, 1, 4 );
	PQEnQueue( pQ, 7, 5 );
	PQEnQueue( pQ, 4, 6 );
	PQEnQueue( pQ, 8, 7 );
	PQPrint( pQ, 0 );
	printf( "\n" );
	
	PQDeQueue( pQ );
	PQPrint( pQ, 0 );
	printf( "\n" );
	
	PQEnQueue( pQ, 8, 7 );
	PQPrint( pQ, 0 );
	printf( "\n" );
	
	IncreaseKey( pQ, 1, 8 );
	PQPrint( pQ, 0 );
	printf( "\n" );
	
	DecreaseKey( pQ, 1, 1 );
	PQPrint( pQ, 0 );
	
	PQRelease( &pQ );

	printf( "\n\n" ); 
	return 0;
}
