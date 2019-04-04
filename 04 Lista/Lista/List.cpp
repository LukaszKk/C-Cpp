#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include "List.h"



//------------------------------------------------------------------
ListItem* MakeEmptyList()		//zwraca wskaznik do zainicjowanej listy
{
	ListItem* p = (ListItem*)malloc( sizeof(ListItem) );
	if( !p )
	{
		printf( "Make: Memory not allocated\n" );
	}
	memset( p, 0, sizeof(ListItem) );

	return p;
}
//------------------------------------------------------------------
int isEmpty( ListItem* pList )			//zwraca 0 gdy lista jest pusta lub 1
{
	return !( pList->m_pNext );
}
//------------------------------------------------------------------
ListItem* Front( ListItem* pList )			//zwraca wartosc szczytowa elementu
{
	if( !isEmpty( pList ) )
		return ( pList->m_pNext );
	return 0;
}
//------------------------------------------------------------------
void Insert( ListItem* pAfter, LISTINFO* pInfo )			//wstawia element do listy po wskazniku przekazanym w parametrze (pAfter-po jakim wskazniku, x-)
{
	ListItem* p = (ListItem*)malloc( sizeof(ListItem) );
	if( !p )
	{
		printf( "Insert: memory not allocated\n" );
		return;
	}
	memset( p, 0, sizeof(ListItem) );
	p->m_pInfo = pInfo;
	p->m_pNext = pAfter->m_pNext;
	pAfter->m_pNext = p;
}
//------------------------------------------------------------------
void InsertFront( ListItem* pAfter, LISTINFO* pInfo )				//wstawia na poczatek (inaczej push)
{
	Insert( pAfter, pInfo );
}
//------------------------------------------------------------------
void Remove( ListItem* pAfter )				//usuwa element po parametrze (podobne do Insert)
{
	if( !isEmpty( pAfter ) )
	{
		ListItem* p = pAfter->m_pNext;
		pAfter->m_pNext = p->m_pNext;
		free( p->m_pInfo );					//zwalnia zapisana info
		free( p );
	}
	else
		printf( "Remove: List empty\n" );
}
//------------------------------------------------------------------
void RemoveFront( ListItem* pAfter )				//usuwa pierwszy istotny element (odpowiednik del())
{
	Remove( pAfter );
}
//------------------------------------------------------------------
ListItem* Find( ListItem* pList, const void* x, ListItem** pPrev, int (__cdecl *comp)( const void*, const void* ) )		//wyszukuje elementu x
{
	*pPrev = pList;
	ListItem* p = pList->m_pNext;
	while( p )
	{
		if( !comp( x, (const void*)(p->m_pInfo) ) )
			return *pPrev;
		*pPrev = p;
		p = p->m_pNext;
	}
	*pPrev = NULL;

	return NULL;
}
//------------------------------------------------------------------
void FreeList( ListItem* pList )	//czysci liste
{
	while( !isEmpty( pList ) )		//!!!!!oprawione
		Remove( pList );
}
//------------------------------------------------------------------
void DelList( ListItem** pList )		//usuwa liste
{
	FreeList( *pList );
	free( *pList );
	*pList = NULL;
}
//------------------------------------------------------------------
void SortList( ListItem* pList, int (__cdecl *comp)( const void*, const void* ) ) //sortuje elementy
{	
	if( isEmpty( pList ) )
	{
		printf( "SortList: List Empty\n" );
		return;
	}
	ListItem* pFirst = pList;					//ustawia na pierwszy el, i do konca po jednym, zostawia po sobie najmniejszy el
	while( pFirst->m_pNext )					//wyszukuje najm i wstawia na poczatek, i tak od pierwszego do konca
	{
		ListItem* pMin = pFirst;				//najmniejszy el, ustawia na pFirst, pozniej skacze do konca i sprawdza czy ktorys jest mniejszy, jesli sie znajdzie najm to zamienia
		ListItem* pNext = pMin->m_pNext;		//skacze po kolejnych el od pFirst do konca
		while( pNext->m_pNext )					//znajduje najm el
		{
			if( comp( pMin->m_pNext->m_pInfo, pNext->m_pNext->m_pInfo ) == 1 )
				pMin = pNext;					//ustawia najm
			pNext = pNext->m_pNext;				//skacze dalej
		}
		if( pFirst != pMin )					//jesli najm jest inny niz pierwszy to zamienia pFirst z pMin
		{
			pNext = pMin->m_pNext->m_pNext;		//pNext ustawia na kolejna wart po pMin, pMin wskazuje na najm, a pNext w m_pInfo przechowuje kolejna wartosc po najmniejszej i wskazuje dalej
			pMin->m_pNext->m_pNext = pFirst->m_pNext;	// wskazuje na to na co pFirst
			pFirst->m_pNext = pMin->m_pNext;	//pFirst wskazuje na el po pMin
			pMin->m_pNext = pNext;				//pMin wskazuje na pNext
		}
		pFirst = pFirst->m_pNext;
	}
}
//------------------------------------------------------------------