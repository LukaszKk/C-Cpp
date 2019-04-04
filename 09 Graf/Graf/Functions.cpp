#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include "Functions.h"
#include "QPrior.h"

#define MS 4
#define SIX 60
#define STAT SIX/MS

Vertex* InitList( int nSize )
{
	Vertex* q = (Vertex*)calloc( nSize, sizeof(Vertex) );		//tworzy tablice
	if( !q )
	{
		printf( "InitList: memory not allocated\n" );
		return 0;
	}
	Vertex* p = q;
	for( int i = 0; i < nSize; i++, p++ )
	{
		p->NeighbourList = (NList*)calloc( 1, sizeof(NList) );
		if( !(p->NeighbourList) )
		{
			printf( "InitList: memory not allocated\n" );
			return 0;
		}
		p->Path = (int*)calloc( nSize, sizeof(int) );
		if( !(p->Path) )
		{
			printf( "InitList: memory not allocated\n" );
			return 0;
		}
	}

	return q;
}

double GetNum( FILE* fi, char* c )
{
	double digit = 0;
	double coef = 0.1;
	while( (*c != ' ') && (*c != '\t') && (*c != '\n') && (*c != EOF) )
	{
		if( *c == '.' )
		{
			*c = getc( fi );
			digit += (*c - '0') * coef;
			coef *= 0.1;
		}
		else
			digit = digit * 10 + (*c - '0');
		*c = getc( fi );
	}
	return digit;
}
void SkipSpaces( FILE* fi, char* c )
{
	while( (*c < '0' || *c > '9') && (*c != '\n') && (*c != EOF) )
		*c = getc( fi );
}

void Read( FILE* fi, Vertex* q, int nSize )
{
	char c;
	getc( fi );
	c = getc( fi );
	for( int i = 0; i < nSize; i++ )
	{
		q[i].NeighbourList->Index = (int)GetNum( fi, &c );
		SkipSpaces( fi, &c );
		q[i].NeighbourList->IsShop = (int)GetNum( fi, &c );
		SkipSpaces( fi, &c );

		while( (c != '\n') && !feof( fi ) )			//(c != EOF) )				//read line by line
		{
			NList* p = (NList*)calloc( 1, sizeof(NList) );
			if( !p )
			{
				printf( "Read: Memoy not allocated\n" );
				return;
			}

			p->Index = (int)GetNum( fi, &c );
			SkipSpaces( fi, &c );
			p->Distance = GetNum( fi, &c );
			SkipSpaces( fi, &c );
			p->IsShop = (int)GetNum( fi, &c );
			SkipSpaces( fi, &c );
			
			p->pNext = q[i].NeighbourList->pNext;
			q[i].NeighbourList->pNext = p;
		}
		if( !feof( fi ) )							//c != EOF )
			c = getc( fi );
	}
}

void DFS( Vertex* q, int v, int** t )
{
	for( NList* p = q[v].NeighbourList->pNext; p; p = p->pNext )
		if( !t[v][p->Index] )
		{
			t[v][p->Index] = 1;
			p->Time = p->Distance * STAT;										//!!!!!!!!!!!!!!!!
			DFS( q, p->Index, t );
		}
}

void CountDijkstra( Vertex* q, int nSize )
{
	for( int i = 0; i < nSize; i++ )
		if( !q[i].NeighbourList->IsShop )
		{
			q[i].WayShop = Dijkstra( q, nSize, i );
			int* tab = (int*)calloc( nSize, sizeof(int) );								//sciezka
			if( !tab )
			{
				printf( "CountDijkstra: Memory not allocated\n" );
				return;
			}
			memcpy( tab, q[i].Path, nSize * sizeof(int) );
			int k = q[i].IndexShop;
			q[i].Path[0] = k;
			int j = 0;
			for( j = 1; k != i; j++ ) 
			{
				q[i].Path[j] = tab[k];
				k = tab[k];
			}
			for( int m = 0; m < (j + 1) / 2; m++ )
			{
				int tmp = q[i].Path[j - m - 1];
				q[i].Path[j - m - 1] = q[i].Path[m];
				q[i].Path[m] = tmp;
			}
			free( tab );
		}
}

double Dijkstra( Vertex* village, int nSize, int nFirst )
{
	double* PathTime = (double*)calloc( nSize, sizeof(double) );
	if( !PathTime )
	{
		printf( "Dijkstra: Memory not allocated\n" );
		return 0;
	}
	double* PathLen = (double*)calloc( nSize, sizeof(double) );
	if( !PathLen )
	{
		printf( "Dijkstra: Memory not allocated\n" );
		return 0;
	}

	PQueue* q = PQInit( nSize );												//tablica przechowuje wartosci aktualnie najkrotszej drogi 
	for( int i = 0; i < nSize; i++ )
		PathLen[i] = INT_MAX;
	PathLen[ nFirst ] = 0;
	PQEnQueue( q, nFirst, 0 );
	double x = 0;
	while( !pQisEmpty( q ) )
	{
		int k = PQDeQueue( q );
		if( village[k].NeighbourList->IsShop )
		{
			village[nFirst].IndexShop = k;
			village[nFirst].WayTime = PathTime[k];
			x = PathLen[k];										//!!!!!!!!!
			break;
		}
		for( NList* p = village[k].NeighbourList->pNext; p; p = p->pNext )
		{
			int nNode = p->Index;
			if( (PathLen[k] + p->Distance) < PathLen[nNode] )
			{
				village[nFirst].Path[nNode] = k;
				PathTime[nNode] = PathTime[k] + p->Time;
				PathLen[nNode] = PathLen[k] + p->Distance;
				PQEnQueue( q, nNode, PathLen[ nNode ] );
			}
		}
	}
	PQRelease( &q );
	free( PathTime );
	free( PathLen );
	return x;
}

void PrintToTxt( Vertex* q, int nSize, const char* sFileName )
{
	FILE* fi = NULL;
	if( !(fi = fopen( sFileName, "w" )) )
	{
		printf( "File didn't create\n" );
		return;
	}

	for( int i = 0; i < nSize; i++ )
		if( !q[i].NeighbourList->IsShop )
		{
			fprintf( fi, "%d\t", q[i].NeighbourList->Index );
			fprintf( fi, "najblizszy sklep: %d \t", q[i].IndexShop );
			fprintf( fi, "czas przejscia: %.1lf min \t", q[i].WayTime );
			fprintf( fi, "odl. do sklepu: %.1lf km \t\t", q[i].WayShop );
			fprintf( fi, "droga do sklepu: %d", q[i].Path[0] );
			int j;
			for( j = 1; (j < nSize - 1) && !(q[ q[i].Path[j] ].NeighbourList->IsShop); j++ )
				fprintf( fi, "->%d", q[i].Path[j] );
			fprintf( fi, "->%d\n", q[i].Path[j] );
		}

	fclose( fi );
}

void Release( Vertex** q, int nSize )
{
	Vertex* p = *q;
	for( int i = 0; i < nSize; i++, p++ )
	{
		free( p->NeighbourList );
		free( p->Path );
	}
	free( *q );
}