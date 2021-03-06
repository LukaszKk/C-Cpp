// Graf.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Functions.h"

void MakeArr( int*** t, int nSize );
void DeleteArr( int*** t, int nSize );

int main( int argc, char* argv[] )
{
	if( argc != 3 )
	{
		printf( "Usage: %s <Input file> <Output file>\n", argv[0] );		 //!!!!!!! i indeksowanie wyrzucone, na dole i w InitList
		return 1;
	}
	
	FILE* fi = NULL;
	if( !(fi = fopen( argv[1], "r" )) )
	{
		printf( "File didn't open\n" );
		return 1;
	}
	int nSize;
	fscanf( fi, "%d", &nSize );
	Vertex* List = InitList( nSize );
	Read( fi, List, nSize );
	fclose( fi );

	int** t = NULL;
	MakeArr( &t, nSize );
	DFS( List, 0, t );
	DeleteArr( &t, nSize );
	
	CountDijkstra( List, nSize );

	PrintToTxt( List, nSize, argv[2] );

	Release( &List, nSize );
	
	printf( "\n\n" );
    return 0;
}

void MakeArr( int*** t, int nSize )
{
	int** p = *t = (int**)calloc( nSize, sizeof(int*) );
	if( !(*t) )
	{
		printf( "Memory not allocated\n" );
		return;
	}

	for( int i = 0; i < nSize; i++, p++ )
	{
		*p = (int*)calloc( nSize, sizeof(int) );
		if( !(*p) )
		{
			printf( "Memory not allocated\n" );
			return;
		}
	}
}

void DeleteArr( int*** t, int nSize )
{
	int** p = *t;
	for( int i = 0; i < nSize; i++, p++ )
		free( *p );
	free( *t );
	*t = NULL;
}