#pragma once
#ifndef _SORTED_
#define _SORTED_

//iteracyjne
void InsertionSort( int* t, int nSize );
void SelectionSort( int* t, int nSize );
void HalfSort( int* t, int nSize );
void ShakeSort( int* t, int nSize);
void SekMergeSort( int* t, int nSize );
void HeapSort( int* t, int nSize );

//rekurencyjne
void QuickSort( int* t, int left, int right );
void MergeSort( int* t, int* tmp, int left, int right );

#endif