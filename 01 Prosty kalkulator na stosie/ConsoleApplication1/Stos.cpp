#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include "Stos.h"
using namespace std;


					 //--------------------//wloz na stos
void dpush(dStack** dpHead, double x) //inaczej dodawanie elementu do listy
{
	dStack* dp = (dStack*)malloc(sizeof(dStack)); //przydzielenie pamieci
	if (dp) //jesli pamiec zostala przydzielona
	{
		memset(dp, 0, sizeof(dStack)); //zerowanie pamieci
		dp->dKey = x; //p wskazuje na Key, czyli to jest informacja c
		dp->dpNext = *dpHead; //p wskazuje na pNext, tak jak pHead
		*dpHead = dp; //pierwszy index to teraz p wskazujace na nastepny index pNext
	}
}
//---------------------//szczytowy el ze stosu
double dtop(dStack* dpHead)
{
	if (!(disEmpty(dpHead)))
		return dpHead->dKey;
	return 0;
}
//-------------------//sprawdz czy stos jest pusty
int disEmpty(dStack* dpHead)
{
	return !dpHead;
}
//------------------//zdejmij ze stosu
double dpop(dStack** dpHead)
{
	double x = dtop(*dpHead);
	if (!disEmpty(*dpHead))
	{
		double c = dtop(*dpHead);
		ddel(dpHead);
	}
	else
		printf("dpop: Stack underflown\n");
	return x;
}
//-----------------//usun ze stosu
void ddel(dStack** dpHead) //usuwa el z listy
{
	if (!(disEmpty(*dpHead)))
	{
		dStack* dp = *dpHead; //p i pHead wskazuja na to samo
		*dpHead = dp->dpNext; //pHead->pNext
		free(dp); //p wskazuje na pamiec do zwolnienia
	}
	else
		printf("del: Stack underflown\n");
}