#ifndef _MATRIX_H_
#define _MATRIX_H

int CreateMatrix( double*** pTab, int nSize );
void PrintMatrix( double** pTab, int nSize );
void DeleteMatrix( double*** pTab, int nSize );
void InverseMatrix( double** pInv, double** pTab, int nSize, double det );
double Det( double** pTab, int nSize );
void LayoutEqu(double** pInv, double* pB, double* pRes, int nSize );
void PrintMatrix( double** pTab, int nSIze );

#endif