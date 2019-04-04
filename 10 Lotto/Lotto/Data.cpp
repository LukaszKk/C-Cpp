#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "Data.h"

int  AllocAddPlayers( LottoPlayer*** pTab, int nCurrSize );
int  AllocAddBets( JackPotBets** pTab, int nCurrSize );
int  SetSex( LottoPlayer* p, char c );
int  SetDate( LottoPlayer* p, int d, int m, int y );


int AllocAddPlayers( LottoPlayer*** pTab, int nCurrSize )
{
	LottoPlayer** Backup = *pTab;
	*pTab = (LottoPlayer**)realloc( *pTab, (NPLAYER + nCurrSize) * sizeof(LottoPlayer*) );
	if( !(*pTab) )
	{
		printf( "Memory not reallocated\n" );
		*pTab = Backup;
		return 0;
	}
	memset( (*pTab + nCurrSize), 0, NPLAYER * sizeof(LottoPlayer*) );

	return NPLAYER;
}

int AllocAddBets( JackPotBets** pBet, int nCurrSize )
{
	JackPotBets* Backup = *pBet;
	*pBet = (JackPotBets*)realloc( *pBet, (NBETS + nCurrSize) * sizeof(JackPotBets) );
	if( !(*pBet) )
	{
		printf( "AllocAddBets: Memory not reallocated\n" );
		*pBet = Backup;
		return 0;
	}
	memset( *pBet + nCurrSize, 0, NBETS * sizeof(JackPotBets) );

	return NBETS;
}

int ReadData( LottoPlayer*** pAllDraws, const char* sfileName )
{
	FILE* fin = fopen( sfileName, "r" );
	if( !fin )
	{
		printf( "ReadData: File didn't open\n" );
		return 0;
	}
	int nCurrSize = 0;
	int nMaxSize = 0;
	LottoPlayer** p = *pAllDraws;
	while( !feof( fin ) )
	{
		char star;
		fscanf( fin, "%c", &star );
		if( star == '*' )
		{
			if( nCurrSize == nMaxSize )
			{	
				nMaxSize += AllocAddPlayers( &p, nCurrSize );
			    if( nCurrSize == nMaxSize )
				  break;
			}
			LottoPlayer* q = p[nCurrSize] = (LottoPlayer*)realloc( p[nCurrSize], sizeof(LottoPlayer) );							//!!!!!!!!!!!!!!!!!
			if( !q )
			{
				printf( "ReadData: Memory not reallocated\n" );
				return 0;
			}
			memset( q, 0, sizeof(LottoPlayer) );
			
			char sex;
			int day;
			int month;
			int year;
			BankCode* v1 = &q->bankID.BCode;
			IbanCode* v2  = &q->bankID.ICode;
			fscanf( fin, "%s %s %c %8c%3c %2c%2c%8c%17c %d/%d/%d %10c\n",														//!!!!!!!!!!!!!!!!!!!
				q->pSurName, q->pFirstName, &sex,
				v1->pSwift, v1->pBankBranch,
				v2->pPL, v2->pControl, v2->pBank, v2->pAccNum,
				&day, &month, &year,
				q->pPesel );
			if( !SetSex( q, sex ) )
			{
				printf( "Sex is inappropriate\n" );
				free( q );
				break;
			}
			if( !SetDate( q, day, month, year ) )
			{
				printf( "Date is inappropriate\n" );
				free( q );
				break;
			}
			nCurrSize++;
		}
		else
		{
			ungetc( star, fin );
			LottoPlayer* v = p[nCurrSize - 1];
			if( v->nBetsSize == v->nBetsMaxS )
			{	
				v->nBetsMaxS += AllocAddBets( &(v->Bets), v->nBetsSize );
				if( v->nBetsSize == v->nBetsMaxS )	
					break;
			}
			int n = v->nBetsSize;
			JackPotBets* b = &v->Bets[n];
			b->pArrTwo = (int*)calloc( NTWO, sizeof(int) );
			if( !(b->pArrTwo) )
			{
				printf( "ReadData: Memory not allocated\n" );
				break;
			}
			b->pArrFive = (int*)calloc( NFIVE, sizeof(int) );
			if( !(b->pArrFive) )
			{
				printf( "ReadData: Memory not allocated\n" );
				break;
			}

			int* q = b->pArrFive;
			for( int i = 0; i < NFIVE; i++, q++ )
				fscanf( fin, " %d", q );
			q = b->pArrTwo;
			fscanf( fin, " %d %d", q, q+1 );															//!!!!!!!!!!!!!!!!!!!!!
			v->nBetsSize++;
		}
	}
	*pAllDraws = p;

	HeapCheck();
	fclose( fin );
	return nCurrSize;
}

void FreeMem( LottoPlayer** pTab, int nDrawsNo )
{
	LottoPlayer** v = pTab;																//!!!!!!!!!!!!!!!!!!!
	for( int i = 0; i < nDrawsNo; i++, v++ )
	{
		JackPotBets* p = (*v)->Bets;
		for( int j = 0; j < (*v)->nBetsSize; j++, p++ )
		{
			free( p->pArrFive );
			free( p->pArrTwo );
		}
		free( (*v)->Bets );
		free( *v );
	}
	free( pTab );
}

int SetSex( LottoPlayer* p, char c )
{
	if( c != 'M' && c != 'm' && c != 'f' && c != 'F' )
		return 0;
	switch( c )
	{
	case 'm' :
    case 'M' : p->sex = male; break;
	case 'f' :
	case 'F' : p->sex = female; break;
	}
	return 1;
}

int SetDate( LottoPlayer* p, int d, int m, int y )
{
	if( (d < 1 || d > 31) || (m < 1 || m > 12) || (y < 1900) )
		return 0;
	p->Date.nYear = y;
	p->Date.nDayInMonth = d;

	tm readTime;
	readTime.tm_year = y - 1900;
	readTime.tm_mon = m - 1;
	readTime.tm_mday = d - 1;
	readTime.tm_hour = readTime.tm_min = readTime.tm_sec = 0;
	mktime( &readTime );

	switch( readTime.tm_wday )
	{
	case 0 : p->Date.day = Sun; break;
	case 1 : p->Date.day = Sat; break;
	case 2 : p->Date.day = Fri; break;
	case 3 : p->Date.day = Thu; break;
	case 4 : p->Date.day = Wed; break;
	case 5 : p->Date.day = Tue; break;
	case 6 : p->Date.day = Mon; break;
	}
	switch( m )
	{
	case 1 : p->Date.month = Jan; break;
	case 2 : p->Date.month = Feb; break;
	case 3 : p->Date.month = Mar; break;
	case 4 : p->Date.month = Apr; break;
	case 5 : p->Date.month = May; break;
	case 6 : p->Date.month = Jun; break;
	case 7 : p->Date.month = Jul; break;
	case 8 : p->Date.month = Aug; break;
	case 9 : p->Date.month = Sep; break;
	case 10 : p->Date.month = Oct; break;
	case 11 : p->Date.month = Nov; break;
	case 12 : p->Date.month = Dec; break;
	}

	return 1;
}

void HeapCheck()
{
	int heapstatus = _heapchk();  
	switch( heapstatus )  
	{
	case _HEAPOK:  
		printf(" OK - heap is fine\n" );  
		break;  
	case _HEAPEMPTY:  
		printf(" OK - heap is empty\n" );  
		break;  
	case _HEAPBADBEGIN:  
		printf( "ERROR - bad start of heap\n" );  
		break;  
	case _HEAPBADNODE:  
		printf( "ERROR - bad node in heap\n" );  
		break;  
	}  

}