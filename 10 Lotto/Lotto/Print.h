#ifndef _LOTTO_HP_
#define _LOTTO_HP_

#include "defs.h"

void PrintResults( int* pNums, LottoPlayer** pDraws, int nDrawsNo, const char* sFileName );
void PrintSex( FILE* fout, LottoPlayer* p );
void PrintDate( FILE* fout, LottoPlayer* p );
void PrintBets( FILE* fout, JackPotBets** pBets );

#endif