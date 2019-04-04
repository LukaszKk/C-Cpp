// Sortowania.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "Nag.h"


#define NUMS 100	//gorny zakres generowanych liczb
//#define _DEBUG_

int* MakeArr( int nSize );
void FillArr( int* t, int nSize );
void PrintArr( int* t, int nSize );
void CopyArr( int* tOut, int* tIn, int nSize );
void DelArr( int** t );

typedef void ( *pf )( int*, int );
void Test( pf Arr[], const char* Names[], int NumSort, int* ArrOr, int* ArrNew, int nSize );				//wskaznik na funkcje, nazwa funkcji, ilosc sortowan, oryginalna tablica, skopiowana tablica, rozmiar tablicy


//===========================================================================================
int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		printf( "There is no second parameter\n" );
		return 1;
	}
	int nSize = atoi( argv[1] );
	const char* Names[] = { "InsertionSort", "SelectionSort", "HalfSort", "ShakeSort", "SekMergeSort", "HeapSort" };				//tablica nazw
	pf Arr[] = { InsertionSort, SelectionSort, HalfSort, ShakeSort, SekMergeSort, HeapSort };								//tablica funkcji
	
	int* ArrOr = NULL;
	ArrOr = MakeArr( nSize );
	if( !ArrOr )
	{
		printf( "Memory not allocated" );
		return 1;
	}
	FillArr( ArrOr, nSize );
	int* ArrNew = NULL;

	Test( Arr, Names, sizeof( Arr ) / sizeof( pf ), ArrOr, ArrNew, nSize  );
	
	DelArr( &ArrOr );

	printf( "\n\n" );
    return 0;
}
//===========================================================================================

void Test( pf Arr[], const char* Names[], int NumSort, int* ArrOr, int* ArrNew, int nSize )
{
	#ifdef _DEBUG_
	printf( "tablica: " );
	if( nSize > 20 )
		PrintArr( ArrOr, 20 );
	else
		PrintArr( ArrOr, nSize );
	#endif
	
	ArrNew = MakeArr( nSize );
	if( !ArrNew )
	{
		printf( "Test: Memory not allocated" );
		return;
	}
	clock_t start;
	clock_t end;

	for( int i = 0; i < NumSort; i++ )
	{
		CopyArr( ArrNew, ArrOr, nSize );
		printf( "%s [s]\t", Names[i] ); 
		start = clock();
		Arr[i]( ArrNew, nSize );
		end = clock();
		printf( "%lf [s]\n", (end - start) / (double)CLOCKS_PER_SEC );
		
		if( nSize > 20 )
			PrintArr( ArrNew, 20 );
		else
			PrintArr( ArrNew, 20 );
	}

	//rekurencyjne
	CopyArr( ArrNew, ArrOr, nSize );
	start = clock();
	QuickSort( ArrNew, 0, nSize );
	end = clock();
	printf( "QuickSort [s]\t%lf [s]\n", (end - start) / (double)CLOCKS_PER_SEC );
	if( nSize > 20 )
		PrintArr( ArrNew, 20 );
	else
		PrintArr( ArrNew, nSize );

	CopyArr( ArrNew, ArrOr, nSize );
	int* tmp = NULL;
	tmp = MakeArr( nSize );
	if( !tmp )
	{
		printf( "Test: Memory not allocated" );
		return;
	}
	start = clock();
	MergeSort( ArrNew, tmp, 0, nSize - 1 );
	end = clock();
	printf( "MergeSort [s]\t%lf [s]\n", (end - start) / (double)CLOCKS_PER_SEC );
	if( nSize > 20 )
		PrintArr( ArrNew, 20 );
	else
		PrintArr( ArrNew, 20 );

	DelArr( &ArrNew );
	DelArr( &tmp);
}

//----------------------------------------------------------------------------------

int* MakeArr( int nSize )
{
	return (int*)calloc( nSize, sizeof(int) );
}

void FillArr( int* t, int nSize )
{
	srand( (unsigned)time(NULL) );
	int* v = t;
	for( int i = 0; i < nSize; i++ )
		*v++ = rand() % NUMS;
}

void PrintArr( int* t, int nSize )
{
	int* v = t;
	for( int i = 0; i < nSize; i++ )
		printf( "%d ", *v++ );
	printf( "\n" );
}

void CopyArr( int* tOut, int* tIn, int nSize )
{
	memcpy( tOut, tIn, nSize * sizeof( int ) );
}

void DelArr( int** t )
{
	free( *t );
	*t = NULL;
}