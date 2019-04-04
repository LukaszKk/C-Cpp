#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "Nag.h"

void Merge( int* t, int* tmp, int left, int med, int right );
void Update( int* t, int left, int right );
void CopySerie( int* t, int* tmp, int nSize, int* i, int* j );
bool Copy( int* t, int* tmp, int nSize, int* i, int* j );

//=======================================================================	InsertionSort

void InsertionSort( int* t, int nSize )
{
	for( int i = 1; i < nSize; i++ )						//ustawia min na kolejny (na poczatku drugi) el, i skacze po poprzednich zamieniajac (sortujac)
	{
		int min = t[i];
		int j = i - 1;
		while( j >= 0 && t[j] > min )
			t[j + 1] = t[j--];
		t[j + 1] = min;
	}
}

//=======================================================================	SelectionSort

void SelectionSort( int* t, int nSize )						//ustawia min na pierwszy i szuka do konca najmniejszego i zamienia
{
	for( int i = 0; i < nSize - 1; i++ )
	{
		int min = t[i];
		int k = i;
		for( int j = i + 1; j < nSize; j++ )
			if( t[j] < min )
			{
				min = t[j];
				k = j;
			}
		t[k] = t[i];
		t[i] = min;
	}
}

//=======================================================================	HalfSort

void HalfSort( int* t, int nSize )					//znajduje najm dzielac tab na pol
{
	for( int i = 1; i < nSize; i++ )
	{
		int min = t[i];
		int left = 0;
		int right = i - 1;
		while( left <= right )								//ustawia left na index na ktorym trzeba wstawic el, wyszukuje left polowkowo
		{
			int med = (left + right) / 2;
			if( min < t[med] )
				right = med - 1;
			else
				left = med + 1;
		}
		for( int j = i - 1; j >= left; j-- )				//przsuwa wszystkie el o jeden w prawo robiac miejsce na indexie left dla min
			t[j + 1] = t[j];
		t[left] = min;
	}
}

//=======================================================================	ShakeSort ( mieszane )

void ShakeSort( int* t, int nSize )						//sortuje babelkowo w prawo, a pozniej wraca i sortuje w lewo
{
	int left = 0;
	int right = nSize - 1;
	int last = 0;										//index ostatniej zamiany
	while( left < right )
	{
		for( int i = left; i < right; i++ )
			if( t[i] > t[i + 1] )
			{
				int tmp = t[i + 1];
				t[i + 1] = t[i];
				t[i] = tmp;
				last = i + 1;
			}
		right = last;
		for( int i = right; i > left; i-- )	
			if( t[i] < t[i - 1] )
			{
				int tmp = t[i - 1];
				t[i - 1] = t[i];
				t[i] = tmp;
				last  = i - 1;
			}
		left = last;
	}
}

//=======================================================================	QuickSort

void QuickSort( int* t, int left, int right )
{
	int i = left;
	int j = right - 1;
	int med = t[(left + right) / 2];
	while( i <= j )
	{
		while( t[i] < med )
			i++;
		while( t[j] > med )
			j--;
		if( i <= j )
		{
			if( i != j )	//!!!!!!!!!!!!p
			{
				int tmp = t[i];
				t[i] = t[j];
				t[j] = tmp;
			}
			i++;
			j--;
		}
	}
	if( left < j )
		QuickSort( t, left, j + 1 );				//j + 1 bo jest wywolanie (t, 0, nSize), a j jest nSize - 1
	if( i < right )
		QuickSort( t, i, right );
}

//=======================================================================	SekMergeSort

