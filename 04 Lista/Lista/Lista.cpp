// Lista.cpp: Definiuje punkt wejścia dla aplikacji konsolowej.
//

#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include "List.h"
#include "global.h"

#define MAX 16
#define COL 4

void PrintList( ListItem* pList, int nLineSize );

//==================================================================
int main( int argc, char* argv[] )
{
	ListItem* pList = MakeEmptyList();
	for( int i = 0; i < MAX; i++ )
	{
		LISTINFO* x = (LISTINFO*)malloc( sizeof(LISTINFO) );
		x->nKey = 50 + i;
		InsertFront( pList, x );
	}
	PrintList( pList, COL );
	printf( "\n" );
	LISTINFO* x = (LISTINFO*)malloc( sizeof(LISTINFO) );
	x->nKey = 65;
	ListItem* pPrev = NULL;
	ListItem* f = Find( pList, x, &pPrev, compare );
	if( f )
		RemoveFront( f );
	PrintList( pList, COL );
	printf( "\n\n" );
	x->nKey = 50;
	InsertFront( Find( pList, x, &pPrev, compare ), x );
	SortList( pList, compare );
	PrintList( pList, COL );
	DelList( &pList );
	
	printf( "\n\n" );
	return 0;
}
//==================================================================

void PrintList( ListItem* pList, int nLineSize )
{
	ListItem* p = Front( pList );
	int i = 1;
	while( p != NULL )
	{
		printf( "%d ", p->m_pInfo->nKey );
		if( ( i++ % nLineSize ) == 0)
			printf( "\n" );
		p = p->m_pNext;
	}
}
//------------------------------------------------------------------
int compare( const void* pFirst, const void* pNext)
{
	if( ((LISTINFO*)pFirst)->nKey > ((LISTINFO*)pNext)->nKey )
		return 1;
	if( ((LISTINFO*)pFirst)->nKey == ((LISTINFO*)pNext)->nKey )
		return 0;
	return -1;
}