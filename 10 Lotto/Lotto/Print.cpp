#include <stdio.h>
#include <string.h>
#include "Print.h"


void PrintResults( int* pNums, LottoPlayer** pDraws, int nDrawsNo, const char* sFileName )
{
	FILE* file = fopen( sFileName, "w" );
	if( !file )
	{
		printf( "File didn't open\n" );
		return;
	}

	for( int i = 0; i < nDrawsNo; i++, pDraws++ )
	{
		fprintf( file, " %s %s ", (*pDraws)->pSurName, (*pDraws)->pFirstName );
		int x = NAMES - strlen((*pDraws)->pSurName) - strlen((*pDraws)->pFirstName);
		for( int i = 0; i < x; i++ )
			fprintf( file, " " );
		PrintSex( file, *pDraws );
		PrintDate( file, *pDraws );
		BankCode* v1 = &(*pDraws)->bankID.BCode;
		IbanCode* v2  = &(*pDraws)->bankID.ICode;
		fprintf( file, "%.8s%.3s\t%.2s%.2s%.8s%17s %.10s", v1->pSwift, v1->pBankBranch,
			v2->pPL, v2->pControl, v2->pBank, v2->pAccNum,
			(*pDraws)->pPesel );
		fprintf( file, "\n----------------------------------------------------------------------------------------------------------------\n" );
		
		JackPotBets* p = (*pDraws)->Bets;
		for( int j = 0; j < (*pDraws)->nBetsSize - 1; j++, p++ )
			PrintBets( file, &p );
		fprintf( file, "\n" );
	}

	fprintf( file, "\n\n =======================================\n     S T A T I S T I C S\n =======================================\n" );
	int* q = pNums;											//!!!!!!!!!!!!!!!!!!!
	for( int i = 0; i < FIFTY; i++, q++ )
	{
		fprintf( file, " %2d: %2d\t", i + 1, *q );
		if( !((i + 1) % PESEL) )
			fprintf( file, "\n" );
	}
	fprintf( file, "\n\n" );
	for( int i = 0; i < PESEL; i++, q++ )
	{
		fprintf( file, " %2d: %2d\t", i + 1, *q );
		if( !((i + 1) % NFIVE) )
			fprintf( file, "\n" );
	}

	fclose( file );
}

void PrintSex( FILE* fout, LottoPlayer* p )
{
	switch( p->sex )
	{
	case female : fprintf( fout, "*Panienka*  "); break;
	case male : fprintf( fout, "*Facet*     " ); break;
	}
}

void PrintDate( FILE* fout, LottoPlayer* p )
{
	switch( p->Date.day )
	{
	case Mon :  fprintf( fout, "Mon" ); break;
	case Tue :  fprintf( fout, "Tue" ); break;
	case Wed :  fprintf( fout, "Wed" ); break;
	case Thu :  fprintf( fout, "Thu" ); break;
	case Fri :  fprintf( fout, "Fri" ); break;
	case Sat :  fprintf( fout, "Sat" ); break;
	case Sun :  fprintf( fout, "Sun" ); break;
	}
	fprintf( fout, ", %2d/", p->Date.nDayInMonth );
	switch( p->Date.month )
	{
	case Jan :  fprintf( fout, "Jan" ); break;
	case Feb :  fprintf( fout, "Feb" ); break;
	case Mar :  fprintf( fout, "Mar" ); break;
	case Apr :  fprintf( fout, "Apr" ); break;
	case May :  fprintf( fout, "May" ); break;
	case Jun :  fprintf( fout, "Jun" ); break;
	case Jul :  fprintf( fout, "Jul" ); break;
	case Aug :  fprintf( fout, "Aug" ); break;
	case Sep :  fprintf( fout, "Sep" ); break;
	case Oct :  fprintf( fout, "Oct" ); break;
	case Nov :  fprintf( fout, "Nov" ); break;
	case Dec :  fprintf( fout, "Dec" ); break;
	}
	fprintf( fout, "/%d\t", p->Date.nYear );
}

void PrintBets( FILE* fout, JackPotBets** pBets )
{
	int* q = (*pBets)->pArrFive;
	for( int k = 0; k < NFIVE; k++, q++ )
		fprintf( fout, "%2d ", *q );
	fprintf( fout, "\t" );
	q = (*pBets)->pArrTwo;
	for( int k = 0; k < NTWO; k++, q++ )
		fprintf( fout, "%2d ", *q );
	fprintf( fout, "\n" );
}