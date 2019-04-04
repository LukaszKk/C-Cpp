#include <stdio.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include "matrix.h"

//#define _DEBUG_

void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim );
void ComplMatrix(double** pTabD, double** pTab, int nDim );
void TransMatrix( double** pTab, int nDim );

//---------------------------------------------------------------------------------------------

int CreateMatrix( double*** pTab, int nSize )			//tworzy macierz
{
	*pTab = (double**)calloc( nSize, sizeof(double*) );
	if( !*pTab )
		return 0;
	double** v = *pTab;
	for( int i = 0; i < nSize; i++, v++ )
	{
		*v = (double*)calloc( nSize, sizeof(double) );
		if( !*v )
			return 0;
	}
	return 1;
}

//---------------------------------------------------------------------------------------------

void PrintMatrix( double** pTab, int nSize )		//wypisuje macierz
{
	for( int i = 0; i < nSize; i++ )
	{
		double* v = *pTab++;
		for( int j = 0; j < nSize; j++ )
			printf( "%.2lf\t", *v++ );
		printf( "\n" );
	}
}

//---------------------------------------------------------------------------------------------

void DeleteMatrix( double*** pTab, int nSize )		//usuwa macierz
{
	double** v = *pTab;
	for( int i = 0; i < nSize; i++ )
		free( *v++ );
	free( *pTab );
	*pTab = NULL;
}

//---------------------------------------------------------------------------------------------

void InverseMatrix( double** pInv, double** pTab, int nSize, double det )		//odwraca macierz: A^-1
{
	ComplMatrix( pInv, pTab, nSize );
	TransMatrix( pInv, nSize );
	for( int i = 0; i < nSize; i++ )
	{
		double* v = *pInv++;
		for( int j = 0; j < nSize; j++ )
			*v++ /= det;														//*(*(pInv + i) + j) /= det;
	}
}

//---------------------------------------------------------------------------------------------

double Det( double** pTab, int nSize )		//liczy wyznacznik
{
	if( nSize == 1 )
		return **pTab;
	if( nSize == 2 )
		return ( **pTab * *(*(pTab + 1) + 1) - *(*pTab + 1) * **(pTab + 1) );
	double** pTabO;
	if( !CreateMatrix( &pTabO, ( nSize - 1) ) )
	{
		printf( "Det: CreateMatrix: Memory not allocated\n" );
		return 0;
	}
	double* v = *pTab;
	double det = 0;
	double coef = 1;
	for( int j = 0; j < nSize; j++ )
	{
		Complement( pTabO, pTab, 0, j, nSize );
		det += coef * *v++ * Det( pTabO, nSize - 1 );		//!!!!!!!!!!!poprawione
		coef = -coef;
	}
	DeleteMatrix( &pTabO, ( nSize - 1 ) );
	return det;
}

//---------------------------------------------------------------------------------------------

void LayoutEqu(double** pInv, double* pB, double* pRes, int nSize )		//wylicza: x = b * A^-1
{
	for( int i = 0; i < nSize; i++ )
	{
		double* r = pRes++;
		double* p = *pInv++;
		double* v = pB;
		for( int j = 0; j < nSize; j++, v++, p++ )
			*r += *v * *p;		//wypelnia tab wynikowa
	}
}

//---------------------------------------------------------------------------------------------

void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim )		//wycina, tworzy nSize - 1 macierz (pTabO)
{
	if( nDim > 1 )
	{
		for( int i = 0; i < nDim; i++ )
		{
			double* v = *pTabI++;
			if( i == nRow )
				continue;
			double* p = *pTabO++;
			for( int j = 0; j < nDim; j++, v++ )
			{
				if( j == nCol )		//!!!!poprawione
					continue;
				*p++ = 	*v;
			}
		}
	}
}

//---------------------------------------------------------------------------------------------

void ComplMatrix(double** pTabD, double** pTab, int nDim )		//liczy macierz dopelnien
{

	double** pTabO = NULL;
	if( !CreateMatrix( &pTabO, (nDim - 1) ) )
		printf( "ComplMatrix: CreateMatrix: Memory not allocated\n" );
	#ifdef _DEBUG_
	printf( "\nMacierz dopelnien: \n" );
	#endif
	for( int i = 0; i < nDim; i++ )
	{
		double coef = (i%2)? -1 : 1;

		double* v = *pTabD++;
		for( int j = 0; j < nDim; j++, v++ )
		{
			Complement( pTabO, pTab, i, j, nDim );
			*v = Det( pTabO, (nDim - 1) ) * coef;
			coef = -coef;		//!!!!!!!!!!!poprawione
		#ifdef _DEBUG_
			printf( "%.2lf\t", *v );
		#endif
		}
	#ifdef _DEBUG_
		printf( "\n" );
	#endif
	}
	DeleteMatrix( &pTabO, (nDim - 1) );
}

//---------------------------------------------------------------------------------------------

void TransMatrix( double** pTab, int nDim )		//transponuje macierz
{
	for( int i = 0; i < nDim; i++ )
	{
		double* v = *(pTab + i ) + i;
		for( int j = i; j < nDim; j++, v++ )
		{
			double n =*v;
			*v = pTab[j][i];
			pTab[j][i] = n;
		}
		#ifdef _DEBUG_
			printf( "\nTransponowanie Macierzy: wiersz i kolumna nr. %d\n", i + 1 );
			PrintMatrix( pTab, nDim );
		#endif
	}
}

//---------------------------------------------------------------------------------------------