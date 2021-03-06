// Macierz.cpp : Defines the entry point for the console application.
//

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "matrix.h"

#define _DEBUG_

void ReadData( FILE* fi, double** pM, double* b, int nDim);

//================================================================================================================
int main( int argc, char* argv[] )
{
	//------------------------------------------------------------------------
	//Pobiera z pliku rozmiar macierzy
	if( argc != 2 )
	{
		printf( "There is no data file. Run programme again with the name of the file with data as a second parameter\n\n" );
		return 1;
	}
	FILE* fi = NULL;					//!!!!!!!!!!!poprawione
	fi = fopen( "dane.txt", "r" );
	if( !fi )
	{
		printf( "File didn't open\n\n" );
		return 1;
	}
	int nSize;
	fscanf( fi, "%d", &nSize );
	fclose( fi );

	//------------------------------------------------------------------------
	//tworzenie macierzy
	double** pTab = NULL;
	if( !CreateMatrix( &pTab, nSize ) )
	{
		printf( "CreateMatrix: Memory not allocated\n" );
		return 1;
	}

	//------------------------------------------------------------------------
	//tworzenie tablicy wyrazow wolnych
	double* Arr = NULL;
	Arr = (double*)calloc( nSize, sizeof(double) );		//!!!!poprawione
	if( Arr == NULL )
	{
		printf( "Memory not allocated\n" );
		return 1;
	}
	
	//------------------------------------------------------------------------
	//wypelnienie macierzy liczbami z pliku
	ReadData( fi, pTab, Arr, nSize );
	#ifdef _DEBUG_
		printf( "Macierz:\n" );
		PrintMatrix( pTab, nSize );
	#endif

	//------------------------------------------------------------------------
	//wyznacznik macierzy
	double n = Det( pTab, nSize );
	#ifdef _DEBUG_
		printf( "\nWyznacznik macierzy: %.0lf\n", n );
	#endif
	//------------------------------------------------------------------------
	//macierz odwrotna
	double** pInv = NULL;
	if( !CreateMatrix( &pInv, nSize ) )
	{
		printf( "CreateMatrix: Memory not allocated\n" );
		return 1;
	}
	if( !n )		//!!!!!!!!!!!!!!porpawione
	{
		printf( "Tej macierzy nie da sie odwrocic\n" );
		return 1;
	}
	InverseMatrix( pInv, pTab, nSize, Det( pTab, nSize ) );
	#ifdef _DEBUG_
		printf( "\nMacierz odwrotna:\n" );
		PrintMatrix( pInv, nSize );
	#endif

	//------------------------------------------------------------------------
	//rozw ukladu
	double* ArrRes = NULL;
	ArrRes = (double*)calloc( nSize, sizeof(double) );
	if( !ArrRes )
	{
		printf( " Memory not allocated\n" );
		return 1;
	}
	memset( ArrRes, 0, nSize * sizeof(double) );
	LayoutEqu( pInv, Arr, ArrRes, nSize );
	printf( "\nWyniki:\t" );
	for( int i = 0; i < nSize; i++ )
		printf( "%.2lf\t", *(ArrRes + i) );

	//------------------------------------------------------------------------
	//usuniecie macierzy
	DeleteMatrix( &pTab, nSize );
	DeleteMatrix( &pInv, nSize );		//!!!! poprawione
	free( Arr );
	Arr = NULL;
	free( ArrRes );
	ArrRes = NULL;
	
	//------------------------------------------------------------------------
	printf( "\n\n" );
	return 0;
}
//================================================================================================================

void ReadData( FILE* fi, double** pM, double* b, int nDim)
{
	fi = NULL;
	fi = fopen( "dane.txt", "r" );
	if( fi == NULL )
	{
		printf( "File didn't open\n\n" );
		return;
	}
	int a;
	fscanf( fi, "%d", &a );			//pierwsza liczba, rozmiar macierzy, do pominiecia
	for( int i = 0; i < nDim; i++ )
	{
		double* v = *pM++;
		for( int j = 0; j < nDim; j++ )
			fscanf( fi, "%lf", v++ );		//macierz
		fscanf( fi, "%lf", b++ );		//wyrazy wolne
	}
	fclose( fi );
}