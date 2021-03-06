// Statki.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include "StatH.h"


int CreateMatrix( int*** pTab, int nSize, int mSize );
void DeleteMatrix( int*** pTab, int nSize );
void PrintMatrix( int** pTab, int nSize, int mSize );
int CreateDepth( char* sFile, int nSize, int mSize, int x_dest, int y_dest );

int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		printf( "Usage:%s <Input file> ", argv[0] );
	}
	int** pTab = NULL;
	int** pRoot = NULL;
	if( !CreateMatrix( &pTab, N, M) )
		return 1;
	if( !CreateMatrix( &pRoot, N, M) )
		return 1;
	//if( !CreateDepth( argv[1], N, M, N - 1, M - 1 ) )
		//return 1;
	setTab( argv[1], pTab, N, M );
	if( !root( pTab, N, M, DEPTH_MIN, 0, 0, pRoot, N - 1, M - 1 ) )
	{
		printf( "** Nie ma mozliwosci doplynac do portu!!\n\n" );
		return 1;
	}
	PrintMatrix( pRoot, N, M );

	DeleteMatrix( &pTab, N );
	DeleteMatrix( &pRoot, N );
	printf( "\n\n" );
    return 0;
}

int CreateMatrix( int*** pTab, int nSize, int mSize )
{
	*pTab = (int**)calloc( nSize, sizeof(int*) );
	if( !(*pTab) )
	{
		printf( "Memory not allocated" );
		return 0;
	}
	int** v = *pTab;
	for( int i = 0; i < mSize; i++, v++ )
	{
		*v = (int*)calloc( mSize, sizeof(int) );
		if( !(*v) )
		{
			printf( "Memory not allocated" );
			return 0;
		}
	}
	return 1;
}

void DeleteMatrix( int*** pTab, int nSize )
{
	int** v = *pTab;
	for( int i = 0; i < nSize; i++ )
		free( *v++ );
	free( *pTab );
	*pTab = NULL;
}

void PrintMatrix( int** pTab, int nSize, int mSize )
{
	for( int i = 0; i < nSize; i++, pTab++ )
	{
		int* v = *pTab;
		for( int j = 0; j < mSize; j++, v++ )
			printf( "%d ", *v );
		printf( "\n" );
	}
}


int CreateDepth( char* sFile, int nSize, int mSize, int x_dest, int y_dest )
{
	FILE* fin = fopen( sFile, "w" );
	if( !fin )
	{
		printf( "File didn't open\n" );
		return 0;
	}
	srand( (unsigned)time(NULL) );
	for( int i = 0; i < nSize; i++ )
	{
		for( int j = 0; j < mSize; j++ )
		{
			if( ((i == x_dest) && (j == y_dest)) || ((i == 0) && (j == 0)) )
				fprintf( fin, "%2d ", DEPTH_MIN + 2 );
			else
				fprintf( fin, "%2d ", rand() % 29 + 5 );
		}
		fprintf( fin, "\n" );
	}
	fclose( fin );
	return 1;
}