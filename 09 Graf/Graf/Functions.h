#ifndef _GRAF_H_
#define _GRAF_H_

typedef struct tagNList						//lista
{
	tagNList* pNext;
	int		  Index;						//index
	double	  Distance;						//odleglosc
	double	  Time;							//czas przejscia
	int		  IsShop;						//czy sklep
} NList;

typedef struct tagVertex					//tablica
{
	NList*	  NeighbourList;				//lista
	int		  IndexShop;					//index najblizszego sklepu
	double	  WayShop;						//odleglosc do sklepu
	double	  WayTime;						//czas przejscia calosci
	int* Path;								//droga do sklepu
} Vertex;

Vertex* InitList( int );
void Read( FILE*, Vertex*, int );
void DFS( Vertex*, int, int** );
void CountDijkstra( Vertex*, int );
double Dijkstra( Vertex*, int nSize, int nFirst );
void PrintToTxt( Vertex*, int, const char* );
void Release( Vertex**, int );

#endif