#ifndef _QUEUEFIFO_
#define _QUEUEFIFO_

typedef struct tagQueue
{
	int mCurrSize;			//ilosc zapelnionych
	int mFront;				//pierwszy zajety
	int mTail;				//pierwszy wolny
	int nMaxEl;				//koniec tab
	int* Arr;
} Queue;

Queue* QCreate( int nSize );
int QisEmpty( Queue* q );
void QEnQueue( Queue* q, int x );
int QDeQueue( Queue* q );
void QClear( Queue* q );
void QDel( Queue** q );

#endif