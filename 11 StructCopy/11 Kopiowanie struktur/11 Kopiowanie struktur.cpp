// 11 Kopiowanie struktur.cpp : Defines the entry point for the console application.
//
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 20
#define MAXSTR 5

typedef struct
{
	int nKey;
	char* pStr;							//wsk do dynamicznej pamieci
} T;

void printTab( T* pTab, int nSize );
void CopyTab( T* pTab1, T* pTab2, int nSize );

int main()
{
	T* t = (T*)calloc( MAX, sizeof( T ) );			//t tablica struktur T
	
	srand( (unsigned)time(NULL) );
	for( int i = 0, c = 'A'; i < MAX; i++, c++ )
	{
		t[i].nKey = rand() % MAX;
		t[i].pStr = (char*)calloc( MAXSTR, sizeof(char) );
		for( int j = 0; j < MAXSTR - 1; j++ )
			t[i].pStr[j] = c;
	}
	printTab( t, MAX );
	printf( "\n" );
	T* t1 = (T*)calloc( MAX, sizeof(T) );
	CopyTab( t, t1, MAX );

	for( int i = 0; i < MAX; i++ )
		free( t[i].pStr );
	free( t );

	printf( "Copy:\n" );
	printTab( t1, MAX );

	free( t1 );
	

	printf( "\n\n" );
    return 0;
}

void printTab( T* pTab, int nSize )
{
	for( int i = 0; i < nSize; i++ )
	{
		printf( "%d -- %s ", pTab[i].nKey, pTab[i].pStr );
		if( (i+1) % 4 == 0 ) printf( "\n" );
	}
	printf( "\n" );
}

void CopyTab( T* pTab1, T* pTab2, int nSize )
{
	for( int i = 0; i < nSize; i++ )
		pTab2[i] = pTab1[i];			//kopiowanie struktur		!!!! UWAGA NA POLA DYNAMICZNE
}