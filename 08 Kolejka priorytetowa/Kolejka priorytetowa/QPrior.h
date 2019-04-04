#ifndef _PRIOR_H_
#define _PRIOR_H_

typedef struct
{
	int nKey;
	int nPrior;
} PQItem;
typedef struct 
{
	PQItem* Arr;
	int pQSize;
	int pQCurrSize;
} PQueue;

PQueue* PQInit( int nSize );
int pQisEmpty( PQueue* );
void PQEnQueue( PQueue*, int nKey, int nPrior );
int PQDeQueue( PQueue* );
void PQRelease( PQueue** );
void PQPrint( PQueue*, int i );
void DecreaseKey( PQueue*, int nKey, int nPrior );
void IncreaseKey( PQueue*, int nKey, int nPrior );


#endif