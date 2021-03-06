// Lotto.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "defs.h"
#include "Data.h"
#include "Print.h"

int InitTab( int** pArr );
void CalcStat( int* pNums, LottoPlayer** pDraws, int nDrawsNo );
void Sort( LottoPlayer** pDraws, int nDrawsNo );
int StrCmp( char* s1, char* s2);


int main( int argc, char* argv[] )
{
	if( argc != 3 )
	{
		printf( "Usage: %s <Input File> <Output file>\n", argv[0] );
		return 1;
	}
	LottoPlayer** pPlayers = NULL;
	int nData = ReadData( &pPlayers, argv[1] );
	if( !nData )
	{
		printf( "There are no players\n" );
		return 1;
	}
	int* pStatArr = NULL;
	if( !InitTab( &pStatArr ) ) return 1;
	
	CalcStat( pStatArr, pPlayers, nData );
	Sort( pPlayers, nData );
	PrintResults( pStatArr, pPlayers, nData, argv[2] );
	
	free( pStatArr );
	FreeMem( pPlayers, nData );
	HeapCheck();

	printf( "\n\n" );
    return 0;
}

int InitTab( int** pArr)
{
	*pArr = (int*)calloc( STATISTICARR, sizeof(int) );
	if( *pArr ) return 1;
	printf( "InitTab: Memory not allocated\n" );
	return 0;
}

void CalcStat( int* pNums, LottoPlayer** pDraws, int nDrawsNo )
{
	for( int i = 0; i < nDrawsNo; i++, pDraws++ )
	{
		JackPotBets* p = (*pDraws)->Bets;
		for( int j = 0; j < (*pDraws)->nBetsSize; j++, p++ )
		{
			int* q = p->pArrFive;
			for( int k = 0; k < NFIVE; k++, q++ )
				if( (*q > 0) && (*q <= FIFTY) )						//!!!!!!!!!!!!!!!!!!!
					pNums[*q - 1]++;
			q = p->pArrTwo;
			for( int k = 0; k < NTWO; k++, q++ )
				if( (*q > 0) && (*q <= PESEL) )
					pNums[*q + FIFTY - 1]++;
		}
	}
}

void Sort( LottoPlayer** pDraws, int nDrawsNo )
{
	for( int i = 0; i < nDrawsNo; i++, pDraws++ )
	{
		LottoPlayer** q = pDraws + 1;
		for( int j = i + 1; j < nDrawsNo; j++, q++ )
		{
			int cmp = StrCmp( (*pDraws)->pSurName, (*q)->pSurName );
			if( ( ( cmp == 0 ) && (StrCmp( (*pDraws)->pFirstName, (*q)->pFirstName ) > 0) ) || ( cmp > 0 ) )
			{
				LottoPlayer* v = *pDraws;
				*pDraws = *q;
				*q = v;
			}
		}
	}
}

int StrCmp( char* s1, char* s2)
{
	char* s1Copy = (char*)calloc( strlen(s1) + 1, sizeof(char) );
	if( !s1Copy )
	{
		printf( "StrCmp: Memory not allocated\n" );
		return 0;
	}
	strcpy( s1Copy, s1 );
	char* s2Copy = (char*)calloc( strlen(s2) + 1, sizeof(char) );
	if( !s2Copy )
	{
		printf( "StrCmp: Memory not allocated\n" );
		return 0;
	}
	strcpy( s2Copy, s2 );
	_strupr( s1Copy );
	_strupr( s2Copy );
	int res = strcmp( s1Copy, s2Copy );
	free( s1Copy );
	free( s2Copy );

	return res;
}