void SekMergeSort( int* t, int nSize )
{
	int* tmp1 = (int*)calloc( nSize, sizeof( int ) );
	if( tmp1 == NULL )
	{
		printf( "SekMerge: Memory not allocated" );
		return;
	}
	int* tmp2 = (int*)calloc( nSize, sizeof( int ) );
	if( tmp2 == NULL )
	{
		printf( "SekMerge: Memory not allocated" );
		return;
	}
	int nSerie;
	do
	{
		int i = 0;		//poczatek t
		int j = 0;		//poczatek tmp1
		int k = 0;		//poczatek tmp2
		while( i < nSize )											//rozklada tablice t na 2 tablice
		{
			while( (i < nSize - 1) && (t[i] <= t[i + 1]) ) 
				tmp1[j++] = t[i++];
			if( i < nSize )											//jeden nie zostal przekopiowany
				tmp1[j++] = t[i++];
			while( (i < nSize - 1) && (t[i] < t[i + 1]) ) 
				tmp2[k++] = t[i++];
			if( i < nSize ) 
				tmp2[k++] = t[i++];
		}
		//laczenie
		int righttmp1 = j;											//koniec tmp1
		int righttmp2 = k;											//koniec tmp2
		nSerie = 0;
		i = j = k = 0;
		while( (j < righttmp1) && (k < righttmp2) )
		{
			bool end = true;										//info czy koniec kopiowania, true - nie, false - koniec
			while( end )
			{
				if( tmp1[j] <= tmp2[k] )							//kopiuj mniejszy
				{
					end = Copy( t, tmp1, righttmp1, &i, &j );
					if( !end )										//jesli koniec serii z tmp1
						CopySerie( t, tmp2, righttmp2, &i, &k );
				}
				else
				{
					end = Copy( t, tmp2, righttmp2, &i, &k );
					if( !end )
						CopySerie( t, tmp1, righttmp1, &i, &j );
				}
				nSerie++;
			}
		}
		while( j < righttmp1 )										//jesli nie koniec tablicy to dokopiuj
		{
			CopySerie( t, tmp1, righttmp1, &i, &j );
			nSerie++;
		}
	} while( nSerie > 1 );
	
	free( tmp1 );
	free( tmp2 );
}

//-----------------------------------------------------------------------

void CopySerie( int* t, int* tmp, int nSize, int* i, int* l )
{
	bool end = true;
	while( end )
		end = Copy( t, tmp, nSize, i, l );
}

//-----------------------------------------------------------------------

bool Copy( int* t, int* tmp, int nSize, int* i, int* l )
{
	t[(*i)++] = tmp[(*l)++];
	return !( *l == nSize || tmp[*l] < tmp[*l - 1] );				//czy koniec tablicy, czy koniec serii
}

//=======================================================================	rekMergeSort

void MergeSort( int* t, int* tmp, int left, int right )
{
	if( left < right )
	{
		int med = (left + right) / 2;
		MergeSort( t, tmp, left, med );
		MergeSort( t, tmp, med + 1, right );
		Merge( t, tmp, left, med, right );
	}
}

//-----------------------------------------------------------------------

void Merge( int* t, int* tmp, int left, int med, int right )
{
	for( int i = left; i <= right; i++ )
		tmp[i] = t[i];
	int i = left;																//poczatek tablicy "pierwszej" - do polowy
	int j = med + 1;															//poczatek tablicy "drugiej" - od polowy
	int q = left;																//indeks tablicy tmp
	while( i <= med && j <= right )												//kopiowanie danych tablicy t do tmp, porownuje i-ty z j-tym i wstawia mniejszy
	{
		if( tmp[i] < tmp[j] )
			t[q++] = tmp[i++];
		else
			t[q++] = tmp[j++];
	}
	while( i <= med )											//jesli jakies elementy zostaly to wrzuc je do tablicy
		t[q++] = tmp[i++];
}

//=======================================================================	HeapSort

void HeapSort( int* t, int nSize )
{
	for( int med = nSize / 2; med >= 0; med-- )														//buduje stos
		Update( t, med, nSize - 1 );
	for( int right = nSize - 1; right > 0; right-- )												//zamienia pierwszy z ostatnim, ostatni jest posortowany
	{
		int x = t[0];
		t[0] = t[right];
		t[right] = x;
		Update( t, 0, right - 1 );
	}
}

//-----------------------------------------------------------------------

void Update( int* t, int left, int right )
{
	if(left == right ) return;

	int i = left;											//parent
	int j = 2 * i + 1;										//child
	int x = t[i];
	while( j <= right )
	{
		if( j < right && t[j] < t[j + 1] )
			j++;
		if( x > t[j] )
			break;
		t[i] = t[j];
		i = j;
		j = 2 * i + 1;
	}
	t[i] = x;
}

//=======================================================================