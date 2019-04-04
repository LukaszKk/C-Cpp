#ifndef _LOTTO_HD_
#define _LOTTO_HD_

#include "defs.h"

int  ReadData( LottoPlayer*** pAllDraws, const char* sfileName );
void FreeMem( LottoPlayer** pTab, int nDrawsNo );
void HeapCheck();

#endif