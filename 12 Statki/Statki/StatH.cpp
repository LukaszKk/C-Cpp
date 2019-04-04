#include <stdio.h>
#include "StatH.h"

int move( int** pTab, int nRow, int nCol, int nDepth, 
	int move_nr, int x, int y, int* px, int* py, int** pRoot )
{
	switch( move_nr )
	{
	case UP : (*px)--; break;
	case RIGHT : (*py)++; break;
	case DOWN : (*px)++; break;
	case LEFT : (*py)--; break;
	}
	if( *px < nCol && *px >= 0 && *py < nRow && *py >= 0 )
		if( pTab[*px][*py] > nDepth + 1 )
			if( !pRoot[*px][*py] )
				return 1;

	return 0;
}

int root( int** pTab, int nRow, int nCol, int nDepth,  
	int x, int y, int** pRoot, int x_dest, int y_dest  )
{
	pRoot[x][y] = 1;
	if( (x == x_dest) && (y == y_dest) )
		return 1;

	int px = x;
	int py = y;
	
	for( int i = 0; i <= LEFT; i++ )
	{
		if( move( pTab, nRow, nCol, nDepth, i, x, y, &px, &py, pRoot ) )
			if( root( pTab, nRow, nCol, nDepth, px, py, pRoot, x_dest, y_dest ) )
				return 1;
		px = x;
		py = y;
	}

	pRoot[x][y] = 2;							//ruch byl zly
	return 0;
}

void setTab( char* sFile, int** pTab, int nRow, int nCol )
{
	FILE* fin = fopen( sFile, "r" );
	if( !fin )
	{
		printf( "seTab: File didn't open" );
		return;
	}
	for( int i = 0; i < nRow; i++, pTab++ )
	{
		int* v = *pTab;
		for( int j = 0; j < nCol; j++, v++ )
			fscanf( fin, "%d", v );
	}

	fclose( fin );
}