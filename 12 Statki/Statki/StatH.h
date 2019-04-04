#ifndef _SDEBUG_H_
#define _SDEBUG_H_

#define N 10
#define M 10
#define DEPTH_MIN 8

typedef enum MoveXY{ UP, RIGHT, DOWN, LEFT } Move;
int move( int** pTab, int nRow, int nCol, int nDepth, 
	int move_nr, int x, int y, int* px, int* py, int** pRoot );
int root( int** pTab, int nRow, int nCol, int nDepth,  
	int x, int y, int** pRoot, int x_dest, int y_dest  );
void setTab( char* sFile, int** pTab, int nRow, int nCol );

#endif