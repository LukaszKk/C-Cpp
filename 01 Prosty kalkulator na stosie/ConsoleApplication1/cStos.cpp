#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include "cStos.h"
using namespace std;

//--------------------//wloz na stos
void push(Stack** pHead, char c) //inaczej dodawanie elementu do listy
{
	Stack* p = (Stack*)malloc(sizeof(Stack)); //przydzielenie pamieci
	if (p) //jesli pamiec zostala przydzielona
	{
		memset(p, 0, sizeof(Stack)); //zerowanie pamieci
		p->Key = c; //p wskazuje na Key, czyli to jest informacja c
		p->pNext = *pHead; //p wskazuje na pNext, tak jak pHead //dodajemy *pHead bo nie dzialam na pHead tylko na *pHead ///(*p).pHead
		*pHead = p; //pierwszy index to teraz p wskazujace na nastepny index pNext
	}
}
//---------------------//szczytowy el ze stosu
char top(Stack* pHead)
{
	if (!(isEmpty(pHead)))
		return pHead->Key;
	return 0;
}
//-------------------//sprawdz czy stos jest pusty
int isEmpty(Stack* pHead)
{
	return !pHead;
}
//------------------//zdejmij ze stosu
char pop(Stack** pHead)
{
	char c = top(*pHead);
	if (c)
		del(pHead);
	else
		printf("pop: Stack underflown\n");
	return c;
}
//-----------------//usun ze stosu
void del(Stack** pHead) //usuwa el z listy
{
	if (!(isEmpty(*pHead)))
	{
		Stack* p = *pHead; //p i pHead wskazuja na to samo
		*pHead = p->pNext; //pHead->pNext
		free(p); //p wskazuje na pamiec do zwolnienia
	}
	else
		printf("del: Stack underflown\n");
}